#ifndef PARSER_H
#define PARSER_H

#include <sys/types.h>    
#include <sys/stat.h>    
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datas.h"


enum PARSE_RETURN_VAL{
    PARSE_SUCCESS,
    PARSE_EXIT,
    PARSE_SKIP,
    PARSE_CONTINUE
};

enum PARSE_RETURN_VAL parse(char buf[], char *nextBuf);

#endif  // PARSER_H
