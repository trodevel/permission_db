/*

Permission DB - Types.

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

// $Revision: 8740 $ $Date:: 2018-03-02 #$ $Author: serge $

#ifndef LIB_PERMISSION_DB__TYPES_H
#define LIB_PERMISSION_DB__TYPES_H

#include <cstdint>          // std::uint32_t

namespace permission_db
{

typedef uint32_t user_id_t;
typedef uint32_t product_id_t;
typedef uint32_t category_id_t;
typedef uint32_t template_id_t;

} // namespace permission_db

#endif // LIB_PERMISSION_DB__TYPES_H
