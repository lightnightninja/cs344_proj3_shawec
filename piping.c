/* NOTE THIS IS STILL ALMOST THE EXACT CODE FROM THE BOOK, STILL WORKING WITH IT. */


#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

#define BUF_SIZE 10

int piper(char **args, char **envp, int after) {
    int pfd[2];                             /* Pipe file descriptors */
    char buf[BUF_SIZE];
    ssize_t numRead;
    int status = 0;

    if (pipe(pfd) == -1){                    /* Create the pipe */
        perror("error opening pipe");
        status = -1;
    }

    switch (fork()) {
        case -1:
            perror("fork");
            status = -1;
            break;

        case 0:             /* Child  - reads from pipe */
            if (close(pfd[1]) == -1){
                perror("couldn't shut the child away (aka close the fd)");
                break;
            }

            for (;;) {              /* Read data from pipe, echo on stdout */
                numRead = read(pfd[0], buf, BUF_SIZE);
                if (numRead == -1)
                    perror("read");
                if (numRead == 0)
                    break;                      /* End-of-file */
                if (write(STDOUT_FILENO, buf, numRead) != numRead)
                    perror("child - partial/failed write");
            }

            write(STDOUT_FILENO, "\n", 1);
            if (close(pfd[0]) == -1){
                perror("close");
                status = -1;
            }
            break;

        default:            /* Parent - writes to pipe */
            if (close(pfd[0]) == -1)            /* Read end is unused */
                perror("close - parent");

            if (write(pfd[1], args[1], strlen(args[1])) != strlen(args[1]))
                perror("parent - partial/failed write");

            if (close(pfd[1]) == -1)
                perror("The parent didn't want to stop.");
            wait(NULL); //that child better hurry up.
            status = -1;

    }

    return status;
}