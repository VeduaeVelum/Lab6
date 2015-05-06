#include "filework.h"

struct queue_words *q_first = { NULL }, *q_last = { NULL };

bool determine_repeating_words(void)
{
	int i = 0;
	struct stack_words *st = { NULL };
	FILE *f;
	char symbol;
	bool flag = false;
	if (!(f = fopen("input_file.txt", "r+t")))
	{
		printf("File couldn't be opened. Maybe it doesn't exist\n");
		return false;
	}
	if (!(st = (struct stack_words*)calloc(1, sizeof(struct stack_words))) ||
		!(st->word = (char*)calloc((STRING_LENGTH + 1), sizeof(char))))
	{
		printf("Memory is not allocated\n");
		func_delete(st);
		exit(-1);
	}
	while (1)
	{
		if (feof(f)) break;
		fscanf(f, "%c", &symbol);
		flag = true;
		if (symbol >= 'a' && symbol <= 'z')
		{
			st->word[i++] = symbol;
		}
		else
		{
			if (i != 0)
			{
				st = insert_word(st, st->word);
				i = 0;
			}
		}
	}
	flag = true;
	flag = print_results(st);
	flag = func_delete(st);
	fclose(f);
	return (flag == false) ? false : true;
}
bool print_results(struct stack_words *st)
{
	FILE *f;
	struct queue_words *q_current;
	if (q_first == NULL)
	{
		printf("There are not words into the file\n");
		return true;
	}
	if (!(f = fopen("output_file.txt", "a+t")))
	{
		printf("File couldn't be opened for unknown reasons\n");
		func_delete(st);
		return false;
	}
	fprintf(f, "\t\tDetermined results: \n");
	q_current = q_first;
	do
	{
		fprintf(f, "The word %s repeats at file %d times\n", q_current->word, q_current->repeating_number);
		q_current = q_current->next;
	} while (q_current != NULL);
	fclose(f);
	return true;
}
bool func_delete(struct stack_words *st)
{
	struct queue_words *q_current;
	struct stack_words *top;
	if (q_first == NULL && st == NULL)
	{
		return true;
	}
	q_current = q_first;
	while (q_current != NULL)
	{
		q_first = q_current;
		q_current = q_first->next;
		free(q_first->word);
		free(q_first);
	}
	while (st != NULL)
	{
		top = st;
		st = st->next;
		free(top->word);
		free(top);
	}
	return true;
}
struct stack_words *insert_word(struct stack_words *st, char *word)
{
	struct queue_words *q_current;
	struct stack_words *top = { NULL };
	bool flag = false;
	if (!(top = (struct stack_words*)calloc(1, sizeof(struct stack_words))) ||
		!(top->word = (char*)calloc((STRING_LENGTH + 1), sizeof(char))))
	{
		printf("Memory is not allocated\n");
		func_delete(st);
		exit(-1);
	}
	if (q_first == NULL)
	{
		queue_push(st, st->word);
		top->next = st;
		return top;
	}
	else
	{
		q_current = q_first;
		do
		{
			if (strcmp(q_current->word, st->word) == 0)
			{
				q_current->repeating_number++;
				flag = true;
				break;
			}
			q_current = q_current->next;
		} while (q_current != NULL);
		if (flag == false)
		{
			queue_push(st, st->word);
		}
	}
	top->next = st;
	return top;
}
void queue_push(struct stack_words *st, char *string)
{
	struct queue_words *q;
	int i = 0;
	if (!(q = (struct queue_words*)calloc(1, sizeof(struct queue_words))) ||
		!(q->word = (char*)calloc(WORD_LENGTH, sizeof(char))))
	{
		printf("Memory is not allocated\n");
		func_delete(st);
		exit(-1);
	}
	do
	{
		q->word[i] = string[i++];
	} while (string[i] != '\0');
	q->repeating_number = 1;
	if (q_first == NULL) q_first = q_last = q;
	else
	{
		q_last->next = q;
		q_last = q;
	}
}
