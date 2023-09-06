#ifndef EXECUTE_H
#define EXECUTE_H

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include<libgen.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datas.h"


enum EXEC_RETURN_VAL{
    EXEC_SUCCESS,
    EXEC_ERROR
};

int judge_exit();
void judge_pwd(token_t* token);
int judge_cd();
enum EXEC_RETURN_VAL execute();
void error_handler(errors_t error, char *content);
//int savefd1, savefd2;

extern pid_t pid_first;
extern char path_stored[512];

#endif // EXECUTE_H
