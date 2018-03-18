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

// $Revision: 8776 $ $Date:: 2018-03-16 #$ $Author: serge $

#ifndef LIB_PERMISSION_DB__PERMISSION_DB_H
#define LIB_PERMISSION_DB__PERMISSION_DB_H

#include <vector>           // std::vector
#include <mutex>            // std::mutex

#include "product_db.h"     // ProductDb
#include "permission.h"     // Permission

namespace permission_db
{

class PermissionDb
{
public:
    PermissionDb();

    bool init(
            uint32_t                    log_id,
            const std::string           & permission_db,
            const product_db::ProductDb * product_db );

    bool is_allowed(
            user_id_t           user_id,
            template_id_t       template_id,
            lang_tools::lang_e  lang ) const;

private:

    typedef std::map<user_id_t,Permission>  MapUserIdToPermission;

    struct FlatPermission
    {
        user_id_t       user_id;
        Permission      permission;
    };

private:

    void parse_lines( const std::vector<std::string> & lines );

    void process_line( const std::string & line );
    void process_line( const FlatPermission & p );

    FlatPermission to_flat_permission( const std::string & l );

    Permission to_permission( const std::vector<std::string> & elems );

private:
    mutable std::mutex      mutex_;

    uint32_t                log_id_;

    MapUserIdToPermission   map_user_id_to_permission_;    // map: user id --> list of contact ids

    const product_db::ProductDb     * product_db_;
};

} // namespace permission_db

#endif // LIB_PERMISSION_DB__PERMISSION_DB_H
