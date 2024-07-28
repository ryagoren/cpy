
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void output(char *encoded)
{
	printf("\033]52;c;%s\033\\",encoded);
	fflush(stdout);
}

int main(int argc, char **argv) {

	fprintf(stderr, "wassup\n");


	if (argc != 2) {
		fprintf(stderr, "Usage: %s \"text to copy\"\n", argv[0]);
		return 1;
	}

	char *command;
	asprintf(&command, "echo -n \"%s\" | base64", argv[1]);

	FILE *fp = popen(command, "r");
	if (fp == NULL) {
		fprintf(stderr, "failed to encode provided text in base64\n");
		return 1;
	}

	char encoded[BUFSIZ];
	fgets(encoded, sizeof(encoded), fp);
	pclose(fp);
	encoded[strcspn(encoded, "\n")] = 0;
	output(encoded);
}
