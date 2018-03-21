/*

String Helper. Provides to_string() function.

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

// $Revision: 8790 $ $Date:: 2018-03-20 #$ $Author: serge $

#include "str_helper.h"             // self

#include <sstream>                  // std::ostringstream

#include "utils/to_string_t.h"      // to_string()
#include "lang_tools/str_helper.h"  // to_string()

namespace permission_db
{

std::ostream & StrHelper::write( std::ostream & os, const Permission & l )
{
    os << "prod ids: " << utils::to_string( l.product_ids ) << " ";

    return os;
}

std::ostream & StrHelper::write( std::ostream & os, const RequestParams & l )
{
    os << "template id: " << l.template_id << " lang: " << lang_tools::to_string( l.lang );

    return os;
}

std::string StrHelper::to_string( const Permission & l )
{
    std::stringstream os;

    write( os, l );

    return os.str();
}

std::string StrHelper::to_string( const RequestParams & l )
{
    std::stringstream os;

    write( os, l );

    return os.str();
}

} // namespace permission_db
