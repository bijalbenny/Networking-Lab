#include <stdio.h>
#include <unistd.h>
#include <wait.h>
void main() {
 pid_t id;
 id = fork();
 if(id==0)
 {
 printf("Child Process\n");
 printf("process id is %d\n",getpid());
 printf("parent id is %d\n",getppid());
 }
 else if(id>0){
  wait(NULL);
 printf("Parent Process\n");
 printf("process id is %d\n",getpid());
 }
else
printf("Fork failed\n");
}
