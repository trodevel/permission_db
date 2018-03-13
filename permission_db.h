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

// $Revision: 8747 $ $Date:: 2018-03-12 #$ $Author: serge $

#ifndef LIB_PERMISSION_DB__PERMISSION_DB_H
#define LIB_PERMISSION_DB__PERMISSION_DB_H

#include <set>              // std::set
#include <vector>           // std::vector
#include <mutex>            // std::mutex

#include "product_db.h"     // ProductDB
#include "status.h"         // Status


namespace permission_db
{

class PermissionDb
{
public:
    PermissionDb();

    bool init(
            uint32_t            log_id,
            const std::string   & permission_db,
            const std::string   & product_db );

    bool is_allowed(
            user_id_t           user_id,
            template_id_t       template_id,
            lang_tools::lang_e  lang ) const;

private:

    typedef std::map<user_id_t,std::set<product_id_t>>  MapUserIdToProductIdSet;

private:


private:
    mutable std::mutex      mutex_;

    uint32_t                log_id_;

    MapUserIdToProductIdSet map_user_id_to_product_ids_;    // map: user id --> list of contact ids
};

} // namespace permission_db

#endif // LIB_PERMISSION_DB__PERMISSION_DB_H
