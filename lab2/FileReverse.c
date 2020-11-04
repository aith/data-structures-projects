//Name: Ari Iramanesh
//CruzID: 1628897
//CMPS12M
//
//Role: takes a file as input and reverses each word in input. The reversed
//  input is then printed to an output file, newline after newline.
//
//Instructions for running: use the "make" command to receive the executable,
//  "FileReverse." The executable runs on the command line, and takes two
//  additional arguments: <input> <output>. The results are found in the
//  <output> file. 
//
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stringReverse(char* s){ //accesses by pointer, so by reference
    int s_length = strlen(s);
    int front= 0;
    int back = s_length - 1;
    
    while(front<back){
    char new_front_temp = s[back];
    s[back] = s[front];
    s[front] = new_front_temp;
    front++;
    back--;
    }
}

int main(int argc, char* argv[]){
    FILE* input;
    FILE* output;
    char word[256];
    // int word_length = 0;

    if( argc != 3){
     printf("Incorrect syntax. Usage: %s <input file> <output file>\n", argv[0]);
    exit(EXIT_FAILURE);
    }
    //OPEN INPUT FILE FOR READING
    input = fopen(argv[1], "r");
    if(input==NULL){
        printf("Can't read file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    //OPEN OUTPUT FOR WRITING
    output = fopen(argv[2], "w");
    if( output == NULL ){
        printf("Unable to write to file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    //READ FROM INPUT INTO TEMP STRING, REVERSE IT, THEN PRINT INTO OUTPUT FILE
    while(fscanf(input, "%s", word) != EOF){
        //Reversal algorithm
        
       stringReverse(word);
    
       fprintf(output, "%s\n", word);
    }
    fclose(input);
    fclose(output);

    return(EXIT_SUCCESS);
}

