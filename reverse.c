#define _POSIX_C_SOURCE 200809L
#define _BSD_SOURCE
//
//  reverse.c
//  cs344_proj3_shawec
//  The goal is to just reverse the input given. 
//  Created by Cierra Shawe on 7/22/15.
//  Copyright (c) 2015 Cierra Shawe. All rights reserved.
//


#include <stdio.h>
#include <string.h>

/* No wonder it wasn't working, strrev isn't in linux, whoops. Downside of testing on a mac.
 code from: http://stackoverflow.com/questions/8534274/is-the-strrev-function-not-available-in-linux
 */
char *strrev(char *str){
    char *p1, *p2;

    if (! str || ! *str)
        return str;
    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2){
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    return str;
}

int main(){

    char buffer[128];
    char *ret;
    fgets(buffer, 128, stdin);
    ret = strrev(buffer);
    fputs(ret, stdout);
    fputs('\n', stdout);

    return 0;

}