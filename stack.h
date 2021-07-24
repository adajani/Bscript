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

/*@file stack.h
* @author Ahmad Dajani <eng.adajani@gmail.com>
* @date 24 July 2021
* @brief Integer based stack for general usage header file
*/

#ifndef __STACK_H
#define __STACK_H
    #define STACK_DEBUG
    #define STACK_SIZE 512

    void initialize_stack();
    int stack_is_empty();
    int stack_peek();
    int stack_pop();
    void stack_push(int value);

    #ifdef STACK_DEBUG
    void stack_display();
    #endif
#endif // __STACK_H
