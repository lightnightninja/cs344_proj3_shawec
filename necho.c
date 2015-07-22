//
//  necho.c
//  cs344_proj3_shawec
//  Simple echo program for testing piping 
//  Created by Cierra Shawe on 7/22/15.
//  Copyright (c) 2015 Cierra Shawe. All rights reserved.
//

#include <stdio.h>

int main(){

    char buffer[128];

    fgets(buffer, 128, stdout);

    return 0;
    
}