// attempt to understand how pointer manipulation work in C
/*
int x = 5;
x -> [ 5 ]
	^ address : 0x1000
variable is a named box that directly stored a value

int *p = &x;
p -> [ 0x1000 ]
		^
		|
x -> [ 5 ]

and *p = 20; (dereferencing)
*p means to go to the memory location stored in p and use the value there
so it modifies x indirectly; now x becomes 20;

for function parameters i take in the address of the memory block, and then manipulate it
*/
#include <stdio.h>
#include <stdlib.h>

#define TAPE_SIZE 30000
/*
a tape is an array of 30k cells, each single byte is an unsigned char

ad pointer ptr is used to refer to the first element of the tape array -> &tape[0]

but we dont use tape[index] instead move the pointer forward/backward (++ptr, --ptr) to "walk" through memory
*/

void bf(const char *code) {
	unsigned char tape[TAPE_SIZE] = {0};
	// a tape to store the data
	unsigned char *ptr = tape;
	// the mem address of the first index element of the tape
	const char *pc = code;
	// this is for going through the .bf characterwise -> just a string contianing the bf source code
	// pc is a pointer walking through the string to help us work with individual character

	// *pc is the current command character
	while (*pc) {
		switch (*pc) {
		// pretty self explanatory part
		// we move the pointer left/right -> changing the pointer address
		// to access different index elements from the array
		// moving the pointer a byte forward or backward
		case '>':++ptr;break;
		case '<':--ptr;break;
		// we +/- the value of that particular tape position

		// *ptr means "THE VALUE STORED AT THE MEMORY THAT ptr POINTS TO!"
		case '+':++*ptr;break;
		case '-':--*ptr;break;

		// IO handling here -> character wise
		case '.':putchar(*ptr);break;
		case ',':*ptr = getchar();break;

		// perhaps the only slighly tricky part
		case '[':
			// the data pointer checks whether the current cell is zero or not
			// if 0, then it skips to the command AFTER the matching ]
			if(*ptr == 0) {
				int depth = 1;
				// to keep a check of the number of opening brackets
				while (depth > 0) {
					pc++;
					// moving the pointer
					if (*pc == '[') depth++;
					else if (*pc == ']') depth--;
				}
			}
			break;

		case ']':
			if(*ptr != 0){
				int depth = 1;
				while (depth > 0) {
					pc--;
					if (*pc == '[') depth--;
					else if (*pc == ']') depth++;
				}
			}
			break;
		}
		pc++;
		// we increment the position
	}
}

int main(int argc, char **argv) {
	if (argc < 2) {fprintf(stderr, "Usage: %s <file.bf>\n", argv[0] );return 1;}

	FILE *f = fopen(argv[1], "r");
	// *f is pointer to FILE structure and it's opended in read mode
	// it aint the fie itself, it's a pointer to a structure in memory that represents the file (with other info like file pos, buffer etc)
	if (!f) {perror("Error opening file");return 1;}

	fseek(f, 0, SEEK_END);
	// going to the ending file position to the end of the file
	// we get the current file position with ftell(f), which will be equal to the file size in bytes
	long size = ftell(f);
	rewind(f); // rewind back to the start

	// dynamic memory allocations
	char *code = malloc(size + 1);
	// that extra byte is for the null terminator \0
	// malloc returns a pointer to the beginning of that block (char *code)
	if (!code) {perror("malloc");return 1;}

	fread(code, 1, size, f);
	// copying entire file into the memory pointer to by code
	code[size] = '\0';
	fclose(f);
	/* summing that up, what i see is
	fopen -> fseek + ftell -> malloc -> fread -> fclose :: releasing the file handle, and then using code as a pointer to the program text -> free the memory block */

	bf(code);

	free(code);
	return 0;
}
