//
// Created by Dawnbreaker on 2022/9/29.
//
#include "parse.h"

void error_handler_fromparse(errors_t error, char content){
    switch(error){
        case ERROR_DUP_INPUT: {
            printf("error: duplicated input redirection\n");
            break;
        }
            
        case ERROR_DUP_OUTPUT: {
            printf("error: duplicated output redirection\n");
            break;
        }
        case ERROR_SYNTAX: {
            printf("syntax error near unexpected token `%c\'\n", content);
            break;
        }
        case ERROR_MISSING_PROGRAM: {
            printf("error: missing program\n");
        }
        default:{
            break;
        }

    }
}

enum PARSE_RETURN_VAL parse(char buf[], char *nextBuf){
    size_t length = strlen(nextBuf);
    // token_t token = {0, {NULL}};
    cmd.numbers = 0;
    size_t position_input = 0;
    size_t position_output = 0;
    // size_t position_pipe = 0;
    bool has_content = false;
    int begin_special_char = 0; // o for not begin, 1 for |, 2 for general
    if (strcmp(nextBuf, "exit\n")==0){
        return PARSE_EXIT;
    }else{
        parser_t parser = {0, false, false, false, 0, {0}};
        for (size_t i = 0; i < 1024; i++){
            if (i == length){
                free(cmd.tokens[cmd.numbers].argv[cmd.tokens[cmd.numbers].argc]);
                cmd.tokens[cmd.numbers].argv[cmd.tokens[cmd.numbers].argc] = NULL;
                break;
            }else{ //not empty
                if (parser.buffer_len==0){
                    // no buffer
                    if (strchr(" <>|\n\t", buf[i])!=NULL){
                        if (strchr(" \t", buf[i]) != NULL) continue;
                        if (strchr("<>|", buf[i]) != NULL) {
                            if(!has_content&&begin_special_char!=0){
                                if(begin_special_char==1&&buf[i]=='|'){
                                    error_handler_fromparse(ERROR_MISSING_PROGRAM, buf[i]);
                                    return PARSE_SKIP;
                                }
                                if(!(position_output!=0&&i==position_output+1&&buf[i]=='>')){
                                    error_handler_fromparse(ERROR_SYNTAX, buf[i]);
                                    return PARSE_SKIP;
                                }
                            }
                            if(buf[i] == '<') {
                                parser.is_input_file = true;
                                if (position_input!=0){
                                    error_handler_fromparse(ERROR_DUP_INPUT, buf[i]);
                                    return PARSE_SKIP;
                                }
                                position_input = i;
                            }

                            if(buf[i] == '>'){
                                if (position_output!=0){
                                    if (position_output+1!=i){
                                        error_handler_fromparse(ERROR_DUP_OUTPUT, buf[i]);
                                        return PARSE_SKIP;
                                    }
                                }
                                position_output = i;
                                if (parser.is_output_file == true){
                                    parser.output_mode = 2;
                                }else{
                                    parser.is_output_file = true;
                                }
                            }
                            if(buf[i] == '|'){
                                position_input=i;
                                if (position_output!=0){
                                    error_handler_fromparse(ERROR_DUP_OUTPUT, buf[i]);
                                    return PARSE_SKIP;
                                }
                                cmd.numbers++;
                            }
                            has_content= false;
                            if(buf[i]=='|'){
                                begin_special_char = 1;
                            }else{
                                begin_special_char = 2;
                            }
                        }
                    }else{
                        // printf("%c", buf[i]);
                        // fflush(stdout);
                        parser.buffer[parser.buffer_len] = buf[i];
                        parser.buffer_len++;
                    }
                }
                else
                { //has buffer
                    // printf("c");
                    // fflush(stdout);
                    has_content = true;
                    begin_special_char = 0;
                    if (strchr(" <>|\n\t", buf[i])==NULL){
                        // printf("%c", buf[i]);
                        // fflush(stdout);
                        parser.buffer[parser.buffer_len] = buf[i];
                        parser.buffer_len++;
                        continue;
                    }else{ // qingsuan
                        char tok[BUFFER_SIZE];
                        char *ptr = tok;
                        strcpy(ptr, parser.buffer);
                        parser.buffer_len = 0;
                        memset(parser.buffer, 0, BUFFER_SIZE);
                        
                        if(parser.is_output_file == true){
                            if(parser.output_mode == 2){
                                cmd.output=true;
                                cmd.append=true;
                                strcpy(cmd.output_file, ptr);
                            }else{
                                cmd.output=true;
                                strcpy(cmd.output_file, ptr);
                            }
                            parser.is_output_file = false;
                            if(buf[i] == '<') parser.is_input_file = true;
                            if (buf[i]=='\n') cmd.numbers++;
                            continue;
                        }
                        if(parser.is_input_file == true){
                            cmd.input = true;
                            strcpy(cmd.input_file, ptr);
                            parser.is_input_file = false;
                            if(buf[i] == '>') parser.is_output_file = true;
                            if (buf[i]=='\n') cmd.numbers++;
                            continue;
                        }    
                        if (strchr(" \t\n", buf[i]) != NULL){
                            cmd.tokens[cmd.numbers].argv[cmd.tokens[cmd.numbers].argc] = malloc(sizeof(char)*BUFFER_SIZE);
                            strcpy(cmd.tokens[cmd.numbers].argv[cmd.tokens[cmd.numbers].argc], ptr);
                            cmd.tokens[cmd.numbers].argc++;
                            if (buf[i]=='\n')
                            {
                                cmd.numbers++;
                            }
                            
                            continue;

                            // printf("%s\n", cmd.argv[*cmd.argc]);
                            // fflush(stdout);
                        }
                        if (strchr("<>|", buf[i]) != NULL) {
                            if(buf[i] == '<'){
                                parser.is_input_file = true;
                                cmd.tokens[cmd.numbers].argv[cmd.tokens[cmd.numbers].argc] = malloc(sizeof(char)*BUFFER_SIZE);
                                strcpy(cmd.tokens[cmd.numbers].argv[cmd.tokens[cmd.numbers].argc], ptr);
                                cmd.tokens[cmd.numbers].argc++;
                                continue;
                            } 
                            if(buf[i] == '>'){
                                parser.is_output_file = true;
                                parser.output_mode = 1;
                                cmd.tokens[cmd.numbers].argv[cmd.tokens[cmd.numbers].argc] = malloc(sizeof(char)*BUFFER_SIZE);
                                strcpy(cmd.tokens[cmd.numbers].argv[cmd.tokens[cmd.numbers].argc], ptr);
                                cmd.tokens[cmd.numbers].argc++;
                                continue;
                            }
                        }
                    }
                }
            }
        }
        for (size_t i = 0; i < cmd.numbers; i++) {
            if (cmd.tokens[i].argc == 0) {
                error_handler_fromparse(ERROR_MISSING_PROGRAM, 'a');
                return PARSE_SKIP;
            }
        }
        return PARSE_SUCCESS;
    }
}
        // nextBuf[strlen(nextBuf)-1] = '\0';
        // char *tok = strtok(nextBuf, " ");
        // cmd.argc = 0;
        // if (tok == NULL){
        //     return PARSE_SKIP; //this code could be wrong
        // }else{
        //     cmd.argv[0]=tok;
        //     int in_redirection = 0;
        //     int out_redirection = 0;
        //     while (tok!=NULL)
        //     {
        //         tok = strtok(NULL, " ");
        //         if (tok == NULL){
        //             cmd.argc++;
        //             cmd.argv[cmd.argc] = NULL;
        //             break;
        //         }
        //         cmd.argc++;
        //         if (strcmp(tok,">")==0)
        //         {
        //             out_redirection = 1;
        //             continue;
        //         }
        //         else if (strcmp(tok,">>")==0)
        //         {   
        //             out_redirection = 2;
        //             continue;
        //         }
        //         else if (strcmp(tok,"<")==0)
        //         {
        //             in_redirection = 1;
        //             continue;
        //         }
        //         else{
        //             if (in_redirection!=0){
        //                 *cmd.input_file = open(tok, O_RDONLY, 0666);
        //                 in_redirection=0;
        //                 continue;
        //             }
        //             else if (out_redirection!=0){
        //                 if(out_redirection==1){ // > mode
        //                     *cmd.output_file = open(tok, O_WRONLY|O_CREAT|O_TRUNC, 0666);
        //                 }else{ // >> mode
        //                     *cmd.output_file = open(tok, O_WRONLY|O_CREAT|O_APPEND, 0666);
        //                 }
        //                 out_redirection=0;
        //                 continue;
        //             }
        //             else{
        //                 cmd.argv[cmd.argc]=tok;

        //             }
        //         }               
        //     }     
        // }
