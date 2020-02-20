#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

#define SWAP_IO 309

int aredigits(char *arg);

int main(int argc, char *argv[]){
  /* variable declaration */
  int chg_result;
  int pid_A, fd_A, pid_B, fd_B;

  /* check argument */
  if(argc != 4){
    fprintf(stderr,"Error! Number of arg is not right\n");
    return 0;
  }

  if(!(aredigits(argv[1]) && aredigits(argv[2]))){
    fprintf(stderr,"Error! Argument is not right\n");
    return 0;
  }

  pid_A = atoi(argv[1]);
  fd_A = atoi(argv[2]);

  /* get pid */
  pid_B = getpid();

  /* open file */
  fd_B = open(argv[3],O_RDWR|O_CREAT,S_IREAD|S_IWRITE);
    
  if(fd_B == -1){
    fprintf(stderr,"Error! Open flie failed\n");
    return 0;
  }

  /* swap */
  chg_result = syscall(SWAP_IO, pid_A, fd_A, pid_B, fd_B);

  /* result message */
  if(chg_result == 0){
    printf("chg success\n");
  }else if(chg_result == 2){
    fprintf(stderr,"Error! No such process or file description\n");
  }else{
    fprintf(stderr,"Error! chg failed\n");
  }

  /* close file */
  close(fd_B);
  return 0;
}

/* function of isdigit for every disit */
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
