/*****************************************************************************\
Macau University of Science and Technology

Module Name:
Lab01: Implementation of Multiplier and Divider

instructor:
Dr. Liang Yanyan

In this c file, you are required to modify and fill in the body of the functions
accroding to the document.

History:
Created on 09/22/2016 by CHI-LIN

\*****************************************************************************/

#include "functions.c"

/*****************************************************************************\ 
Function Description:
halfadder. 
notice that if u want to set a output value inside the function, you need to 
use * to access the memory.

Arguments:
IN      a       : BOOL   - the first bit u want to feed the gate
IN      b       : BOOL   - the second bit  
OUT     c       : BOOL * - carry bit
OUT     s       : BOOL * - sum bit

Return Value:
void
\*****************************************************************************/
void halfadder(IN BOOL a, IN BOOL b,
                OUT BOOL * c, OUT BOOL * s){
    *s = xor_gate(a, b);
    *c = and_gate(a, b);
}

/*****************************************************************************\ 
Function Description:
fulladder. 

Arguments:
IN      a           : BOOL   - the first bit 
IN      b           : BOOL   - the second bit  
IN      carry_in    : BOOL   - carry in bit
OUT     carry_out   : BOOL * - carry out bit
OUT     s           : BOOL * - sum bit

Return Value:
void
\*****************************************************************************/
void fulladder(IN BOOL a, IN BOOL b, IN BOOL carry_in,
                OUT BOOL * carry_out, OUT BOOL * s){
    //TODO
    /*
    TASK 1

    You need to employ a full-adder to perform addition and subtraction operations. 
    The full-adder can be implemented by the following formulas (see document). You
	may check your full-adder according to the truth table (see document).

    You are encouraged to implement the full-adder using basic logic gates. A 1-bit 
    half-adder is implemented at first, which contains two logic gates: a XOR gate 
    and an AND gate. And then, a 1-bit full-adder is built using two half-adders 
    and an OR gate.

    Hint: 
    1. when u call the function halfadder, you need to pass the address of the 
    value to the output parameter. use & to get the address of the value.
    2. if u want to set a output value, use * to access the memory and set it.

    */

	// write your code here.
    BOOL* temp_c1 = (BOOL*)malloc(sizeof(BOOL));
    BOOL* temp_c2 = (BOOL*)malloc(sizeof(BOOL));
    BOOL* temp_s1 = (BOOL*)malloc(sizeof(BOOL));
    BOOL* temp_s2 = (BOOL*)malloc(sizeof(BOOL));
    //Initialization

    halfadder(a, b, temp_c1, temp_s1);
    halfadder(carry_in, *temp_s1, temp_c2, temp_s2);
    *s = *temp_s2;
    *carry_out = or_gate(*temp_c2, *temp_c1);
}

/*****************************************************************************\ 
Function Description:
fulladder32. this function simulat a 32 bit fulladder. it will save the result
in parameter c.

Arguments:
IN      a           : int   - the first number
IN      b           : int   - the second number
OUT     c           : int * - the result of the number

Return Value:
void
\*****************************************************************************/
void fulladder32(IN int a, IN int b, OUT int * c){

	// don't revise this code segment.
    int i;
    BOOL A_bin[WIDTH], B_bin[WIDTH], S_bin[WIDTH]; 
	for (i = 0; i < WIDTH; i++){
		A_bin[i] = get_bit(a,i);  // representing A in binary.
		B_bin[i] = get_bit(b,i);  // representing B in binary.
	}
	BOOL C[WIDTH+1];   // Declaration of carry in and carry out;
	C[0] = 0;
	
	//TODO
    /*
    TASK 2

    A 32-bit full-adder is implemented by just connecting the carry-out of the 
    least significant bit of 1-bit full-adder to the carry-in of the next least 
    significant bit of another 1-bit full-adder.

    Hint: 
    You need to write a loop and calculate it from lowest bit to high bit, and
    save the carry_out result for the next eval.

    */
	
	
	// write your code here.
	for(i = 0; i < WIDTH; i++)
        fulladder(A_bin[i], B_bin[i], C[i], &C[i+1], &S_bin[i]);
	
	// don't modify this code segment.
	for (i = 0; i < WIDTH; i++){
		change_bit(c, i, S_bin[i]);	
	}	
	
}

/*****************************************************************************\ 
Function Description:
neg. this function gets the inverse of input number.

Arguments:
IN      num           : int - the input number

Return Value:
the inverse of input number
\*****************************************************************************/
int neg(int num){
    int an = 0;
    int inverse_an = 0;
    inverse(num, &inverse_an);
    fulladder32(inverse_an, 1, &an);
    return an;
}

/*****************************************************************************\ 
Function Description:
add. this function performs addition.

Arguments:
IN      a           : int   - the first number
IN      b           : int   - the second number
OUT     c           : int * - the result of the number

Return Value:
void
\*****************************************************************************/
void add(IN int a, IN int b, OUT int * c){
    fulladder32(a, b, c);
}

/*****************************************************************************\ 
Function Description:
add. this function performs substraction.

Arguments:
IN      a           : int   - the first number
IN      b           : int   - the second number
OUT     c           : int * - the result of the number

Return Value:
void
\*****************************************************************************/
void sub(IN int a, IN int b, OUT int * c){
    fulladder32(a, neg(b), c);
}

