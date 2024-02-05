#ifndef ALGORITHMS_H_INCLUDED
#define ALGORITHMS_H_INCLUDED

extern int dictionary_size;
extern int input_file_size;
extern int output_file_size;
/*
Now testing the compress with an input string
after file name will be passed and
will open the file in function
*/
void compress(char *, char * , char *);

//void decompress(int * encoded, int size);
void decompress(char *, char *, char *);


long int get_file_size(char *filename);

void print_decompression(char *filename);
void print_compression();

void print_info(char *file_name);

#endif // ALGORITHMS_H_INCLUDED
