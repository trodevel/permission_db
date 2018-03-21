/*

Example.

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

// $Revision: 8806 $ $Date:: 2018-03-20 #$ $Author: serge $

#include <cstdio>
#include <sstream>                          // std::stringstream
#include <iostream>                         // std::cout

#include "permission_db.h"                  // PermissionDb

#include "utils/dummy_logger.h"             // dummy_log_set_log_level
#include "product_db/str_helper.h"          // to_string()
#include "str_helper.h"                     // to_string()

void loading_test( uint32_t log_id, const char * name, const char * filename, product_db::ProductDb * prod_db )
{
    std::cout << name << " - started" << std::endl;

    try
    {
        permission_db::PermissionDb perm_db;

        perm_db.init( log_id, filename, prod_db );
    }
    catch( std::exception & e )
    {
        std::cout << "exception: " << e.what() << std::endl;
    }

    std::cout << name << " - finished" << std::endl;
}

void test_03( permission_db::PermissionDb & perm_db )
{
    std::cout << "03" << " - started" << std::endl;

    permission_db::user_id_t user_id = 12121212;

    auto perm = perm_db.get_permission( user_id );

    if( perm )
    {
        std::cout << "OK: found permission for user - " << * perm << std::endl;
    }
    else
    {
        std::cout << "ERROR: user id " << user_id << " not found" << std::endl;
    }

    std::cout << "03" << " - finished" << std::endl;
}

void test_04( permission_db::PermissionDb & perm_db )
{
    std::cout << "04" << " - started" << std::endl;

    permission_db::user_id_t user_id = 77777777;

    auto perm = perm_db.get_permission( user_id );

    if( perm )
    {
        std::cout << "ERROR: found unexpected permission for user - " << * perm << std::endl;
    }
    else
    {
        std::cout << "OK: invalid user id " << user_id << " not found" << std::endl;
    }

    std::cout << "04" << " - finished" << std::endl;
}

void test_05( permission_db::PermissionDb & perm_db )
{
    std::cout << "05" << " - started" << std::endl;

    permission_db::user_id_t user_id = 34343434;

    auto products = perm_db.get_products( user_id );

    if( products.empty() == false )
    {
        std::cout << "OK: found " << products.size() << " products for user id " << user_id << std::endl;

        for( auto & p : products )
        {
            std::cout << * p << std::endl;
        }
    }
    else
    {
        std::cout << "ERROR: user id " << user_id << " not found" << std::endl;
    }

    std::cout << "05" << " - finished" << std::endl;
}

int main()
{
    try
    {
        dummy_logger::set_log_level( log_levels_log4j::DEBUG );

        auto log_id_prod        = dummy_logger::register_module( "ProductDb" );
        auto log_id             = dummy_logger::register_module( "PermissionDb" );

        product_db::ProductDb       prod_db;
        permission_db::PermissionDb perm_db;

        prod_db.init( log_id_prod, "product_db.csv" );

        loading_test( log_id, "01", "broken_permission_db_01.csv", & prod_db );
        loading_test( log_id, "02", "broken_permission_db_02.csv", & prod_db  );

        perm_db.init( log_id, "permission_db.csv", & prod_db );

        test_03( perm_db );
        test_04( perm_db );
        test_05( perm_db );

        return EXIT_SUCCESS;
    }
    catch( std::exception & e )
    {
        std::cout << "exception: " << e.what() << std::endl;

        return EXIT_FAILURE;
    }
}
