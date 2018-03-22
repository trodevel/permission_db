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

// $Revision: 8808 $ $Date:: 2018-03-21 #$ $Author: serge $

#ifndef LIB_PERMISSION_DB__STR_HELPER_H
#define LIB_PERMISSION_DB__STR_HELPER_H

#include <string>

#include "request_params.h"     // RequestParams
#include "permission.h"         // Permission

namespace permission_db
{

class StrHelper
{
public:
    static std::ostream & write( std::ostream & os, const Permission & l );
    static std::ostream & write( std::ostream & os, const RequestParams & l );

    static std::string to_string( const Permission & l );
    static std::string to_string( const RequestParams & l );
};

} // namespace permission_db

inline std::ostream& operator<<( std::ostream& os, const permission_db::Permission & l )
{
    return permission_db::StrHelper::write( os, l );
}

inline std::ostream& operator<<( std::ostream& os, const permission_db::RequestParams & l )
{
    return permission_db::StrHelper::write( os, l );
}

#endif // LIB_PERMISSION_DB__STR_HELPER_H
