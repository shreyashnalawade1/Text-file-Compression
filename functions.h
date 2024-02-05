#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED


typedef struct trie_node{

    char data;
    int index; 
    struct trie_node *child[256];


}trie_node;






typedef trie_node * encoding_dictionary;


void init_encoding_dictionary(encoding_dictionary *);

/*This function will return index if we find the pattern
else will return -1
*/
int search_pattern(encoding_dictionary t, char * p);

void insert_pattern(encoding_dictionary *t, char * s);

trie_node * get_node(char c, int d);

void destroy_encoding_dictionary(encoding_dictionary t);

typedef struct dict_element{

    int prefix_code;
    char curr_char;

}dict_element;


void init_decoding_dictionary(dict_element* decoding_dictionary);

void get_output(int code, char *t, FILE * op, dict_element* decoding_dictionary);

void add_element_to_dictionary(int p, char c, dict_element* decoding_dictionary);

#endif // FUNCTIONS_H_INCLUDED
