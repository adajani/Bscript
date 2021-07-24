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

/*@file basic.c
* @author Ahmad Dajani <eng.adajani@gmail.com>
* @date 24 July 2021
* @brief Basic language definitions source file
*/

#include <stdio.h> /* printf */
#include <ctype.h> /* tolower */
# include <strings.h> /* strcasecmp */
#include "basic.h"
#include "lexical.h"
#include "expression.h" /* calculate */

static int variables[VARIABLES_COUNT] = {0};

/* Bscript keyword lookup table
   Commands must be entered lowercase in this table.
*/
static struct Keyword keywords_table[] = {
    {"print" , KEYWORD_PRINT},
    {"input" , KEYWORD_INPUT},
    {"if"    , KEYWORD_IF},
    {"then"  , KEYWORD_THEN},
    {"for"   , KEYWORD_FOR},
    {"to"    , KEYWORD_TO},
    {"next"  , KEYWORD_NEXT},
    {"goto"  , KEYWORD_GOTO},
    {"gosub" , KEYWORD_GOSUB},
    {"return", KEYWORD_RETURN},
    {"end"   , KEYWORD_END},
    {""      , KEYWORD_END}  /* end of table */
};

static struct Label label_table[LABEL_COUNT];
static struct For_stack for_stack[FOR_STACK_SIZE]; /* stack for FOR/NEXT loop */
static char *gosub_stack[GOSUB_STACK_SIZE];	/* stack for gosub */

//WIP
int ftos;  /* index to top of FOR stack */
int gtos;  /* index to top of GOSUB stack */

int keyword_look_up(char *input_keyword) {
    register unsigned int keyword_index;
    char *input_keyword_pointer;

    input_keyword_pointer = input_keyword;

    /* convert to lowercase */
    while(*input_keyword_pointer){
        *input_keyword_pointer = tolower(*input_keyword_pointer);
        input_keyword_pointer++;
    }

    /* see if token is in table */
    for(keyword_index=0; strcmp((char*)&keywords_table[keyword_index].name, "") != 0; keyword_index++) {
      if(!strcasecmp((char*)&keywords_table[keyword_index].name, input_keyword)) {
        return keywords_table[keyword_index].token;
      }
    }

    return KEYWORD_UNKNOWN;
}

/* Find the value of a variable. */
int get_variable(char variable) {
    if(!isalpha(variable)){
        print_error(NOT_A_VARIABLE);
    }
    return variables[toupper(variable) - 'A'];
}

/* display an error message */
void print_error(enum BscriptError error) {
    static char *error_message[]= {
        "Syntax error",
        "Unmatched parentheses",
        "No expression present",
        "Equals sign expected",
        "Not a variable",
        "Label table full",
        "Duplicate label",
        "Undefined label",
        "THEN expected",
        "TO expected",
        "Too many nested FOR loops",
        "NEXT without FOR",
        "Too many nested GOSUBs",
        "RETURN without GOSUB",
    };
    printf("Error: %s\n", error_message[error]);
}

void execute_command(char *command) {
    switch(keyword_look_up(command)) {
        case KEYWORD_PRINT:
            printf("print keyword\n");
            break;

        case KEYWORD_UNKNOWN:
            printf("unkown keyword %s\n", command);
            break;
    }
}

int evaluate_expression() {
    char *expression = NULL;
    struct Parser_result *parser;
    printf("evaluate_expression: start\n");
    while(1) {
        parser = get_token();
        if(!expression) { /* expression pointer, relative to */
            expression = parser->token;
        }
        if(parser->type == LEXICAL_FINISHED || parser->type == LEXICAL_EOL) {
            *parser->token = '\0';
            break;
        }
    }
    printf("evaluate_expression: end\n");
    printf("evaluate_expression: %s\n", expression);

    return calculate(expression);
}

void variable_assignment(char *variable) {
    int variable_name;
    struct Parser_result *parser;

    variable_name = toupper(*variable) - 'A';

    /* get the equals sign */
    parser = get_token();
    if(*parser->token != '=') {
        print_error(EQUALS_SIGN_EXPECTED);
        return;
    }

    /* assign the value */
    variables[variable_name] = evaluate_expression();
}

void bscript_execute(char *bscript) {
    int finish = 0;
    struct Parser_result *parser;
    initialize_lexical(bscript);

    while( !finish ) {
        parser = get_token();
        switch(parser->type) {
            case LEXICAL_FINISHED:
                finish = 1;
                printf("finish\n");
                break;

            case LEXICAL_VARIABLE:
                variable_assignment(parser->token);
                break;

            case LEXICAL_STRING:
                execute_command(parser->token);
                break;

            default:
                    printf("unkown token %s\n", parser->token);
        }
    }
}
