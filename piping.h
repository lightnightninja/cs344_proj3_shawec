#define _POSIX_C_SOURCE 200809L
#define _BSD_SOURCE

//
//  piping.h
//  cs344_proj3_shawec
//
//  Created by Cierra Shawe on 7/22/15.
//  Copyright (c) 2015 Cierra Shawe. All rights reserved.
//

#ifndef __piping__
#define __piping__

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

int piper(char **, char **, int);

#endif /* defined(__piping__) */
