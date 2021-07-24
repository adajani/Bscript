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

/*@file stack.c
* @author Ahmad Dajani <eng.adajani@gmail.com>
* @date 24 July 2021
* @brief Integer based stack for general usage source file
*/

#include <stdio.h>
#include "stack.h"

static int stack[STACK_SIZE] = {0};
static int top = -1;

void initialize_stack() {
    top = -1;
}

int stack_is_empty() {
    return top == -1;
}

void stack_push(int value) {
    if(top == STACK_SIZE) {
        return; /* stack is full */
    }
    stack[++top] = value;
}

int stack_pop() {
    if(top == -1) {
        return -1; /* stack is empty */
    }
    return stack[top--];
}

int stack_peek(){
    if(top == -1) {
        return -1; /* stack is empty */
    }
    return stack[top];
}

#ifdef STACK_DEBUG
void stack_display() {
    register int index;
    for(int index=top ; index > -1; index--) {
        printf("%d ",stack[index]);
    }
    printf("\n");
}
#endif
