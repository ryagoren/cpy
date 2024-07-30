#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int MAX = 10000;
const int MAX_USR = 56245;
const char encoding_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int encode(char *in, size_t len, char *encoded, size_t *outlen)
{
	if (in == NULL || len == 1) 
	{
		fprintf(stderr, "input is empty. wont bother.");
		return 1;
	}

	char *l = in;
	char *r = in + len;
	char *el=encoded;
	size_t bv;

	while (l < r) 
	{
		bv = *l++;
		bv = l < r ? bv << 8 | *l : bv << 8;
		bv = l+1 < r ? bv << 8 | *(l+1) : bv << 8;

		*el++ = encoding_table[(bv >> 18) & 0x3F];
		*el++ = encoding_table[(bv >> 12) & 0x3F];

		if (l++ < r) 
			*el++ = encoding_table[(bv >> 6) & 0x3F];
		else
			*el++ = '=';

		if (l++ < r) 
			*el++ = encoding_table[bv & 0x3F];
		else
			*el++ = '=';
	}

	*outlen=(el-encoded);
	return 0;
}

int main()
{
	char buf[MAX_USR];

	size_t buf_remaining=MAX_USR;
	size_t bytes_read;

	bytes_read = fread(buf, 1, MAX_USR, stdin);

	if (bytes_read == 0) {
		fprintf(stderr, "error: input is empty or errored, but im lazy, will not override.\n");
		return 1;
	}

	char *back = buf + bytes_read - 1;

		while (back >= buf && (*back == '\n' || *back == '\r')) 
			back--;

		*(back+1) = '\0';

        size_t backpos=back-buf + 1;

	size_t enc_size = backpos; 
	if (enc_size % 3) 
		enc_size += 3 - (enc_size % 3);
	enc_size = (enc_size * 4) / 3;

	char encoded[enc_size+1];

	const char *prefix =  "\x1B]52;c;";
	memcpy(encoded, prefix, strlen(prefix));

	size_t encode_pos=0;
	int ret = encode(buf, backpos, encoded+7, &encode_pos);
	if (ret != 0) {
		fprintf(stderr, "bigsad, failed to encode. wcyd.\n");
		return ret;
	}
	encode_pos += 7;
	encoded[encode_pos++] = '\x07';
	 size_t written = fwrite(encoded, 1, encode_pos, stdout);
	 fflush(stdout);
	return 0;
}
