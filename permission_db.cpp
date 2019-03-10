/*

Permission DB.

Copyright (C) 2018 Sergey Kolevatov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

// $Revision: 10612 $ $Date:: 2019-03-10 #$ $Author: serge $

#include "permission_db.h"          // self

#include "utils/dummy_logger.h"     // dummy_log_debug
#include "utils/read_config_file.h" // utils::read_config_file
#include "utils/tokenizer_ext.h"    // tokenize_and_convert
#include "utils/utils_assert.h"           // ASSERT
#include "utils/mutex_helper.h"     // MUTEX_SCOPE_LOCK

#include "str_helper.h"             // StrHelper


namespace permission_db
{

PermissionDb::PermissionDb():
        log_id_( 0 ),
        product_db_( nullptr )
{
}

bool PermissionDb::init(
        uint32_t                        log_id,
        const std::string               & permission_db,
        const product_db::ProductDb     * product_db )
{
    log_id_ = log_id;

    ASSERT( product_db );

    product_db_ = product_db;

    if( permission_db.empty() )
        return false;

    std::vector<std::string> lines;

    utils::read_config_file( permission_db, lines );

    parse_lines( lines );

    dummy_log_info( log_id_, "loaded %u permissions from %s", lines.size(), permission_db.c_str() );

    return true;
}

bool PermissionDb::is_permitted(
        user_id_t           user_id,
        const RequestParams & rp ) const
{
    dummy_log_trace( log_id_, "is_permitted: user_id %u, %s", user_id, StrHelper::to_string( rp ).c_str() );

    auto permission = get_permission( user_id );

    if( permission == nullptr )
    {
        dummy_log_error( log_id_, "is_permitted: user_id %u not found", user_id );
        return false;
    }

    dummy_log_debug( log_id_, "is_permitted: user_id %u, %u products available", user_id, permission->product_ids.size() );

    for( auto prod_id : permission->product_ids )
    {
        if( is_permitted_for_prod( prod_id, rp ) )
        {
            dummy_log_info( log_id_, "is_permitted: user_id %u, %s - permitted (product id %u)", user_id, StrHelper::to_string( rp ).c_str(), prod_id );
            return true;
        }
    }

    dummy_log_info( log_id_, "is_permitted: user_id %u, %s - not permitted", user_id, StrHelper::to_string( rp ).c_str() );

    return false;
}

bool PermissionDb::is_permitted_for_prod(
        product_id_t        product_id,
        const RequestParams & rp ) const
{
    auto prod = product_db_->get_product( product_id );

    if( prod == nullptr )
    {
        dummy_log_error( log_id_, "is_permitted: product id %u not found", product_id );
        return false;
    }

    return is_permitted_for_prod( prod, rp );
}

bool PermissionDb::is_permitted_for_prod(
        const product_db::Product   * product,
        const RequestParams         & rp ) const
{
    if( product->langs.count( rp.lang ) == 0 )
        return false;

    if( product->template_ids.count( rp.template_id ) == 0 )
        return false;

    return true;
}

const Permission * PermissionDb::get_permission( user_id_t user_id ) const
{
    auto it = map_user_id_to_permission_.find( user_id );

    if( it == map_user_id_to_permission_.end() )
        return nullptr;

    return & it->second;
}

const std::vector<const product_db::Product*> PermissionDb::get_products( user_id_t user_id ) const
{
    std::vector<const product_db::Product*> res;

    auto permission = get_permission( user_id );

    if( permission == nullptr )
    {
        return res;
    }

    for( auto p : permission->product_ids )
    {
        auto product = product_db_->get_product( p );

        if( product )
        {
            res.push_back( product );
        }
    }

    return res;
}

void PermissionDb::parse_lines( const std::vector<std::string> & lines )
{
    for( auto & l : lines )
    {
        process_line( l );
    }
}

void PermissionDb::process_line( const std::string & line )
{
    auto e = to_flat_permission( line );

    process_line( e );
}

void PermissionDb::process_line( const FlatPermission & e )
{
    auto b = map_user_id_to_permission_.insert( std::make_pair( e.user_id, e.permission ) ).second;

    if( b == false )
    {
        throw std::runtime_error( "duplicate user id " + std::to_string( e.user_id ) );
    }
}

PermissionDb::FlatPermission PermissionDb::to_flat_permission( const std::string & l )
{
    // format: <user_id>;product_id_1 ... product_id_n;
    FlatPermission res;

    std::vector< std::string > elems;
    tokenize_to_vector( elems, l, ";" );

    if( elems.size() < 1 )
        throw std::runtime_error( "not enough arguments (<1) in entry: " + l  );

    try
    {
        res.user_id         = std::stoul( elems[0] );

        if( elems.size() > 1 )
            res.permission      = to_permission( elems );
    }
    catch( std::exception & e )
    {
        throw std::runtime_error( std::string( e.what() ) + ": " + l );
    }

    return res;
}

Permission PermissionDb::to_permission( const std::vector<std::string> & elems )
{
    // format: <user_id>;product_id_1 ... product_id_n;
    Permission res;

    std::vector<product_id_t> prod_ids;
    utils::tokenize_and_convert( prod_ids, elems[1], " " );

    res.product_ids    = std::set<product_id_t>( prod_ids.begin(), prod_ids.end() );

    return res;
}
} // namespace permission_db
