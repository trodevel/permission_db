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

// $Revision: 8788 $ $Date:: 2018-03-19 #$ $Author: serge $

#ifndef LIB_PERMISSION_DB__REQUEST_PARAMS_H
#define LIB_PERMISSION_DB__REQUEST_PARAMS_H

#include "lang_tools/language_enum.h"   // lang_tools::lang_e
#include "product_db/types.h"           // template_id_t

namespace permission_db
{

struct RequestParams
{
    product_db::template_id_t   template_id;
    lang_tools::lang_e          lang;
};

} // namespace permission_db

#endif // LIB_PERMISSION_DB__REQUEST_PARAMS_H
