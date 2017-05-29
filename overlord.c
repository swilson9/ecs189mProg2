#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

pid_t branch(){
	pid_t pid
	int fd[2];
	char * const args[] = "necromancer.out", NULL);
	switch(pid = fork()){
		case -1:
			perror("fork failed");
			return -1;
		case 0:
			if(execvp("./necromancer.out",args) < 0){
				perror("exec failed");
				exit(1);

	return pid;

int main(int argc, char** argv){
	pid_t pid[3];
	int status;
	int count = 0;

	for(int i = 0; i < 3; i++){
		if(pid[i] = branch() > 0){
			++count;
		}
	}

	for(int i = 0; count > 0; ++i){
		if(pid[i] > 0){
			if(waitpid(pid[i], &status, WNOHANG) != 0){
				pid[i] = 0
			}
		}
	}

	printf("%d/n", getpid());
	
	return 0;
