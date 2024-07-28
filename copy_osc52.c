
#include<stdio.h>

#include<stdlib.h>
#include<string.h>


void output(char *encoded)
{
	printf("\033]52;c;%s\033\\",encoded);
	fflush(stdout);
}

const int MAX = 10000;
const int MAX_USR = 56245;

// lazy way out - worst case would be 


int encode(char *buf, size_t len, char *encoded, size_t *read)
{
	char *command;
	asprintf(&command, "echo -n \"%s\" | base64", buf);
	FILE *fp = popen(command, "r");
	if (fp == NULL) {
		fprintf(stderr, "failed to encode provided text in base64\n");
		free(command);
		return 1;
	}
	read = fread(encoded, 1, MAX-1, fp);
	*read=bytes_read;
	pclose(fp);
	if (bytes_read <=0) {
		fprintf("encoding unsuccesssful. big sad.\n");
		return 1;
	}
	encoded[strcspn(encoded, "\n")] = 0;
	encoded[bytes_read] = '\0';
	return 0;
}


int main()
{
	char buf[MAX_USR];
	char encoded[MAX];

	size_t buf_remaining=MAX_USR;
	size_t bytes_read;

	bytes_read = fread(buf, 1, MAX_USR, stdin);
	if bytes_read == 0 {
		fprintf(stderr, "error: input is empty (or errored, but im lazy), will not override.\n");
		return 1;
	}
	buf[bytes_read]='\0';

	size_t encode_pos;
	int ret = encode(&buf, bytes_read, &encoded, &encode_pos);
	if (ret != 0) {
		fprintf("bigsad, failed to encode. wcyd.\n");
		return ret;
	}
	output(encoded);
	return 0;
}


int read_remainder(char *remainder)
{
	char buf[BUFSIZ];
	ret = fread(buf, sizeof(*buf), sizeof(buf)/sizeof((buff)[0]), stdin);
	if ret == 0 {
		return 0;
	}
	size_t curlen = 0;
	char *buf = malloc(bufsize);

	if (!buf) {
		fprintf(stderr, "malloc failed, there's some gooooooood sht happenin' on your box");
		return 1;
	}

	int c;

	while ((c=

}




int main(int argc, char **argv) {
	if (argc != 1) {
	fprintf(stderr, "-unimplemented!-\n");
	return 1;
	}

	char buf[MAX]



	char buf[BUFSIZ];
	if (!fgets(buf, sizeof(buf), stdin)) {
		fprintf(stderr, "failed to read from stdin\n");
		return 1;
	}

	buf[strcspn(buf, "\n")] = 0;
	char *command;
	asprintf(&command, "echo -n \"%s\" | base64", buf);
	FILE *fp = popen(command, "r");
	if (fp == NULL) {
		fprintf(stderr, "failed to encode provided text in base64\n");
		free(command);
		return 1;
	}

	char encoded[BUFSIZ];
	fgets(encoded, sizeof(encoded), fp);
	pclose(fp);

	encoded[strcspn(encoded, "\n")] = 0;
	output(encoded);

	free(command);
	return 0;
}
