// Write a program that forks a child and creates a shared pipe
// between the parent and child processes. Have the child write 
// the three messages to the parent and have the parent print out 
// the messages. 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MSGSIZE 16

char* msg1 = "hello world #1";
char* msg2 = "hello world #2";
char* msg3 = "hello world #3";

int main(void)
{
    char inbuf[MSGSIZE];    // a buffer that will hold the incoming data that is being written
    int p[2]; // a two-element array to hold the read and write file descriptors that are used by the pipe
    // Initialize our Pipe
    if (pipe(p) < 0) {
        fprintf(stderr, "pipe failed\n");
        exit(1);
    }  
    int rc = fork();
    // child process starts executing here
    if (rc < 0) {    // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {    // child process satisfies this branch
        // write 16 bytes of data to the write file descriptor
        write(p[1], msg1, MSGSIZE);
        write(p[1], msg2, MSGSIZE);
        write(p[1], msg3, MSGSIZE);
    } else {

       int wc = waitpid(rc, NULL, 0);
       close(p[1]);
      printf("parent ork YO\n");
       while(read(p[0], inbuf, MSGSIZE)> 0){
           printf("% s\n", inbuf);
       }
        
    }
    return 0;
}
