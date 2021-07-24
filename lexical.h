/***************************************************************************
* Copyright (C) 2021 by Ahmad Dajani                                       *
*                                                                          *
* This file is part of Bscript.                                            *
*                                                                          *
* Bscript is free software: you can redistribute it and/or modify it       *
* under the terms of the GNU Lesser General Public License as published    *
* by the Free Software Foundation, either version 3 of the License, or     *
* (at your option) any later version.                                      *
*                                                                          *
* Bscript is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY* without even the implied warranty of           *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
* GNU Lesser General Public License for more details.                      *
*                                                                          *
* You should have received a copy of the GNU Lesser General Public         *
* License along with Bscript.  If not, see <http://www.gnu.org/licenses/>. *
****************************************************************************/

/*@file lexical.h
* @author Ahmad Dajani <eng.adajani@gmail.com>
* @date 24 July 2021
* @brief Lexical header file
*/

#ifndef __LEXICAL_H
    #define __LEXICAL_H

    #define MAX_TOKEN_LENGTH 80

    enum Lexical_types {
        LEXICAL_UNKNOWN,
        LEXICAL_ERROR, /* double quote without closing, e.g "asd */
        LEXICAL_DELIMITER,
        LEXICAL_VARIABLE,
        LEXICAL_NUMBER,
        LEXICAL_KEYWORD,
        LEXICAL_STRING,
        LEXICAL_QUOTE,
        LEXICAL_FINISHED,
        LEXICAL_EOL,
    };

    struct Parser_result {
        char *token;
        enum Lexical_types type;
    };

    int is_white_space(char character);
    int is_delimiter(char character);
    struct Parser_result *get_token();
    void initialize_lexical(char *programPointer);
#endif // __LEXICAL_H
