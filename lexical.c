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

/*@file lexical.c
* @author Ahmad Dajani <eng.adajani@gmail.com>
* @date 24 July 2021
* @brief Lexical source file
*/

#include <stdlib.h>  /* NULL */
#include <string.h> /* strchr */
#include <ctype.h> /* isdigit*/
#include "lexical.h"

static char token[MAX_TOKEN_LENGTH];
static char *user_program;

void initialize_lexical(char *programPointer) {
    user_program = programPointer;
}

/* Get a token. */
struct Parser_result *get_token() {
    /* reset the token index */
    char *token_pointer = token;
    static struct Parser_result parser_result = {.token=NULL,
                                                 .type=LEXICAL_UNKNOWN};

    /* skip over white space */
    while(is_white_space(*user_program)) {
        ++user_program;
    }

    /* end of file */
    if(*user_program=='\0') {
        parser_result.token = '\0';
        parser_result.type = LEXICAL_FINISHED;
        return &parser_result;
    }

    /* delimiter */
    if(is_delimiter(*user_program)){
        if(*user_program=='\n') {
            parser_result.type = LEXICAL_EOL;
        } else {
            parser_result.type = LEXICAL_DELIMITER;
        }

        *(token_pointer  ) = *user_program;
        *(token_pointer+1) = '\0';
        parser_result.token = token;

        user_program++; /* advance to next position */
        return &parser_result;
    }

    /* quoted string */
    if(*user_program=='"') {
        user_program++; /* +1 skip first double quote */
        while(*user_program!='"'&& *user_program!='\n') {
          *token_pointer++ = *user_program++;
        }
        *token_pointer ='\0';
        if(*user_program == '\n' || *user_program != '"') {
            parser_result.token = '\0';
            parser_result.type = LEXICAL_ERROR;
            return &parser_result;
        }
        parser_result.token = token;
        parser_result.type = LEXICAL_QUOTE;
        user_program ++;  /* +1 second first double quote */
        return &parser_result;
    }

    /* number */
    if(isdigit(*user_program)) {
        while(!is_delimiter(*user_program)) {
          *token_pointer++ = *user_program++;
        }
        *token_pointer = '\0';
        parser_result.token = token;
        parser_result.type = LEXICAL_NUMBER;
        return &parser_result;
    }

    /* variable or command */
    if(isalpha(*user_program)) {
        while(!is_delimiter(*user_program)){
          *token_pointer++ = *user_program++;
        }
        *token_pointer = '\0';

        /* see if a string is a command or a variable */
        if(strlen(token) == 1) { /* we have only one char var */
            parser_result.token = token;
            parser_result.type = LEXICAL_VARIABLE;
            return &parser_result;
        }
        else {
            parser_result.token = token;
            parser_result.type = LEXICAL_STRING;
            return &parser_result;
        }
    }

    /* Unknown token */
    parser_result.token = token;
    parser_result.type = LEXICAL_UNKNOWN;
    return &parser_result;
}

/* Return true if character is a delimiter. */
int is_delimiter(char character) {
    if(strchr(" ;,+-<>/*%^=()|&~", character) ||
       character==9 ||
       character=='\n' ||
       character==0) {
        return 1;
    }
    return 0;
}

/* Return 1 if character is space or tab. */
int is_white_space(char character) {
    if(character==' ' || character=='\t') {
        return 1;
    }
    return 0;
}
