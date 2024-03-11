#include <stdio.h>

void print_star(){
    int i = 0;
    int starNum = 50;
    for(i = 0; i < starNum; i++){
        printf("*");
    }
    printf("\n");
}

void test_signed_div(){
    int i = 0;
    int testNum = 20;
    int suc = 0;


    print_star();
    printf("test for signed_div\n");
    print_star();
    for(i = 0; i < testNum; i++){
        int a = rand() % 100000 - 50000;
        int b = rand() % 100 - 50;
        while(b == 0){
            b = rand() % 100 - 50;
        }
        int r = 0;
        int q = 0;
        printf("test %d: %d / %d\nexpect: %d, %d \t", i, a, b, a/b, a%b);
        signed_div(a, b, &r, &q);
        if(q == a / b && r == a % b){
            printf("\x1b[32mAC\x1b[0m\n");
            suc++;
        }
        else{
            printf("\x1b[31mWA\x1b[0m\t");
            printf("re = %d, %d\n", q, r); 
        }
    }
    print_star();

    printf("\x1b[32m%d / %d test is pass for signed_div().\x1b[0m\n",suc, testNum);
    print_star();
    printf("\n");
}

void test_booth_mult(){
    int i = 0;
    int testNum = 20;
    int suc = 0;


    print_star();
    printf("test for booth_mult\n");
    print_star();
    for(i = 0; i < testNum; i++){
        int a = rand() % 10000 - 5000;
        int b = rand() % 10000 - 5000;
        long long int c = 0;
        printf("test %d: %d * %d\nexpect: %d \t", i, a, b, a*b);
        booth_mult(a, b, &c);
        if(c == a * b){
            printf("\x1b[32mAC\x1b[0m\n");
            suc++;
        }
        else{
            printf("\x1b[31mWA\x1b[0m\t");
            printf("re = %ld \n", c); 
        }
    }
    print_star();

    printf("\x1b[32m%d / %d test is pass for booth_mult().\x1b[0m\n",suc, testNum);
    print_star();
    printf("\n");
}

void test_fulladder(){
    int i = 0;
    int testNum = 20;
    int suc = 0;


    print_star();
    printf("test for fulladder\n");
    print_star();
    for(i = 0; i < testNum; i++){
        int a = rand() % 1000;
        int b = rand() % 1000;
        int c = 0;
        printf("test %d: %d + %d\nexpect: %d \t", i, a, b, a+b);
        fulladder32(a, b, &c);
        if(c == a + b){
            printf("\x1b[32mAC\x1b[0m\n");
            suc++;
        }
        else{
            printf("\x1b[31mWA\x1b[0m\t");
            printf("re = %d \n", c); 
        }
    }
    print_star();

    printf("\x1b[32m%d / %d test is pass for fulladder().\x1b[0m\n",suc, testNum);
    print_star();
    printf("\n");
}
