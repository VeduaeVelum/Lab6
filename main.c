# Lab6
#include "filework.h"

bool help(void);
bool show_file(void);

int main(int argc, char** argv)
{
	typedef bool(*func_p)();
	int i, j;
	bool flag = false;
	func_p function_pointer[NUMBER_OF_COMANDS] = { help, show_file, determine_repeating_words };
	char optStrings[NUMBER_OF_COMANDS][WORD_LENGTH] = {
		{ "help" },
		{ "see" },
		{ "determine" } };
	for (i = 1; i < argc; i++)
	{
		for (j = 0; j < NUMBER_OF_COMANDS; j++)
		{
			if (strcmp(argv[i], optStrings[j]) == 0)
			{
				flag = function_pointer[j]();
				break;
			}
		}
	}
	if (flag == false)
	{
		printf("\nIn the course of an error occurred\n");
		return 1;
	}
	return 0;
}
bool help(void)
{
	puts("List of comands:");
	puts("                 see - to look throw the file information");
	puts("                 determine - to calculate number of repeating word");
	puts("                 help - to see list of comands");
	return true;
}
bool show_file(void)
{
	FILE *f;
	char *string;
	if (!(f = fopen("input_file.txt", "r+t")))
	{
		printf("File couldn't be opened. Maybe it doesn't exist\n");
		return false;
	}
	string = (char*)calloc((STRING_LENGTH + 1), sizeof(char));
	while (fgets(string, STRING_LENGTH, f))
	{
		puts(string);
	}
	fclose(f);
	free(string);
	return true;
}
