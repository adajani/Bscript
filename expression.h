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

/*@file expression.h
* @author Ahmad Dajani <eng.adajani@gmail.com>
* @date 24 July 2021
* @brief Expression evaluation header file
*/

#ifndef __EXPRESSION_H
#define __EXPRESSION_H
    int calculate(char *expression);
    static char *infix_to_postfix(char *expression);
    static int evaluate_postfix(char *postfix);
    static int is_operand(char ch);
    static int operator_precedence(char ch);
#endif // __EXPRESSION_H
