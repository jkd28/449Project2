/**************** 
John Dott 
CS 449: Project 2 Part 1
mystrings
Due 2/26/17
*****************/
#include <stdio.h>
#include <stdlib.h>

/*method to determine if a character is printable*/
int isValid(char character){
	if((character>=32) && (character<=126)){
		return 1;
	} else {
		return 0;
	}
}

/*gets strings of length > 4 and prints them to the screen*/
void getStrings(FILE *f){
	int current_offset, i;
	int result, count=0;
	char c;
	char *string;
	/*check for strings of length > 4*/
	result=1;
	while(result != 0){
		//read a character  
		result = fread(&c, sizeof(char),1,f);
		
		//while characters are valid, increment a count
		while(isValid(c) && (result !=0)){
			count++;
			result = fread(&c, sizeof(char),1,f); //get next character
		}
		
		/*if there are less than 4 valid characters in a row, skip the rest of the loop */
		if(count < 4){
			count = 0;
			continue;
		} else {
		/*if there are >=4 characters in a row, reread all the characters, generate string, print string, free string*/	
			/*get the current location in the file*/
			current_offset = ftell(f);
			/*seek back to the beginning of our string*/
			fseek(f, (current_offset-(count+1)), SEEK_SET);
			/*allocate appropriate memory for the string*/
			string = malloc((count+1)*sizeof(char));
			/*get the characters for the string*/
			for(i=0; i < count; i++){
				fread(&string[i],sizeof(char),1,f);
			}
			string[count] = '\0'; /*be sure to add the NUL terminator to complete the string */
			
			printf("%s\n",string); /*print the string*/
			
			free(string);/*free the string's allocated memory*/
			count = 0; /*reset count */
			fseek(f, current_offset, SEEK_SET);
		}
	}	
}

int main(int argc, char *argv[]){
	/*variable initializations*/
	char c;
	int inString = 0;
	int charCount = 0;
	
	/*open the file*/
	FILE *f = fopen(argv[1], "rb");
	if(f == NULL){
		printf("ERROR: Input File Does Not Exist. Terminating Program.\n");
		return 1;
	}	
	getStrings(f);
	fclose(f);
	return 0;
}