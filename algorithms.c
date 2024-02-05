#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include"input_output.h"
#include"functions.h"
#include"algorithms.h"
#include"common.h"
#include"error.h"
//stores the code size in number of bits
int  code_size = 8;
//stores the dictionary size
int dictionary_size = 255;

int input_file_size = 0;
int output_file_size = 0;

int leftOver = 0;
int leftValue = 0;


long int get_file_size(char *filename)
{

      // opening the file in read mode
        FILE* fp = fopen(filename, "rb");

        // checking if the file exist or not
        if (fp == NULL) {
            printf("File Not Found!\n");
            return -1;
        }

        fseek(fp, 0L, SEEK_END);
      
        // calculating the size of the file
        return  ftell(fp);


}

void print_info(char *filename)
{   printf("********************************************************************************************************************\n");
    printf("      Compressing the file : %s\n",filename);
    printf("      INPUT FILE SIZE      : %d Bytes\n",input_file_size);
    printf("      OUTPUT FILE SIZE     : %d Bytes\n",output_file_size);
    long int difference = input_file_size - output_file_size;
    float ratio = (float) difference/input_file_size;
    ratio = ratio * 100;
    printf("      %.2f %% space saved\n",ratio);
     printf("********************************************************************************************************************\n");



}


void print_decompression(char *filename)
{
     printf("********************************************************************************************************************\n");
    printf("             DECOMPRESSING THE INPUT FILE :%s\n",filename);
     printf("********************************************************************************************************************\n");


}



char * extract_file_name(char * file_path)
{

   char *token;

   /* get the first token */
   token = strtok(file_path, "/");

   char * ret;
   /* walk through other tokens */
   while( token != NULL ) {

      ret = token;

      token = strtok(NULL, "/");
   }
   return ret;

}

//AABAB

/*
Initialize table with single character strings
  2     P = first input character
  3     WHILE not end of input stream
  4          C = next input character
  5          IF P + C is in the string table
  6            P = P + C
  7          ELSE
  8            output the code for P
  9          add P + C to the string table
  10           P = C
  11         END WHILE
  12    output code for P
*/

void compress(char *file_name, char * output_folder, char * new_file_name)
{

    code_size = 8;
    dictionary_size = 255;
    leftOver = 0;
    leftValue = 0;

   // puts(output_folder);
    mkdir(output_folder);



//    int file_name_length = strlen(file_name);

    /*

     How to create a output file path from given output folder path and input file path
     extract the file name from the input file path ie. output file name
     for extract purpose used the function extract file name also copied the file name in 
     copy_file_name because if called extract directly on the input_file_name then it may
      get changed  copy the output folder path in another new output_file_path.
 
    */
    int i;
    char output_file_name[MAX_PATH];

    for( i=0 ; i< strlen(new_file_name);i++)
    {
        output_file_name[i] = new_file_name[i];
    }



    output_file_name[i] = '\0';

    char *extension = ".bin";

    int length_to_be_appended = strlen(extension);

    strncat(output_file_name,extension, length_to_be_appended);

    char  output_file_path[MAX_PATH];

    for( i=0;i<strlen(output_folder);i++)
    {

        output_file_path[i] = output_folder[i];
    }



    output_file_path[i] = '\0';

    strcat(output_file_path,output_file_name);



    FILE *input_file = fopen(file_name,"r");




    if(input_file == NULL)
    {
        error_handler(ERR_OPEN);
    }


    FILE * output_file = fopen(output_file_path, "w+b");

    if(output_file == NULL)
    {

        error_handler(ERR_OPEN);

    }


    encoding_dictionary root;
    //initialize the encoding dictionary
    init_encoding_dictionary(&root);

    //This stores the current pattern
    //the maximum pattern length can be 32513
    char pattern[32515] ;

   //x<<y == x*2^y

    if(dictionary_size == ((1 << code_size)-1))
    {
        code_size++ ;
    }

    //initiate pattern with the first character of the input
    pattern[0] = fgetc(input_file);

    pattern[1] = '\0';

    //code from the dictionary
    int code;
    //flg is used to check whether the current pattern is present in the dictionary or not
    //if flg = -1 not present
    //else present
   
    char c;
    while ((c = fgetc(input_file)) != EOF)
    {
       
        //tmp is temporary pattern which we need to check
        char tmp[32515] = {'\0'};

        strcpy( tmp, pattern);

        strncat(tmp , &c , 1);

        int flg = search_pattern( root ,tmp );   // AABABA

        //if the tmp  is present then update pattern with tmp.
        if(flg != -1)
        {
                strncat(pattern, &c, 1);
        }
        //find the code for the "pattern" and output it and then again start the pattern with current character.
        else
        {
                //search the pattern in dictionary.
                code = search_pattern( root ,pattern );


                //write to output file
                write_binary(output_file, code,code_size);
                //if the code written is equal to 2^ (limit)-1
                //then increase the limit size

                //insert the pattern which was not present i.e.tmp
                insert_pattern(&root, tmp);
                if(dictionary_size == ((1 << code_size )-1))code_size++;

                //restart the pattern from the first character.
                pattern[0] = c;
                pattern[1] = '\0';

        }


    }

   code  = search_pattern( root , pattern );

   write_binary(output_file, code ,code_size);

   if (leftOver > 0) fputc(leftValue<<(8-leftOver), output_file);

   destroy_encoding_dictionary(root);


   fclose(output_file);

   fclose(input_file);
   output_file_size = get_file_size(output_file_path);
   input_file_size = get_file_size(file_name);

   print_info(file_name);

    return ;
}


