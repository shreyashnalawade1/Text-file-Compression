#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<getopt.h>
#include <dirent.h>
#include <sys/stat.h>
#include"error.h"
#include"algorithms.h"
#include"common.h"


void print_help();

void folder_compress(char *folder_name, char *);

void folder_decompress(char *folder_name, char *);

int isDirectory(const char *path);

//This function takes the folder path
void construct_output_folder_name( char * input_name , char *output_name, char * output_folder_path)
{
    //needed for strncat function
    int len = strlen(input_name);

    int i;

    //copy the path in output folder path
    for( i=0; i< len; i++)
    {
        output_folder_path[i] = input_name[i];
    }

    output_folder_path[i] = '\0';

    int len1 = strlen(output_folder_path);
    int index;
    for(int i=len1-1;i>=0;i--)
    {
        if(output_folder_path[i] == '/')
        {
            index = i;
            break;

        }

    }
    index++;
    //a
    //ab
    len = strlen(output_name);
    for(int i=0;i<len;i++)
    {
        output_folder_path[index++] = output_name[i];

    }
    output_folder_path[index] = '\0';




}


int isDirectory(const char *path) {

   struct stat statbuf;

   if (stat(path, &statbuf) != 0)

       return 0;  // upon the successful compilation stat returns zero else -1

   return S_ISDIR(statbuf.st_mode);
}

//argc stores the value of total number of parameters
int main(int argc, char **argv)
{
    //if only one argument is passed
	if(argc == 1)
    {
       error_handler(ERR_INVALID_COMMAND);
    }
    else if( argc == 2)
    {

        if( strcmp(argv[1], "--help") == 0 ){

            print_help();

            return 0;
        }
        else
        {
           error_handler(ERR_INVALID_COMMAND);

        }

    }
    else if( argc == 6){

           char* input_name = NULL;
           char* output_name = NULL;
           int c_flag = 0; //compression
           int d_flag = 0;  //decomp
           int o_flag = 0;  //input file
           int i_flag = 0;
           int opt;
           //':' before c will help to return : for missing argument instead of ?
      // ./c.exe -c -i a.txt -o a
           while ((opt = getopt(argc, argv, ":cdi:o:")) != -1) {
               switch (opt) {
               case 'c':
                      c_flag = 1;
                      break;

               case 'd':
                        d_flag = 1;
                        break;

                case 'i':
                        input_name = optarg;
                        i_flag = 1;
                        break;

               case 'o' :
                        output_name = optarg;
                        o_flag = 1;
                        break;

               case ':' :
                         error_handler(ERR_INVALID_COMMAND);
                        break;
               default  :
                        error_handler(ERR_INVALID_COMMAND);
                        break;

               }

           }


           //only c or d  flag must be present and o flg  and i flag must be present
           if(((c_flag == 0 && d_flag == 1)|| (d_flag == 0 && c_flag == 1)) && o_flag == 1 && i_flag == 1){
                if(c_flag == 1)
                {

                        //check if directory
                        if(isDirectory(input_name))
                        {

                            char output_folder_path[MAX_PATH];

                            construct_output_folder_name(input_name, output_name,output_folder_path);

                            folder_compress(input_name,output_folder_path);


                        }
                        else
                        {

                                //copy the path from input name to output folder path
                                char output_folder[MAX_PATH];

                                int len = strlen(input_name);

                                strcpy(output_folder,input_name);

                                int i;

                                for( i = len-1; i >= 0; i--)
                                {
                                    if(output_folder[i] == '/')
                                    {
                                      break;
                                    }
                                }

                                i++;

                                output_folder[i] = '\0';

                                compress(input_name,output_folder,output_name);
                        }
                }
                else if(d_flag == 1)
                {
                                if(isDirectory(input_name))
                               {
                                    char output_folder_path[MAX_PATH];

                                    construct_output_folder_name(input_name, output_name,output_folder_path);

                                    folder_decompress(input_name,output_folder_path);


                                }
                                else
                                {
                                //copy the path from input name to output folder path
                                    char output_folder[MAX_PATH];

                                    int len = strlen(input_name);

                                    strcpy(output_folder,input_name);

                                    int i;

                                    for( i = len-1; i >= 0; i--)
                                    {
                                        if(output_folder[i] == '/')
                                        {
                                            break;
                                        }
                                    }

                                    i++;

                                    output_folder[i] = '\0';

                                    decompress(input_name,output_folder,output_name);
                        }

                }

           }
           else
           {
               error_handler(ERR_INVALID_COMMAND);

           }
    }
    else
    {

        error_handler(ERR_INVALID_COMMAND);

    }

}




