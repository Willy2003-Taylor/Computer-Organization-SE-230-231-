/*****************************************************************************\
Macau University of Science and Technology

Module Name:
Lab01: Implementation of Multiplier and Divider

instructor:
Dr. Liang Yanyan

This file includes some basic function for implementaion of full-adder, multiplier
and divider.

History:
Created on 09/22/2016 by CHI-LIN

\*****************************************************************************/

#define WIDTH 32
#define IN  // Nothing but a sign show the input parameters
#define OUT // Nothing but a sign show the output parameters

typedef enum {
    FALSE = 0,
    TRUE = 1
} BOOL;

/*****************************************************************************\ 
Function Description:
get one bit from an int num. it will return the i th bit from the right.

Arguments:
IN      num     : int   - number which you want to get bit
IN      index   : int   - the index from the right

Return Value:
return i th bit
\*****************************************************************************/
BOOL get_bit(IN int num, IN int index){
    return (num >> index) & 1;
}

/*****************************************************************************\ 
Function Description:
get one bit form a long int num. it will return the i th bit form the right.

Arguments:
IN      num     : long   - number which you want to get bit
IN      index   : int   - the index form the right

Return Value:
return i th bit
\*****************************************************************************/
BOOL get_long_bit(IN long long num, IN int index){
    return (num >> index) & 1;
}
/*****************************************************************************\ 
Function Description:
set i th bit to 1 of the number. notice that it change the number directly

Arguments:
OUT     num     : int * - address of the number which you want to set bit
IN      index   : int   - the index form the right

Return Value:
void
\*****************************************************************************/
void set_bit(OUT int * num, IN int index){
    *num |= 1 << index;
}

/*****************************************************************************\ 
Function Description:
set i th bit to 1 of the number. notice that it change the number directly

Arguments:
OUT     num     : long * - address of the number which you want to set bit

IN      index   : int   - the index form the right

Return Value:
void

\*****************************************************************************/
void set_long_bit(OUT long long * num, IN int index){
    *num |= (long long)1 << index;
}

/*****************************************************************************\ 
Function Description:
set i th bit to 0 of the number. notice that it change the number directly

Arguments:
OUT     num     : int * - address of the number which you want to set bit
IN      index   : int   - the index form the right

Return Value:
void
\*****************************************************************************/
void clean_bit(OUT int * num, IN int index){
    *num &= ~(1 << index);
}

/*****************************************************************************\ 
Function Description:

set i th bit to 0 of the number. notice that it change the number directly

Arguments:

OUT     num     : long * - address of the number which you want to set bit
IN      index   : int   - the index form the right


Return Value:
void
\*****************************************************************************/
void clean_long_bit(OUT long long * num, IN int index){
    *num &= ~((long long)1 << index);
}

/*****************************************************************************\ 
Function Description:
change i th bit to what u want of the number. notice that it change the number 
directly

Arguments:
OUT     num     : int * - address of the number which you want to set bit
IN      index   : int   - the index from the right
IN      bit     : BOOL   - bit what you want to change

Return Value:
void
\*****************************************************************************/
void change_bit(OUT int * num, IN int index, IN BOOL bit){
    if(bit == FALSE) clean_bit(num, index);
    else if(bit == TRUE) set_bit(num, index);
}

/*****************************************************************************\ 

Function Description:
change i th bit to what u want of the number. notice that it change the number 

directly

Arguments:
OUT     num     : long * - address of the number which you want to set bit

IN      index   : int   - the index form the right
IN      bit     : BOOL   - bit what you want to change


Return Value:
void
\*****************************************************************************/
void change_long_bit(OUT long long * num, IN int index, IN BOOL bit){
    if(bit == FALSE) clean_long_bit(num, index);
    else if(bit == TRUE) set_long_bit(num, index);
}

/*****************************************************************************\ 
Function Description:
not gate. 

Arguments:
IN      bit     : BOOL   - bit what you want to change

Return Value:
return !bit
\*****************************************************************************/
BOOL not_gate(IN BOOL bit){
    return !bit;
}

/*****************************************************************************\ 
Function Description:
and gate. 

Arguments:
IN      a       : BOOL   - the first bit u want to feed the gate
IN      b       : BOOL   - the second bit  

Return Value:
return a && b
\*****************************************************************************/
BOOL and_gate(IN BOOL a, IN BOOL b){
    return a && b;
}

/*****************************************************************************\ 
Function Description:
or gate. 

Arguments:
IN      a       : BOOL   - the first bit u want to feed the gate
IN      b       : BOOL   - the second bit  

Return Value:
return a || b
\*****************************************************************************/
BOOL or_gate(IN BOOL a, IN BOOL b){
    return a || b;
}

/*****************************************************************************\ 
Function Description:
xor gate. 

Arguments:
IN      a       : BOOL   - the first bit u want to feed the gate
IN      b       : BOOL   - the second bit  

Return Value:
return a != b
\*****************************************************************************/
BOOL xor_gate(IN BOOL a, IN BOOL b){
    return a != b;
}

/*****************************************************************************\ 
Function Description:
inverse. this function inverse a number.
for example, if you input 1100 1100, it will return 0011 0011.

Arguments:
IN      num         : int   - the number
OUT     an          : int * - the result of the number

Return Value:
void
\*****************************************************************************/
void inverse(IN int num, OUT int * an){
    int i;
    for(i = 0; i < WIDTH; i++){
        BOOL now = get_bit(num, i);
        change_bit(an, i, not_gate(now));
    }
}

/*****************************************************************************\ 
Function Description:
shift_right. it simulates the CPU to shift right a 64 bit register. this register
is combine by two 32 bit int. 
for example (suppose it is a 16 bit register),if we input a [0000 0011] and 
b[0011 0000], it will become a[0000 0001] and b[1001 1000].

Note:
in C, operater >> will depend on the sign of the number. so if the number is 
negative, it will set the higest bit to 1.

Arguments:
OUT     a           : int * - the first number
OUT     b           : int * - the second number

Return Value:
void
\*****************************************************************************/
void shift_right(int * a, int * b){

    BOOL aRight = get_bit(*a, 0);
    *a = *a >> 1;
    *b = *b >> 1;
    change_bit(b, WIDTH - 1, aRight);
}




/*****************************************************************************\ 
Function Description:
shift_left. it simulat the CPU to shift left a 64 bit register. this register
is combine by two 32 bit int. 
for example (suppose it is a 16 bit register),if we input a [0000 1100] and 
b[1100 0000], it will become a[0001 1001] and b[1000 0000].

Arguments:
OUT     a           : int * - the first number
OUT     b           : int * - the second number

Return Value:
void
\*****************************************************************************/
void shift_left(int * a, int * b){
    
    BOOL bLeft = get_bit(*b, 31);
    *a = *a << 1;
    *b = *b << 1;
    change_bit(a, 0, bLeft);
}
 
/*****************************************************************************\ 
Function Description:
shifter. u can set the direction of the shifter.

Arguments:
OUT     a           : int * - the first number
OUT     b           : int * - the second number
IN      direction   : int   - the direction. 1 means shift right. 0 means shift 
                            left.

Return Value:
void
\*****************************************************************************/
void shifter(int * a, int * b, IN int direction){
    if(direction == 0) shift_left(a, b);
    else if(direction == 1) shift_right(a, b);
}

