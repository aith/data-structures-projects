//-----------------------------------------------------------------------------
//charType.c
//
//owner: Ari Iramanesh
//cruzID: 1628897
//class: 12M
//
//    Takes a file's text as input and determines how many different character
//    types there are, as well as specifying them, into an output file.

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<assert.h>
#include<string.h>

#define MAX_STRING_LENGTH 100

// function prototype 
void extract_chars(char* s, char* a,char* d,char* p, char* w);

// function main which takes command line arguments 
int main(int argc, char* argv[]){
   FILE* in;        // handle for input file                  
   FILE* out;       // handle for output file                 
   char* line;      // string holding input line              
   char* alpha; // string holding all alpha-numeric chars 
   char* numeric;
   char* punct;
   char* whitespace;
   int line_count=0;

   // check command line for correct number of arguments 
   if( argc != 3 ){
      printf("Usage: %s input-file output-file\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   // open input file for reading 
   if( (in=fopen(argv[1], "r"))==NULL ){
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }

   // open output file for writing 
   if( (out=fopen(argv[2], "w"))==NULL ){
      printf("Unable to write to file %s\n", argv[2]);
      exit(EXIT_FAILURE);
   }

   // allocate strings line and alpha_num on the heap 
   line = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   alpha = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   numeric = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   punct = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   whitespace = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   assert( line!=NULL && alpha!=NULL && numeric!=NULL && punct!=NULL && whitespace!=NULL); //check

   // read each line in input file, extract alpha-numeric characters 
   while( fgets(line, MAX_STRING_LENGTH, in) != NULL ){ //fgets continues until newline or eof
      line_count++;
      extract_chars(line, alpha, numeric, punct, whitespace);
      fprintf(out, "line %d contains:\n %d alphabetic characters: %s\n %d numberic characters: %s\n %d punctuation characters: %s\n %d whitespace characters: %s\n", line_count, strlen(alpha),
                         alpha, strlen(numeric), numeric, strlen(punct), punct,
                         strlen(whitespace), whitespace);
   }

   // free heap memory 
   free(line);
   free(alpha);
   free(numeric);
   free(punct);
   free(whitespace);

   // close input and output files 
   fclose(in);
   fclose(out);

   return EXIT_SUCCESS;
}

// function definition 
void extract_chars(char* s, char* a,char* d,char* p, char* w){
   int i=0, j=0, digi=0, puncti=0, spacei=0;
   while(s[i]!='\0' && i<MAX_STRING_LENGTH){
      if( isalpha( (int) s[i]) ) a[j++] = s[i];
      if( isdigit( (int) s[i]) ) d[digi++] = s[i];
      if( ispunct( (int) s[i]) ) p[puncti++] = s[i];
      if( isspace( (int) s[i]) ) w[spacei++] = s[i];
      i++;
   }
    a[j] = '\0';
    d[digi] = '\0';
    p[puncti] = '\0';
    w[spacei] = '\0';
}
