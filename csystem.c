#define _POSIX_C_SOURCE 200809L
#define _BSD_SOURCE

/*  Credit:
 TLPI was used for a lot of the implementation of this, as noted in the comments.
 I will not cite it specifically for the rest of the code, however, anything that
 was based off of the textbook, will be commented with an explanation of how I
 understand what is working. Basically, I put a lot of time into learning what
 these thigns are doing, it's just hard to not have the code be very similar to
 the one found in the book when the processes are fairly structured in how this
 needs to work.
 Note: I'll probably check in before submitting this
 */

#include "csystem.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

int csystem(char **args, char **envp, int arg_count) {

    //holds our new values
    sigset_t block;
    //stores the orignal values of sig
    sigset_t original;
    //used to take in new options to ignore
    struct sigaction sigIgnore;
    //stores the original values of sigquit
    struct sigaction sigOrQuit;
    //stores oringal values of sigint
    struct sigaction sigOrInt;
    //used for storing the sig values before the
    struct sigaction sigDefault;
    //where we store the PID of child
    pid_t childPID;
    //used to catch errno while the program is running
    int status = 0;
    //place holder to return errno to original value after program is done
    int sErrno;
    /* We need to block sigchild */
    sigemptyset(&block);
    /*Creating the empty set to handle what we put in it to block*/
    sigaddset(&block, SIGCHLD);
    /*adding SIGCHILD to the list that we well next block*/
    sigprocmask(SIG_BLOCK, &block, &original);
    /*this is setting block to be the new set, and storing the old set in orginal (sigprocmask(2)) of the man pages*/

    /* Now we need to ignore SIGINT and SIGQUIT */
    sigIgnore.sa_handler = SIG_IGN; //this sets it so we'll be using ignore when we call sigprocmask
    sigIgnore.sa_flags = 0; //no special flags
    sigemptyset(&sigIgnore.sa_mask); //setting up the set of signals to ignore
    sigaction(SIGINT, &sigIgnore, &sigOrInt); //setting SIGINt as something we need to ignore
    sigaction(SIGQUIT, &sigIgnore, &sigOrQuit); //setting SIGQUIT as something else we want to ignore
    char *noaccess[] = {"./shell", "exit", NULL};

    /*  Okay, time to start actually creating processes, now that we've set
     it up so that we don't have to worry about SIGINT, and SIGQUIT,
     since they could really mess things up for later. For will either
     reutrn -1 when it fails, or 0 when it succeeds, however it rarely fails.
     */
     printf("error here at start of system?\n");
        switch (childPID = fork()) {

        case -1: /* Error */
            status = -1; //we don't want to return/exit, we need to unblock stuff after
            break; //we just want to get out and close our signals.
        case 0: /* The child will run this on success */
            sigDefault.sa_handler = SIG_DFL; //we want to make sure that sigint and sigquit are blocked properly... again
            sigDefault.sa_flags = 0; //more setting of flags, nothing special here.
            sigemptyset(&sigDefault.sa_mask);

            if (sigOrInt.sa_handler != SIG_IGN)
                sigaction(SIGINT, &sigDefault, NULL);
            if (sigOrQuit.sa_handler != SIG_IGN) {
                sigaction(SIGQUIT, &sigDefault, NULL);
            }
            printf("error here before execve?\n");


            /*this is the biggest thing that is different from the TLPI version, as it's using our shell to manage things.*/
            if (access(args[0],F_OK) != -1){
                status = -1;
                execve(args[0], args, envp);
                printf("not accessed\n");
                status = -1;

            }
            else{
                //execve(nofile[0], nofile, NULL);
                printf("Command not recognized\n");
                status = -1;
            }
            break;

        default: /* Parent */
            printf("childs pid: %i\n", childPID);
            while (waitpid(childPID, &status, 0) == -1){
                if(errno != EINTR){
                    printf("xx ");

                }
                status = -1;
                break;
            }

                printf("I'm done waiting\n");
                status = -1;

    }
    printf("I, %i, am about to exit.\n", getpid());
    sErrno = errno; /* The following may change 'errno' */
    sigprocmask(SIG_SETMASK, &original, NULL);
    sigaction(SIGINT, &sigOrInt, NULL);
    sigaction(SIGQUIT, &sigOrQuit, NULL);
    errno = sErrno;
    return status;
}