/*****************************************************************************\ 
Function Description:
unsigned_mult. this function simulat a multiplier with unsigned numbers. it will
save the result in Product.

Arguments:
IN      Multiplicand      : int   - the Multiplicand
IN      Multiplier        : int   - the Multiplier
OUT     Product           : int * - the Product

Return Value:
void
\*****************************************************************************/
void unsigned_mult(int Multiplicand, int Multiplier, long long int * Product){
    int ProductLeft = 0;
    int i;
    for(i = 0; i < WIDTH; i++){
        BOOL LSB = get_bit(Multiplier, 0);
        if(LSB == TRUE){
            int an = 0;
            add(ProductLeft, Multiplicand, &an);
            ProductLeft = an;
        }
        shifter(&ProductLeft, &Multiplier, 1);
    }
    
    for(i = 0; i < WIDTH; i++){
        change_long_bit(Product, i, get_bit(Multiplier, i));
        change_long_bit(Product, i + WIDTH, get_bit(ProductLeft, i));
    }
}

/*****************************************************************************\ 
Function Description:
booth_mult. this function simulat a multiplier with signed numbers using Booth
algorithm. it will save the result in Product.

Arguments:
IN      Multiplicand      : int   - the Multiplicand
IN      Multiplier        : int   - the Multiplier
OUT     Product           : int * - the Product

Return Value:
void
\*****************************************************************************/
void booth_mult(int Multiplicand, int Multiplier, long long int * Product){
	
	//TODO
    /*
    TASK 3

    You are required to modify and fill in the body of the functions to implement
	a  multiplier using Booth algorithm.

    Hint: 
    You can refer to the implementation of unsigned_mult.
    */
	
	// write your code here.
	int ProductLeft = 0;
    BOOL LB2 = FALSE;

	for(int i = 0; i < WIDTH; i++){
        BOOL LB1 = get_bit(Multiplier, 0);
        if((LB1 == TRUE && LB2 == TRUE) || (LB1 == FALSE && LB2 == FALSE)){
            shifter(&ProductLeft, &Multiplier, 1);
            LB2 = LB1;
            //inverse LB2 individually
        }
        else if(LB1 == FALSE && LB2 == TRUE){
            int an = 0;
            add(ProductLeft, Multiplicand, &an);
            ProductLeft = an;
            shifter(&ProductLeft, &Multiplier, 1);
            LB2 = LB1;
        }

        else if(LB1 == TRUE && LB2 == FALSE){
            int an = 0;
            sub(ProductLeft, Multiplicand, &an);
            ProductLeft = an;
            shifter(&ProductLeft, &Multiplier, 1);
            LB2 = LB1;
        }
    }

    for(int i = 0; i < WIDTH; i++){
        change_long_bit(Product, i, get_bit(Multiplier, i));
        change_long_bit(Product, i + WIDTH, get_bit(ProductLeft, i));
    }
	
	// don't modify this code segment.
    *Product = 0L;
    int i; 
    for(i = 0; i < WIDTH; i++){		
        change_long_bit(Product, i, get_bit(Multiplier, i));
        change_long_bit(Product, i + WIDTH, get_bit(ProductLeft, i));
    }

}

/*****************************************************************************\ 
Function Description:
unsigned_div. this function simulat a divider with unsigned numbers. it will
save the results in Remainder and Quotient.

Arguments:
IN      Dividend            : int   - the Dividend
IN      Divisor             : int   - the Divisor
OUT     Remainder           : int * - the Remainder
OUT     Quotient            : int * - the Quotient

Return Value:
void
\*****************************************************************************/
void unsigned_div(IN int Dividend, IN int Divisor,
             OUT int * Remainder, OUT int * Quotient){
             	
    //TODO
    /*
    TASK 4

    You are required to modify and fill in the body of the functions to implement
	a  divider with unsign numbers.
    */
    
	// write your code here.
    
	
	
}

/*****************************************************************************\ 
Function Description:
unsigned_div. this function simulat a divider with signed numbers. it will
save the results in Remainder and Quotient.

Arguments:
IN      Dividend            : int   - the Dividend
IN      Divisor             : int   - the Divisor
OUT     Remainder           : int * - the Remainder
OUT     Quotient            : int * - the Quotient

Return Value:
void
\*****************************************************************************/
void signed_div(IN int Dividend, IN int Divisor,
                  OUT int * Remainder, OUT int * Quotient){
    BOOL DividendBS = get_bit(Dividend, WIDTH - 1);
    if(DividendBS == TRUE)
        Dividend = neg(Dividend);

    BOOL DivisorBS = get_bit(Divisor, WIDTH - 1);
    if(DivisorBS == TRUE)
        Divisor = neg(Divisor);

    unsigned_div(Dividend, Divisor, Remainder, Quotient);

    BOOL RemainderBS = DividendBS;
    BOOL QuotientBS = xor_gate(DividendBS, DivisorBS);

    if(RemainderBS == TRUE)
        *Remainder = neg(*Remainder);
    if(QuotientBS == TRUE)
        *Quotient = neg(*Quotient);
}
