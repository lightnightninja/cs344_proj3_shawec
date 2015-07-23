//
//  redirection.c
//  cs344_proj3_shawec
//
//  Created by Cierra Shawe on 7/22/15.
//  Copyright (c) 2015 Cierra Shawe. All rights reserved.
/* For this part I just went through the redirection "example" description laid everything out */

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>


int redir(char **args, char **envp, int after, int which){

    pid_t childPID;
    int fd = 0;
    int in = 0, out = 0;
    int status = 0;
    if (which == 0)
        in  = 1;
    else
        out = 1;
    int in_save, out_save;

    fflush(STDIN_FILENO); //make sure there is nothing left in stdin

    switch (childPID = fork()) {
        case -1:
            perror("coudn't fork");
            return -1;
        case 0:
            if (in == 1) { // < in
                fd = open(args[after], O_RDONLY, 0);
                 printf("Checking in!\n");
                in_save = fd;
                dup2(fd, STDIN_FILENO); //duping stdin
                close(fd);//closing it so that it'll get used
            }
            if (out == 1) { // > out
                fd = open(args[after], O_WRONLY | O_CREAT,  0664); //creating a rw-rw-r-- file
                if(fd != -1)
                    printf("Checking out!\n");
                out_save = fd;
                dup2(fd, STDOUT_FILENO);//setting the fd to stdout
                close(fd);//closing "stdout" so that it can be used
            }
            execve(args[0], args, envp);
            perror("Uh oh, we failed to open the file.");
            status = -1;
        default:
            waitpid(childPID, &status, 0);
            if (in == 1)
                dup2(in_save, STDIN_FILENO);//we want to restore the values back
            if (out == 1)
                dup2(out_save, STDOUT_FILENO);//save me!

            break;
    }

    return status;
}