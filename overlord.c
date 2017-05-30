#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#define CTL_COUNT 3

struct module{//connection to another process w/ respect to current
  pid_t pid;//process communicated with
  char* file;
};

struct module branch(){
  struct module m;
  char * args[] = {"necromancer.out", NULL, NULL};
  switch(m.pid = fork()){
    case -1:
      perror("fork failed");
      return m;//-1
    case 0:
      //child
      args[1] = (char*) malloc(sizeof(char) * 15);
      sprintf(args[1], "%d", getppid());//pass this pid to child
      if(execvp(".//necromancer.out", args) < 0){
        free(args[1]);
        perror("exec failed");
        exit(1);
      }
    default:
      m.file = (char*)malloc(sizeof(char) * 60);
      sprintf(m.file, "%d.p", getpid());//file to save into
      return m;
     // while(waitpid(pid, &status, WNOHANG) == 0); 
  }

  return m; 
}

int main(int argc, char** argv){
  struct module ccs[CTL_COUNT];
  int status;
  int i;
  int count = 0;
  char readbuf[256];//buffer for storing lines
  char* buffer;
  size_t buffer_size = 0, len = 0;
  FILE *fp, *fp2, *log;
  //readbuf = (char*) malloc(sizeof(char) * 256);
  fp = fopen("master.cmd", "wb+");//create files to write to
  fclose(fp);
  log = fopen("master.log", "wb+");
 
  for(i = 0; i < CTL_COUNT; ++i){
    ccs[i] = branch();
    if(ccs[i].pid > 0){
      ++count;
    }
  }

  for(i = 0; count > 0; ++i){//check status of each control center
    if(ccs[i].pid > 0){
      if(waitpid(ccs[i].pid, &status, WNOHANG) != 0){
        ccs[i].pid = 0;
        --count;
      }
      //printf("running %d\n", i);

      fp = fopen("./master.cmd", "r");
      while((len = getline(&readbuf, &buffer_size, fp)) != -1){//process commands
        readbuf[len + 1] = '\0';
        printf(readbuf);
        fputs(readbuf, log);
        fputs("\n", log);
        buffer = strtok(readbuf, " ");
        buffer = strtok(NULL, " ");
        //do stuff here
        //write communicate with other processes
      }
      //printf("length %d\n", len);
      fclose(fp);
      fp = fopen("./master.cmd", "w");
      fclose(fp);

      if(i == CTL_COUNT - 1){//loop back around
        i = -1;
      }
    }//while still have active cc
  }

  //printf("%d\n", getpid());
  
  fclose(log);
  return 0;
}

