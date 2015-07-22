//
//  csystem.h
//  cs344_proj3_shawec
//
//  Created by Cierra Shawe on 7/22/15.
//  Copyright (c) 2015 Cierra Shawe. All rights reserved.
//

#ifndef __csystem__
#define __csystem__

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

int csystem(char **, char **, int);

#endif /* defined(__csystem__) */
