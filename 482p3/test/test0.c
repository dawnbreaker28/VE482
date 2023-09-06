#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <lib.h>
#include <stdio.h>
#include "time.h"

int main(int argc, char **argv){
  pid_t pid[5];
  nice(-15);
  printf("Start testing\n");
  for(int i=0;i<5;i++){
    pid[i] = fork();
    if(pid[i]==0){
      int cnt = 0;
      pid_t pid = getpid();
      int time_begin, time_end, time_;
      nice(5 - i);
      time_begin = time(NULL);
        while(cnt < 50000){
          float c = 0;
          for (long j = 0; j < 10000; ++j) {
    		c += 98765.4321 / 654.321;
    		c -= 98765.4321 / 654.321;
    		c += 98765.4321 / 654.321;
    		c -= 98765.4321 / 654.321;
  	  }
          cnt++;
        }
      time_end = time(NULL);
      time_ =  (end - time_begin);
      printf("Sub-process %d takes %d seconds\n", i, time_);
      return 0;
    }
  }

  for(i=0;i<5;i++){
    waitpid(pid[i],NULL,0);
  }
  return 0;
}
