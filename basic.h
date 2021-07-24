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

/*@file basic.h
* @author Ahmad Dajani <eng.adajani@gmail.com>
* @date 24 July 2021
* @brief Basic language definitions header file
*/

#ifndef __BASIC_H
#define __BASIC_H
    #define TABLEN	8

    enum BscriptError {
        SYNTAX_ERROR = 0,
        UNMATCHED_PARENTHESES,
        NO_EXPRESSION,
        EQUALS_SIGN_EXPECTED,
        NOT_A_VARIABLE,
        LABEL_TABLE_FULL,
        DUPLICATE_LABEL,
        UNDEFINED_LABEL,
        THEN_EXPECTED,
        TO_EXPECTED,
        TOO_MANY_NESTED_FOR,
        NEXT_WITHOUT_FOR,
        TOO_MANY_NESTED_GOSUB,
        RETURN_WITHOUT_GOSUB,
    };
    void print_error(enum BscriptError error);

    /* 26 user variables, A-Z */
    #define VARIABLES_COUNT 26

    enum BscriptKeywords {
        KEYWORD_UNKNOWN = 0,
        KEYWORD_PRINT,
        KEYWORD_INPUT,
        KEYWORD_IF,
        KEYWORD_THEN,
        KEYWORD_FOR,
        KEYWORD_TO,
        KEYWORD_NEXT,
        KEYWORD_GOTO,
        KEYWORD_GOSUB,
        KEYWORD_RETURN,
        KEYWORD_END,
    };

    #define KEYWORD_LENGTH 8
    struct Keyword {
        unsigned char name[KEYWORD_LENGTH];
        unsigned char token;
    };

    #define LABEL_COUNT 100
    #define LABEL_LENGTH 20
    struct Label {
        char name[LABEL_LENGTH];
        char *location;  /* points to place to go in source file*/
    };

    #define GOSUB_STACK_SIZE 100

    #define FOR_STACK_SIZE 100
    struct For_stack {
        int variable; /* counter variable */
        int target;  /* target value */
        char *location;
    };

    int keyword_look_up(char *input_keyword);
    int get_variable(char variable);
    void print_error(enum BscriptError error);
    void bscript_execute(char *bscript);
    void execute_command(char *command);
    void variable_assignment(char *variable);
    int evaluate_expression();
#endif /* __BASIC_H */
