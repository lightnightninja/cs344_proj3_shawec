//
//  reverse.c
//  cs344_proj3_shawec
//  The goal is to just reverse the input given. 
//  Created by Cierra Shawe on 7/22/15.
//  Copyright (c) 2015 Cierra Shawe. All rights reserved.
//
#include <stdio.h>
#include <string.h>

int main(){

    char buffer[128];

    fgets(buffer, 128, stdin);
    strrev(buffer);
    fputs(buffer, stdout);

    return 0;

}