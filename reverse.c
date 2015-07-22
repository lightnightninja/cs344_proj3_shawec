//
//  reverse.c
//  cs344_proj3_shawec
//  The goal is to just reverse the input given. 
//  Created by Cierra Shawe on 7/22/15.
//  Copyright (c) 2015 Cierra Shawe. All rights reserved.
//

#include <stdio.h>

int main(){

    char buffer[128];
    char temp[128];
    int j = 0;
    int i;

    fgets(buffer, 128, stdin);
    for(i = 0; buffer[i] != '\n' || i < 128; i++);

    for(i = i; i > 0; i--, j++)
        temp[i] = buffer[j];

    fputs(buffer, stdout);

    return 0;

}