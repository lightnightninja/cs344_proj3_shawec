#define _POSIX_C_SOURCE 200809L
#define _BSD_SOURCE
//
//  necho.c
//  cs344_proj3_shawec
//  Simple echo program for testing piping 
//  Created by Cierra Shawe on 7/22/15.
//  Copyright (c) 2015 Cierra Shawe. All rights reserved.
//

#include <stdio.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <string.h>

#include <signal.h>
#include <sys/wait.h>

int main(int argc, char **argv){

    char buffer[128];
    int len = 0;
    if(argc > 1)
        printf("Please don't die :( \n");
    for (int i = 1; i < argc; i++){
        for (int j = 0; argv[i][j] != ' ' && argv[i][j] != '\0' && argv[i][j] != '\n'; j++){
            buffer[len] = argv[i][j];
            len++;
        }
        len++;
    }
    //fgets(buffer, 128, stdin);
    puts(buffer);

    return 0;
    
}