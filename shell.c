#define _POSIX_C_SOURCE 200809L
#define _BSD_SOURCE
//
//  shell.c
//  cs344_proj3_shawec
//
//  Created by Cierra Shawe on 7/18/15.
//  Copyright (c) 2015 Cierra Shawe. All rights reserved.
//
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <string.h>

#include <signal.h>
#include <sys/wait.h>

#include "csystem.h"

#define BSIZE 256


#define endl printf("\n") //I'm sick of printing this, easy enough.

/* Not sure what I want to do with this yet. */
void help(){

    printf("set: the environment variables.\n ");

}
/* makes sure there is nothing left in the buffer */
void in_clear() {
    int check;
    while((check = getchar()) != '\n' || check != EOF);
} //not working

/* has a simple goal of getting back the number of arguments */
int get_arg_count(const char *buffer){

    int num = 0;

    /* Simply getting the count, so we can malloc */
    for (int i = 0; i < BSIZE; i++){
        if (buffer[i] == ' ' || buffer[i] == '\0' || buffer[i] == '\n')
            num++;
        if(buffer[i] == '\n')
            break;
    }

    return num;
}

/* Used to avoid memory leak when taking in args */
void free_arr(void **array, int size){

    for (int i = 0; i < size; i++)
        free(array[i]);

    free(array);
}

/* The goal is to get the input from the user and format it to be used in main */
/* Each argument is a null terminated string */
char **get_args(int *n) {

    /* used for putting things in array. */
    const char buffer[BSIZE];
    char **args;
    int num;
    int pos = 0;
    int len = 0;

    /* Take a command in from stdin */
    printf("c-sh $ "); //this is just for kicks to be a "custom" shell, also a play on my name :P
    fgets((char *)buffer, BSIZE, stdin); //take in input

    //in_clear(); //ensure there is ntohing left in stdin for later. DOESN'T WORK
    num = get_arg_count(buffer); //getting
    n[0] = num; //making it so I can use num later, before we start decrementing it

    if (num == 0){ //checking to make sure args isn't 0
        return args; //we'll do this before we bother taking space.
    }
    args = (char **)malloc(num + 1 * sizeof(char *)); //making space for the pointers to strings + 1 for NULL
    args[num+1] = NULL;
    /* Assigning memory for the args, in order to keep track of them for later */
    for (int i = 0; i < num || i < BSIZE; i++) { //itterating through buffer

        ++len;//we want to start at 1

        if (buffer[i] == '\0' || buffer[i] == ' ' || buffer[i] == '\n') { //checking for 'breaks'

            char *a = (char *)malloc(len * sizeof(char)); //mallocing for args

            args[pos] = a; //assigning the arg to the position in the argument array
            for (int j = 0; j < len; j++) {
                if (buffer[i-len+j+1] == ' ' || buffer[i-len+j+1] == '\n')
                    a[j] = '\0'; //replacing ' ' and \n with null
                else
                    a[j] = buffer[i-len+j+1]; //assigning it based on an offset
            }
            len = 0; //reseting lenth
            num--; //decrementing the number of args we have left
            pos++; //increasing the position

        }
        if (buffer[i] == '\n'){//breaking out of the loop to save time
            break;
        }
    }

    return args; //returning what is hopefully a good array ^_^
}

char *get_arg(int *n) {

    /* used for putting things in array. */
    const char buffer[BSIZE];
    char *args;
    int len = 0;
    int num;

    /* Take a command in from stdin */
    printf("c-sh $ "); //this is just for kicks to be a "custom" shell, also a play on my name :P
    fgets((char *)buffer, BSIZE, stdin); //take in input

    //in_clear(); //ensure there is ntohing left in stdin for later. DOESN'T WORK
    num = get_arg_count(buffer); //getting
    n[0] = num; //making it so I can use num later, before we start decrementing it

    if (num == 0){ //checking to make sure args isn't 0
        return args; //we'll do this before we bother taking space.
    }
    for(len = 0; buffer[len] != '\n' || len < BSIZE; len++);
    args = malloc(len*sizeof(char));
    /* Assigning memory for the args, in order to keep track of them for later */
    for (int i = 0; i < len; i++) { //itterating through buffer

        if (buffer[i] == '\n')
            args[i] = '\0'; //replacing ' ' and \n with null
        else
            args[i] = buffer[i]; //assigning it based on an offset

    }
    return args; //returning what is hopefully a good array ^_^
}//was mostly for testing

/* We all know what main does, doesn't need argv or argc, thsoe are now internal. */
int main(int argc, char **argv) {

    printf("argc = %i\n", argc);

    char **args;
    char **envp = {NULL};
    int exit = 0;
    //Mallocing was how I could make num actually changable.
    //This was the first time Loren helped with anything,
    //other than moral support, on the assignments.
    //Yay for having simple things pointed out!
    int num = (int)malloc(sizeof(int));
    if (strncmp(argv[0], "exit", 4) == 0) {
        return 0;
    }
    if (argc != 1) {
        puts(argv[1]);
        if (strncmp(argv[1], "exit", 4) == 0)
            return 0;
    }

    //ADDMEsystem("clear");//clearing the screen for when the user enters the shell
    /* Creating a 1d array to take in args with */
    for(int i = 0; i < num; i++);
    while (exit != 1) {

        printf("pid before sys: %i\n", getpid());
        args = get_args(&num); //gets the array of arguments, formatted all nice
        //DUBUG system(args);
        for (int i = 0; i < num; i++) {
            puts(args[i]);
        }
        if (strncmp(args[0], "--help", 6) == 0) {
            help();
        }
        if (strncmp(args[0], "exit", 4) == 0)
            exit = 1;
        if (access(args[0],F_OK) != -1) { //this is needed to make sure we aren't accessign something not there.
            if(csystem(args, envp, num) == -1)
                return 0;
            if(num != 0)
                free_arr((void **)args, num);
        }
        printf("returning from csystem\n");


        printf("my pid: %i\n", getpid());
        printf("parent pid pid: %i\n", getppid());


    }

    //ADDMEsystem("clear");
    return EXIT_SUCCESS; /* If we get here, time to be done!  */
}

/*

 To clarify; you can use any of the exec(3) variants
 in order to construct your system call, but those
 variants that revert to calling /bin/sh to interpret
 the command are not sufficient for full credit. If
 you choose to use one of the exec(3) variants that
 calls /bin/sh, that is good for 85% of the total
 points on the assignment.

 The exec family of functions are implemented on top
 of execve(2), which I encourage you to use, and
 will count for full credit. Said differently, you
 must implement the components that /bin/sh would
 provide for full credit.

 commands to implement:
 echo
 pwd
 test
 ls
 cd
 exec,
 exit,
 read,
 set,
 source,
 ulimit,
 umask,
 wait


 ps: The environment variable array that I was thinking of in class is detailed in the man page for exec(3), (extern char **environ;). You will likely find that helpful.

 */