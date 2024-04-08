/*****************************************************************************\
Macau University of Science and Technology

Module Name:
Lab01: Implementation of Multiplier and Divider

instructor:
Dr. Liang Yanyan

Abstract:
In this lab experiment, you are going to implement a 32-bit multiplier simulator 
as well as a 32-bit unsigned_div simulator using C language. Your simulators will 
perform multiply and divide operations for 32-bit binary numbers. Some C files 
implementing each component of the multiplier and the unsigned_div will be provided 
to you, you are required to modify and fill in the body of the functions in these 
files.

This file is the main file.

History:
Created on 09/22/2016 by CHI-LIN

\*****************************************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include<math.h>
#include "lab1.c"
#include "test.c"

/*****************************************************************************\ 
main function
\*****************************************************************************/
int main(void){
    srand(time(NULL));
    test_fulladder();
    test_booth_mult();
    test_signed_div();
}
