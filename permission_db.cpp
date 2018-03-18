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

// $Revision: 8777 $ $Date:: 2018-03-16 #$ $Author: serge $

#include "permission_db.h"          // self

#include "utils/dummy_logger.h"     // dummy_log_debug
#include "utils/read_config_file.h" // utils::read_config_file
#include "utils/tokenizer_ext.h"    // tokenize_and_convert
#include "utils/assert.h"           // ASSERT
#include "utils/mutex_helper.h"     // MUTEX_SCOPE_LOCK


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
        throw std::runtime_error( "duplicate permission id " + std::to_string( e.user_id ) );
    }
}

PermissionDb::FlatPermission PermissionDb::to_flat_permission( const std::string & l )
{
    // format: <user_id>;product_id_1 ... product_id_n;
    FlatPermission res;

    std::vector< std::string > elems;
    tokenize_to_vector( elems, l, ";" );

    if( elems.size() < 2 )
        throw std::runtime_error( "not enough arguments (<2) in entry: " + l  );

    try
    {
        res.user_id         = std::stoi( elems[0] );
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

    std::vector<product_id_t> templ_ids;
    utils::tokenize_and_convert( templ_ids, elems[1], " " );

    return res;
}
} // namespace permission_db
