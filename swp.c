#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <unistd.h>

#define SWAP_IO 309

int aredigits(char *arg);

int main(int argc, char *argv[]){
  /* variable declaration */
  int swp_result;
  int pid_A,pid_B,fd_A,fd_B;

  /* check argument */
  if(argc == 4){
    if( !(aredigits(argv[1])) && aredigits(argv[2]) && aredigits(argv[3])){
      if(!(strcmp(argv[1],"-a"))){
	pid_A = atoi(argv[2]);
	fd_A  = -1;
	pid_B = atoi(argv[3]);
	fd_B  = -1;
      }else{
	fprintf(stderr,"Error! No such option\n");
	return 0;
      }
    }else{
      fprintf(stderr,"Error! Argument is not right\n");
      return 0;
    }
  }else if(argc == 5){
    if(aredigits(argv[1]) && aredigits(argv[2]) && aredigits(argv[3]) && aredigits(argv[4])){
      pid_A = atoi(argv[1]);
      fd_A  = atoi(argv[2]);
      pid_B = atoi(argv[3]);
      fd_B  = atoi(argv[4]);
    }else{
      fprintf(stderr,"Error! Argument is not right\n");
      return 0;
    }
  }else{
    fprintf(stderr,"Error! Number of arg is not right\n");
    return 0;
  }
  
  /* swap */
  swp_result = syscall(SWAP_IO, pid_A, fd_A, pid_B, fd_B);

  /* result message */
  if(swp_result == 0){
    printf("swp success\n");
  }else if(swp_result == 2){
    fprintf(stderr,"Error! No such process or file description\n");
  }else{
    fprintf(stderr,"Error! swp failed\n");
  }
  
  return 0;
}

/* function of isdisit for every digit */
int aredigits(char *arg){
  int i;
  int len = strlen(arg);
  for(i = 0; i < len ; i++){
    if(isdigit(arg[i]) == 0){
      return 0;
    }
  }
  return 1;
}
