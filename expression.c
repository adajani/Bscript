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

/*@file expression.c
* @author Ahmad Dajani <eng.adajani@gmail.com>
* @date 24 July 2021
* @brief Expression evaluation source file
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h> /* isdigit */
#include <stdlib.h>

#include "stack.h"
#include "basic.h" /* get_variable */
#include "expression.h"

static char buffer[80];

int calculate(char *expression) {
    char *postfix;
    postfix = infix_to_postfix(expression);
    if(!postfix) {
        //invalid expression
    }
    return evaluate_postfix(postfix);
}

// The main function that returns value of a given postfix expression
//char exp[] = "231*+9-"; = -4
//printf ("postfix evaluation: %d", evaluatePostfix(exp));
static int evaluate_postfix(char *postfix) { //note: expression length should be <= stack size , see stack.h
    register int index;
    int left_value, right_value;

    for(index=0; postfix[index]; ++index) {
        if(isdigit(postfix[index])) {
            stack_push(postfix[index] - '0');
        }
        else {
            int left_value = stack_pop();
            int right_value = stack_pop();
            switch(postfix[index]) {
                case '+': stack_push(left_value + right_value); break;
                case '-': stack_push(left_value - right_value); break;
                case '*': stack_push(left_value * right_value); break;
                case '/': stack_push(left_value / right_value); break; /* todo: check div by zero */
                //default: /* unknown operator */
            }
        }
    }
    return stack_pop(); /* answer */
}

static int is_operand(char ch) {
    return (ch >= 'a' && ch <= 'z') ||
           (ch >= 'A' && ch <= 'Z');
}

static int operator_precedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
                    return 1;

        case '*':
        case '/':
                    return 2;

        case '^':
                    return 3; // higher precedence
    }
    return -1;
}

//out: buffer
static char *infix_to_postfix(char *expression) {
    int expression_index;
    int buffer_index = -1;

    for (expression_index = 0; expression[expression_index] != '\0'; ++expression_index) {
        // If the scanned character is
        // an operand, add it to output.
        if (is_operand(expression[expression_index]))
            buffer[++buffer_index] = get_variable(expression[expression_index]);

        // If the scanned character is an
        // ‘(‘, push it to the stack.
        else if (expression[expression_index] == '(')
            stack_push(expression[expression_index]);

        // If the scanned character is an ‘)’,
        // pop and output from the stack
        // until an ‘(‘ is encountered.
        else if (expression[expression_index] == ')') {
            while(!stack_is_empty() && stack_peek() != '(') {
                buffer[++buffer_index] = stack_pop();
            }
            if(!stack_is_empty() && stack_peek() != '(') {
                return NULL; // invalid expression
            }
            else {
                stack_pop();
            }
        }
        else { // an operator is encountered
            while(!stack_is_empty() &&
                 operator_precedence(expression[expression_index]) <=
                 operator_precedence(stack_peek())) {
                buffer[++buffer_index] = stack_pop();
            }
            stack_push(expression[expression_index]);
        }

    }

    // pop all the operators from the stack
    while(!stack_is_empty()) {
        buffer[++buffer_index] = stack_pop();
    }

    buffer[++buffer_index] = '\0';
    return &buffer;
}