void print_help(){

    printf("This program can compress and decompress text files\n");
    printf("Usage: ./program [-cd][-i][input file/folder name][-o][output file/folder name]\n");
    printf("-c : Compress\n");
    printf("-d : Decompress\n");
}




void folder_compress(char * basePath, char *output_file_string){



    char path[MAX_PATH];

    DIR *dir;// pointer to opened directory

    struct dirent *dp;  // pointer to stuffs inside the directory

    //check if this is a folder

    if(isDirectory(basePath))
    {
        dir = opendir(basePath);

        // Unable to open directory stream
        if (!dir){

            error_handler(ERR_OPEN );


        }

        while ((dp = readdir(dir)) != NULL)
        {
            if (strcmp(dp -> d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) // checks if it if base dir or not
            {

                // Construct new path from our base path
                strcpy(path, basePath);
                strcat(path, "/");
                strcat(path, dp->d_name);

                if(isDirectory(path))
                {

                    //create a output string by appending compressed
                    char to_be_appended[MAX_PATH] = "/";

                    //int length = strlen(dp->d_name);

                    strcat(to_be_appended,dp->d_name);


                    char   output_file_string_new[MAX_PATH];

                    int i = 0;

                    for(i=0; i< strlen(output_file_string);i++)
                    {
                        output_file_string_new[i] = output_file_string[i];
                    }

                    output_file_string_new[i] = '\0';

                    strcat(output_file_string_new,to_be_appended);

                    folder_compress(path,output_file_string_new);
                }
                else
                {

                   char new_output_string[MAX_PATH];

                   int i;

                   for( i=0; i< strlen(output_file_string);i++)
                   {
                       new_output_string[i] = output_file_string[i];
                   }

                   new_output_string[i] = '\0';

                   strcat(new_output_string,"/");

                   char new_file_name[MAX_PATH];

                   for( i=strlen(path)-1;i>=0;i--)
                   {
                       if(path[i] == '/')break;

                   }
                   int index = 0;

                   for(int j = i+1 ; j < strlen(path);j++)
                   {
                       if(path[j] == '.')
                        break;

                       new_file_name[index++] = path[j];
                   }

                   new_file_name[index] = '\0';
                   compress(path,new_output_string,new_file_name);


                }

        }
    }

        closedir(dir);
    }
    else
    {

        error_handler( ERR_INVALID_FORMAT );
    }



}

void folder_decompress(char * basePath, char *output_file_string){

   char path[MAX_PATH];

    DIR *dir;

    struct dirent *dp;

    //check if this is a folder

    if(isDirectory(basePath))
    {
        dir = opendir(basePath);

        // Unable to open directory stream
        if (!dir){

            error_handler(ERR_OPEN );


        }

        while ((dp = readdir(dir)) != NULL)
        {
            if (strcmp(dp -> d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
            {

                // Construct new path from our base path
                strcpy(path, basePath);

                strcat(path, "/");

                strcat(path, dp->d_name);

                if(isDirectory(path))
                {

                    //create a output string by appending compressed
                    char to_be_appended[MAX_PATH] = "/";

                    //int length = strlen(dp->d_name);

                    strcat(to_be_appended,dp->d_name);


                    char   output_file_string_new[MAX_PATH];

                    int i = 0;

                    for(i=0; i< strlen(output_file_string);i++)
                    {
                        output_file_string_new[i] = output_file_string[i];
                    }

                    output_file_string_new[i] = '\0';

                    strcat(output_file_string_new,to_be_appended);

                    folder_decompress(path,output_file_string_new);
                }
                else
                {

                   char new_output_string[MAX_PATH];

                   int i;

                   for( i=0; i< strlen(output_file_string);i++)
                   {
                       new_output_string[i] = output_file_string[i];
                   }

                   new_output_string[i] = '\0';

                   strcat(new_output_string,"/");

                   char new_file_name[MAX_PATH];

                   for( i=strlen(path)-1;i>=0;i--)
                   {
                       if(path[i] == '/')break;

                   }

                   int index = 0;

                   for(int j = i+1 ; j < strlen(path);j++)
                   {
                       if(path[j] == '.')break;

                       new_file_name[index++] = path[j];
                   }


                   new_file_name[index] = '\0';

                   decompress(path,new_output_string,new_file_name);
                }

        }
    }

            closedir(dir);
    }
    else
    {

        error_handler( ERR_INVALID_FORMAT );
    }
}