// 65 66 256 67
//ABABC
/*
Read OLD_CODE
output OLD_CODE
CHARACTER = OLD_CODE
WHILE there are still input characters DO
Read NEW_CODE
IF NEW_CODE is not in the translation table THEN
STRING = get translation of OLD_CODE
STRING = STRING+CHARACTER
ELSE
STRING = get translation of NEW_CODE
END of IF
output STRING
CHARACTER = first character in STRING
add OLD_CODE + CHARACTER to the translation table
OLD_CODE = NEW_CODE
END of WHILE
*/

void decompress(char *file_name, char * output_folder, char * new_file_name)
{

    print_decompression(file_name);
                                   
    //remove this                     
     mkdir(output_folder);


   // int file_name_length = strlen(file_name);

    /*

     How to create a output file path from given output folder path and input file path
     extract the file name from the input file path ie. output file name
     for extract purpose used the function extract file name also copied the file name in copy_file_name because if called extract directly on the input_file_name then it may get changed
     copy the output folder path in another new output_file_path.

    */
    int i;

    char output_file_name[MAX_PATH];

    for( i=0 ; i< strlen(new_file_name);i++)
    {

        output_file_name[i] = new_file_name[i];


    }


    output_file_name[i] = '\0';


    char *extension = ".txt";

    int length_to_be_appended = strlen(extension);


    strncat(output_file_name,extension, length_to_be_appended);


    char  output_file_path[MAX_PATH];


    for( i=0;i<strlen(output_folder);i++)
    {

        output_file_path[i] = output_folder[i];
    }



    output_file_path[i] = '\0';

    strcat(output_file_path,output_file_name);



    leftOver = 0;
    leftValue = 0;

    dict_element decoding_dictionary[32768];
    init_decoding_dictionary(decoding_dictionary);

 //ababc
//65 66 256 67 
    int prev_code;
    int curr_code;

    char ch = 'b';

    dictionary_size = 255;
    code_size = 8;


   if(dictionary_size == (( 1 << code_size )- 1 ) )code_size++;


    FILE *input_file = fopen(file_name,"r+b");

    FILE *output_file = fopen(output_file_path,"w");



    prev_code = read_binary(input_file, code_size );


    get_output(prev_code , &ch, output_file, decoding_dictionary);


    while((curr_code =  read_binary(input_file, code_size ))!= -1)
    {
        char tmp_ch;

        if(curr_code > dictionary_size)   
        {
            get_output(prev_code , &tmp_ch, output_file, decoding_dictionary);

            fputc(ch,output_file);
        }
        else
        {
            get_output( curr_code , &tmp_ch , output_file, decoding_dictionary );
        }
  //ch=b;
        ch = tmp_ch;

        add_element_to_dictionary( prev_code , ch, decoding_dictionary);

        if(dictionary_size == ((1 << code_size )-2))code_size++;
        //If you are decoding from codes to indexes, you need to increase your
        // code size as soon as you add the code value that is equal to 2^(current code size)-1 to your code table.
        //That is, the next time you grab the next section of bits, you grab one more

        prev_code =  curr_code;
    }

    fclose(input_file);
    fclose(output_file);
    return ;
}

