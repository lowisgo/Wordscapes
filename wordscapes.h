/***
	CMSC 142 Project: Wordscapes
	Submitted by:
		Arquero, Kristine M.
		Go, Lois Angelica B.
***/

void red() {
	printf("\033[0;31m");
}

void green() {
	printf("\033[0;32m");
}

void yellow() {
	printf("\033[0;33m");
}

void reset() {
	printf("\033[0m");
}

int char_search(char *word, char character){
	int flag = 0;

	for (int i=0; i<strlen(word); i++){
		if (word[i] == character){
			flag = 1;
			break;
		}
	}

	return flag;
}

int char_compare(char *given_word, char *word){
	int flag = 0;

	for (int i=0; i<strlen(word); i++){
		if (char_search(given_word, word[i]) != 1){
			flag = 0;
			break;
		} else {
			flag = 1;
		}
	}

	return flag;
}

int compatible(char *hint_word, char *word){
	int flag = 0;

	for (int i=0; i<strlen(hint_word); i++){
		if (hint_word[i] != '_'){
			if(hint_word[i] == word[i]){
				flag = 1;
			} else {
				flag = 0;
				break;
			}
		} else {
			flag = 1;
		}
	}
	return flag;
}

<<<<<<< HEAD
void lower_string(char s[]) {
	int c = 0;
   
	while (s[c] != '\0') {
		if (s[c] >= 'A' && s[c] <= 'Z') {
			s[c] = s[c] + 32;
		}
		c++;
	}
}

=======
>>>>>>> fb77243f99e7a7ec1158577caaa868f355dafe16
void combination(char **input, int word_size, int hint_size){
	int start, move, i, candidate, N;
	int nopts[word_size+2];
	int option[word_size+2][word_size+2];
	char test[hint_size];

	FILE *cfile_ptr;
	cfile_ptr = fopen("./combination.txt", "w");

	move=start=0;
	nopts[start]=1;

	while(nopts[start]>0){
		if(nopts[move]>0){
			nopts[++move] = 0;
			for(i=1;i<move;i++){
				char init = input[1][option[i][nopts[i]]];
				char string[2];
				string[0] = init;
				string[1] = '\0';
				test[i-1] = init;
			} 

			if (strlen(test) == hint_size){
				test[hint_size] = '\0';
				fprintf(cfile_ptr, "%s\n", test);
			}

			for(candidate=word_size;candidate>=0;candidate--){
				for(i=move-1;i>=1;i--){
					if(option[i][nopts[i]]>=candidate) break;
				}
				if(!(i>=1))
					option[move][++nopts[move]]=candidate;
			}			
		}
		else nopts[--move]--;
	}
	fclose(cfile_ptr);
}

void permutation(int hint_size, int file_size){
	int max_char=50, lent, flag = 0;
	char combi_word[max_char], temp2[max_char], str[max_char];
	int cnt = 0;

	int duplicate[file_size];

	for (int i=0; i<file_size; i++){
		duplicate[i] = 0;
	}

	FILE *pfile_ptr;
	char *filename = "./combination.txt";
	pfile_ptr = fopen(filename, "r");

	FILE *fcomp;
	fcomp = fopen("./dictionary.txt", "r");

	if (pfile_ptr == NULL){
		printf("Could not open combination.txt file.\n");
	} else {
		while (fgets(combi_word, max_char, pfile_ptr) != NULL){
			int length = strlen(combi_word);
			if (combi_word[length-1] == '\n') combi_word[length-1] = '\0';

			int nopts[hint_size+2];
			int option[hint_size+2][hint_size+2];
			int start, move, i, candidate;
			char test[hint_size];

			move = start = 0;
			nopts[start] = 1;

			while(nopts[start]>0){
				if(nopts[move]>0){
					nopts[++move] = 0;

					if (move > hint_size){
						for(i=1; i<move; i++){
							char init = combi_word[option[i][nopts[i]]];
							char string[2];
							string[0] = init;
							string[1] = '\0';
							test[i-1] = init;
						}
						test[hint_size] = '\0';

						//compare in dictionary.txt
						int linenum = 0;
						while ((fgets(temp2, max_char, fcomp)) && flag == 0){

							cnt++;
							lent = strlen(temp2);
							if( temp2[lent-1] == '\n' ) temp2[lent-1] = 0;
								
							if(strcmp(test, temp2) == 0 && duplicate[linenum] != 1){
								green();
								printf("\t\t - ");
								reset();
								printf("%s\n", temp2);
								duplicate[linenum] = 1;
								break;
							}

							linenum++;
						}
						fseek(fcomp, 0, SEEK_SET);
										
					} else {
						for(candidate=hint_size-1; candidate>=0; candidate--){
							for(i=move-1; i>=1; i--){
								if(option[i][nopts[i]] == candidate) break;
							}
							if(!(i>=1))
								option[move][++nopts[move]] = candidate;
						}				
					}
				} else nopts[--move]--;
			}
		}		
	}

	fclose(pfile_ptr);
	fclose(fcomp);
}
