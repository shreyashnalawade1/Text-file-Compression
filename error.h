#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

enum ERR_STATES {

    //if the command is not valid
    ERR_INVALID_COMMAND = 0,

    //if the given file format is neither image nor the text file.
    ERR_INVALID_FORMAT,

    //file/folder opening error
    ERR_OPEN


};


void error_handler(int error_type);
#endif // ERROR_H_INCLUDED
