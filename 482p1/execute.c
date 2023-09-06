#include "execute.h"

cmd_t cmd;
pid_t pid_first;
char path_stored[512];

int judge_exit(){
    if (cmd.numbers == 1 && cmd.tokens[0].argc >= 1 &&
        (strcmp(cmd.tokens[0].argv[0], "exit") == 0 ||
        strcmp(cmd.tokens[0].argv[0], "quit") == 0 ||
        strcmp(cmd.tokens[0].argv[0], "q") == 0)){
            return 1;
        }     
    return -1;
}

void input_redirect(){
    // if (cmd.input_file!=-1){
    //     //save_fd1 = dup(0);
    //     dup2(cmd.input_file,fileno(stdin));           
    // }
    if(cmd.input){
        int fd = open(cmd.input_file, O_RDONLY, 0666);
        if (fd < 0){
            error_handler(ERROR_NON_EXIST_FILE, cmd.input_file);
        }
        dup2(fd,fileno(stdin));
    }
}

void output_redirect(){
    // if (cmd.output_file!=-1){
    //     //save_fd2 =dup(1);
    //     dup2(cmd.output_file,fileno(stdout));
    // }
    if(cmd.output){
        if(cmd.append){
            int fd = open(cmd.output_file, O_WRONLY|O_CREAT|O_APPEND, 0666);
            if (fd < 0){
                error_handler(ERROR_OPEN, cmd.output_file);
            }
            dup2(fd,fileno(stdout));
        }else{
            int fd = open(cmd.output_file, O_WRONLY|O_CREAT|O_TRUNC, 0666);
            if (fd < 0){
                error_handler(ERROR_OPEN, cmd.output_file);
            }
            dup2(fd,fileno(stdout));
        }
    }
}

void error_handler(errors_t error, char *content){
    switch(error) {
        case ERROR_NON_EXIST_PROGRAM: {
            fputs(content, stderr);
            fputs(": command not found\n", stderr);
            break;
        }
        case ERROR_NON_EXIST_FILE: {
            fputs(content, stderr);
            fputs(": No such file or directory\n", stderr);
            break;
        }
        case ERROR_OPEN: {
            fputs(content, stderr);
            fputs(": Permission denied\n", stderr);
            break;
        }
        case ERROR_MISSING_PROGRAM:{
            printf("missing program\n");
            break;
        }
        case ERROR_CD: {
            printf("non-existing: No such file or directory\n");
            break;
        }
        default:{
            break;
        }
    }
    if (error == ERROR_CD){
        return;
    }
    exit(1);
}

void judge_pwd(token_t* token){
    if(token->argc == 1 && strcmp(token->argv[0], "pwd")==0){
        char pwd[256]={0};
        if (getcwd(pwd,256)!=NULL){
            printf("%s\n",pwd);
            fflush(stdout);
            // return 1;
            exit(0);
        }
        exit(1);       
    }
    // return -1;
}

int judge_cd(){
    if (cmd.numbers == 1 && strcmp(cmd.tokens[0].argv[0], "cd")==0 && 
                cmd.tokens[0].argc >= 1){
        char path[512] = {0};
        getcwd(path, 512);

        if (cmd.tokens[0].argc == 1){ // cd
            if (chdir(getenv("HOME")) == 0) strcpy(path_stored, path);
        }else if (strcmp(cmd.tokens[0].argv[1], "~") == 0){ // cd ~
            if (chdir(getenv("HOME")) == 0) strcpy(path_stored, path);
        }else if (strcmp(cmd.tokens[0].argv[1], "-") == 0){ // cd -
            if (chdir(path_stored) == 0){
                printf("%s\n", path_stored);
                fflush(stdout);
                strcpy(path_stored, path);
            }
        }else if (strcmp(cmd.tokens[0].argv[1], ".") == 0){ // cd .
            return 1;
        }else if (strcmp(cmd.tokens[0].argv[1], "..") == 0){  // cd ..
            char *path_parent = strdup(path); 
            if (chdir(dirname(path_parent)) == 0) strcpy(path_stored, path);
            if (path_parent!=NULL){
                free(path_parent);
            }
        }else{ // complete path
            if (chdir(cmd.tokens[0].argv[1]) == 0){
                strcpy(path_stored, path);
            }else{
                error_handler(ERROR_CD, "abc");
                return 1;
            }
        }
        return 1;
    }
    return -1;
}


enum EXEC_RETURN_VAL execute(){
    int pipe_fd[512][2];
    int status = 0;
    // pid_t result;
    for (size_t i = 0; i < cmd.numbers; i++){
        if (cmd.numbers > 1 && i!=cmd.numbers-1){
            if (pipe(pipe_fd[i])==-1){
                perror("pipe");
                _exit(1);
            }
        }
        pid_t pid = fork();
        if (i==0){
            pid_first = pid;
        }
        if (pid < 0){
            printf("Failed to fork %d\n", pid);
        }else if (pid == 0){
            if (i==0){
                input_redirect();
            }
            if (cmd.numbers > 1 && i != 0) {
                close(pipe_fd[i - 1][1]);
                dup2(pipe_fd[i - 1][0], fileno(stdin));
            }
            if (cmd.numbers > 1 && i != cmd.numbers - 1) {
                close(pipe_fd[i][0]);
                dup2(pipe_fd[i][1], fileno(stdout));
            }
            if (i== cmd.numbers-1){
                output_redirect();
            }
            judge_pwd(&cmd.tokens[i]);
            // if (pwd_result!=1)
            // {
            if (execvp(cmd.tokens[i].argv[0], cmd.tokens[i].argv) < 0){
                error_handler(ERROR_NON_EXIST_PROGRAM, cmd.tokens[i].argv[0]);
            }
            // }
            
            
        }
        setpgid(pid, pid_first);
        if (i == 0){
            tcsetpgrp(fileno(stdin), pid_first);
        }
        if (cmd.numbers > 1 && i !=0){
            close(pipe_fd[i - 1][1]);
            close(pipe_fd[i - 1][0]);
        }
    }
    
    for (size_t i=0; i<cmd.numbers; i++){
        waitpid(-pid_first, &status, WUNTRACED);
    }
    tcsetpgrp(fileno(stdout), getpgrp());
    return EXEC_SUCCESS; 
}

            // if(fork()==0){
            //     int result = execvp(cmd.tokens[i].argv[0], cmd.tokens[i].argv);
            //     if (result == -1) { // -1 for error
            //         exit(1);
            //     }else{
            //         exit(2);
            //     }
            // }else{
            //     int cpid = wait(&status);
            //     cpid ++; // useless
            //     if (cmd.input_file!=-1||cmd.output_file!=-1){
            //         if(cmd.input_file!=-1){
            //             dup2(save_fd1, 0);
            //             close(save_fd1); 
            //         }
            //         if(cmd.output_file!=-1){
            //             dup2(save_fd2, 1);
            //             close(save_fd2); 
            //         }
                        
            //         cmd.input_file=-1;
            //         cmd.output_file=-1;
            //     }
            //     int high_8 = status >> 8;
            //     if (high_8 == 1) {
            //         return EXEC_ERROR; 
            //     }else{
            //         return EXEC_SUCCESS;
            //     }
            // }       
