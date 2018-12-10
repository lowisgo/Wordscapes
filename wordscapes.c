/***
	CMSC 142 Project: Wordscapes
	Submitted by:
		Arquero, Kristine M.
		Go, Lois Angelica B.
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#include <windows.h>
#include "wordscapes.h"

int main(int argc, char **argv){

	int word_size, hint_size, file_size, max_char=50, len, lent, result, is_file_empty = 0;
	char dict_word[max_char], str[max_char], temp1[max_char], temp2[max_char];
	char *filename;

	word_size = strlen(argv[1]);
	hint_size = strlen(argv[2]);

	/*** reading words.txt ***/
	FILE *rfile_ptr;
	filename = "./words.txt";
	rfile_ptr = fopen(filename, "r");

	if (rfile_ptr == NULL){
		printf("Could not open words.txt file.\n");
		return 1;
	}

	/*** writing dictionary.txt ***/
	FILE *wfile_ptr;
	wfile_ptr = fopen("./dictionary.txt", "w");

	if (argc > 1){

		//Beep(750, 500);

		red();
		printf("\n------------------------------------------------------------\n");
		printf("\t\t\t WORDSCAPES");
		printf("\n------------------------------------------------------------\n");
		reset();

		yellow();
		printf("\t Word: %s\n", argv[1]);
		printf("\t Hint: %s\n", argv[2]);
		reset();

		if (word_size >= hint_size){

			// writing to the internal dictionary
			file_size = 0;
			while (fgets(dict_word, max_char, rfile_ptr) != NULL){
				int length = strlen(dict_word);
				if (dict_word[length-1] == '\n') dict_word[length-1] = '\0';

				lower_string(dict_word);

				if ((char_compare(argv[1], dict_word) == 1) && (strlen(dict_word) == hint_size)){
					if (compatible(argv[2], dict_word) == 1){
						fprintf (wfile_ptr, "%s\n", dict_word);
						file_size++;
					}
				}
			}

			// Closing files and freeing memory
			fclose(rfile_ptr);
			fclose(wfile_ptr);

			//check if dictionary has content
			FILE *fp = fopen( "./dictionary.txt","r" );
			if (NULL != fp) {
			    fseek (fp, 0, SEEK_END);
			    int size = ftell(fp);

			    if (0 == size) {
			    	green();
					printf("\n\t Word does not exist. \n");
					reset();
			        is_file_empty = 1;
			    } 
			}

			fclose(fp);

			if(is_file_empty == 0){
				// backtracking
				green();
				printf("\n\t Possible Answers:\n");
				reset();
				combination(argv, word_size, hint_size);
				permutation(hint_size, file_size);
				//Beep(750, 500);	
			}

			

		} else printf("Invalid input.\n");
	} else printf("Invalid input.\n");

	red();
	printf("\n============================================================\n");
	reset();
	return(0);
}