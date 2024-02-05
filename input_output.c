#include<stdio.h>
#include<stdlib.h>
#include"input_output.h"

int read_binary(FILE *ip, int size)
{


    int read = fgetc(ip);

    if(read == EOF)return -1;

    int code;

    if((leftOver + 8) >= size)
    {


        int code1 = (leftValue << (size - leftOver));

        int code2 =  (read >> ((8-(size-leftOver))));

        code = code1 + code2;

        int tmp = leftOver;

        leftOver = (8-(size-tmp));

        leftValue = read & ((1<< (8-(size-tmp)))-1);
    }
    else
    {
        code = (leftValue << 8 )+ read;


        leftValue = 0;

        read = fgetc(ip);


        size = size- (8+leftOver);


        code = (code << size);   // first 8-leftover bits are extracted

        code = code + (read >> (8-size)); //last leftover bits are extracted from the next input

        leftOver = 8-size;  // update the leftover size of the input 2

        leftValue = (read & ((1<<(8-size))-1));  // update the leftvalue



    }
    return code;


}
void write_binary(FILE *op, int code, int size)
{
    int pre = (leftValue << (8-leftOver)); // first leftover bits are written with pre value

    int curr = (code>>(size-(8-leftOver))); // last remaining bits are written with this

    leftOver = leftOver+size-8;  //updating leftover

    leftValue = code&((1<<(size-(8-leftOver)))-1); //updating leftvalue

    int print = pre + curr;        //oring to get 8 bits

    fputc(print,op);              // fputc writes only 8 bits so every time we should maintain buffer

    while(leftOver >=8 )
    {

        print = (leftValue >> (leftOver-8));

        leftValue = leftValue & ((1<<(leftOver-8))-1);

        leftOver = leftOver-8;

        fputc(print,op);

    }
}
