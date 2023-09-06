#include "main.h"

enum READ_RETURN_VAL{
    READ_SUCCESS,
    READ_FAIL,
    READ_END,
};

volatile sig_atomic_t flag = 0;

void freeResource(){
    // TODO: free resources allocated
    // if (cmd.input_file!=NULL){
    //     free(cmd.input_file);
    // }
    // if (cmd.output_file!=NULL){
    //     free(cmd.output_file);
    // }
    
    for (size_t i = 0; i < cmd.numbers + 1; i++){
        for (size_t j = 0; j < cmd.tokens[i].argc + 1; j++){
            if(cmd.tokens[i].argv[j]!=NULL){
                free(cmd.tokens[i].argv[j]);
            }
        } 
    }   
}

static void my_handler(int sig){
    if (sig == SIGINT){
        flag = 1;
        printf("\n");
        printf("mumsh $ ");
        fflush(stdout);
    }
}

enum READ_RETURN_VAL readcmd(char *buf){
    if(fgets(buf, 1024, stdin)==NULL)
    {   
    // int c = buf[0];
    // if(c == EOF){
    //     printf("exit");
    //     fflush(stdout);
    //     freeResource();
    //     //  _exit(1);
    // }
    // printf("c");
    // fflush(stdout);
        return READ_END;
    }
    else
    {   
    // printf("d");
    // fflush(stdout);
        return READ_SUCCESS;
    }
    
}

void clear_cmd(){
    cmd.input=false;
    cmd.output=false;
    cmd.append=false;
    cmd.numbers=0;
    memset(cmd.tokens, 0, TOKEN_SIZE*sizeof(token_t));
    memset(cmd.input_file, 0, 32);
    memset(cmd.output_file, 0, 32);
}

int main() {
    signal(SIGINT, my_handler);

    while(1){
        if (flag == 0){
            printf("mumsh $ ");
            fflush(stdout);
        }
        clear_cmd();
        flag= 0;
        // cmd.input_file=malloc(sizeof(char)*32);
        // cmd.output_file=malloc(sizeof(char)*32);
        char buf[1024];
        char *nextBuf = buf;    
        enum READ_RETURN_VAL read_val = readcmd(nextBuf);
        // printf("a");
        // fflush(stdout);
        if(read_val == READ_END){            
            printf("exit\n");
            fflush(stdout);
            freeResource();
            return 0;
        }

        enum PARSE_RETURN_VAL parse_val = parse(buf, nextBuf);
        if (parse_val == PARSE_SKIP){
            freeResource();
            continue;
        }
        switch (parse_val) {
            case PARSE_EXIT:
                printf("exit\n");
                fflush(stdout);
                freeResource();
                return 0;  
            case PARSE_SKIP:
                break;
            case PARSE_CONTINUE:
                break;
            default:
                break;     
        }

        int exit_status = judge_exit();
        if(exit_status == 1){
            printf("exit\n");
            fflush(stdout);
            freeResource();
            return 0;
        }

        int cd_status = judge_cd();
        if(cd_status == 1){
            freeResource();
            continue;
        }

        // printf("%zu\n", cmd.numbers);
        // fflush(stdout);
        // for (size_t i = 0; i < cmd.numbers; i++)
        // {
        //     printf("%zu\n", cmd.tokens[i].argc);
        //     fflush(stdout);
        //     for (size_t j = 0; j < cmd.tokens[i].argc; j++)
        //     {
        //         printf("%s\n", cmd.tokens[i].argv[j]);
        //         fflush(stdout);
        //     }
            
        // }
        // printf("%s\n", cmd.input_file);
        // printf("%s\n", cmd.output_file);
        
        enum EXEC_RETURN_VAL exec_val = execute();
        switch (exec_val) {
            case EXEC_SUCCESS:
                break;
            default:
                break;
        }
        freeResource(); 
    }
     
    return 0;
}
