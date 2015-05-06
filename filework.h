#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define STRING_LENGTH 25
#define WORD_LENGTH 25
#define NUMBER_OF_COMANDS 3

struct queue_words
{
	char *word;
	int repeating_number;
	struct queue_words *next;
};
struct stack_words
{
	char *word;
	struct stack_words *next;
};

bool determine_repeating_words(void);
bool print_results(struct stack_words *st);
bool func_delete(struct stack_words *st);
struct stack_words *insert_word(struct stack_words *st, char *word);
void queue_push(struct stack_words *st, char *word);
