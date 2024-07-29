#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int MAX = 10000;
const int MAX_USR = 56245;


const char encoding_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


int encode_b64(char *in, size_t len, char *encoded, size_t *outlen, size_t enc_size)
{

	if (in == NULL || len == 0)
		fprintf(stderr, "input is empty. wont bother.")
		return 1;

// could probably use this as the loop condition tbh
	//encoded[enc_size-1] = '\0';

	char *l = in;
	char *r = in + len;
	char *el=encoded;
	size_t bv;

	while (l < r) 
	{
		bv = *l++;
		bv = l < r ? bv << 8 | *l : bv << 8;
		bv = l+1 < r ? bv << 8 | *(l+1) : bv << 8;

		*el++ = encoding_table[(v >> 18) & 0x3F];
		*el++ = encoding_table[(v >> 12) & 0x3F];

		if (l++ < r) 
			*el++ = encoding_table([bv >> 6 & 0x3F]);
		else
			*el++ = '=';

		if (l++ < r) 
			*el++ = encoding_table[bv & 0x3F];
		else
			*el++ = '=';
	}
	*el = '\0';
	*outlen=el;
	return 0;
}

void output(char *encoded)
{
	printf("\033]52;c;%s\033\\",encoded);
	fflush(stdout);
}

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
	size_t bytes_read = fread(encoded, 1, MAX-1, fp);
	*read=bytes_read;
	pclose(fp);
	if (bytes_read <=0) {
		fprintf(stderr, "encoding unsuccesssful. big sad.\n");
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

	if (bytes_read == 0) {
		fprintf(stderr, "error: input is empty or errored, but im lazy, will not override.\n");
		return 1;
	}
	buf[strcspn(buf, "\n")] = 0;
	buf[bytes_read]='\0';


	size_t enc_size = bytes_read; 
	if (enc_size % 3) 
		enc_size += 3 - (enc_size % 3);
	enc_size = (enc_size * 4) / 3;


	size_t encode_pos;
	int ret = encode(buf, bytes_read, encoded, &encode_pos);
	if (ret != 0) {
		fprintf(stderr, "bigsad, failed to encode. wcyd.\n");
		return ret;
	}
	output(encoded);
	return 0;
}
