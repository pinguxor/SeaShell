#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_SIZE 1024
#define TOK_BUFFER_SIZE 32
#define TOK_DELIM " \t\r\n\a"

char **sea_parseline(char *line)
{
	size_t buff_size = TOK_BUFFER_SIZE;
	int pos = 0;
	char *token;
	char **tokens = malloc(sizeof(char *) * buff_size);
	
	if (!tokens) {
		fprintf(stderr, "seashell: memory allocation failed\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line,TOK_DELIM);
	while (token != NULL) {
		tokens[pos] = token;
		pos++;
  		
		if (pos >= buff_size) {
			buff_size += TOK_BUFFER_SIZE;
			tokens = realloc(tokens,sizeof(char *) * buff_size);
			if (!tokens) {
				fprintf(stderr, "seashell: memory allocation failed\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL,TOK_DELIM);
	}

	tokens[pos] = NULL;
	return tokens;
}

char *sea_readline(void)
{
	size_t buff_size = LINE_BUFFER_SIZE;
	char *buffer = (char *)malloc(sizeof(char) * buff_size);
	int pos = 0;
	int c;

	if (!buffer) {
		fprintf(stderr, "seashell: memory allocation failed\n");
		exit(EXIT_FAILURE);
	}

	while(1) {
		c = getchar();

		if (c == EOF || c == '\n') {
			buffer[pos] = '\0';
			return buffer;
		} else {
			buffer [pos] = c;
		}
		pos++;

		if (pos >= buff_size) {
			buff_size += LINE_BUFFER_SIZE;
			buffer = (char *)realloc(buffer,sizeof(char)*buff_size);
			if (!buffer) {
				fprintf(stderr, "seashell: memory allocation failed\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

void sea_loop(void)
{
	char *line;
	char **args;
	int status = 1;

	do{
		printf("> ");
		line = sea_readline();
		args = sea_parseline(line);
		//status = sea_execute(args);
		printf("%s",args[0]);
	} while(status);
}

int main(int argc, char **argv)
{
	sea_loop();
	return 0;
}
