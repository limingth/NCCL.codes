#include <stdio.h>
#include <assert.h>

int mycp_main(int argc, char *argv[])
{
	FILE *fp1, *fp2;

	if (argc < 3)
	{
		printf("Usage: mycp source_file dest_file\n");
		return -1;
	}

	fp1 = fopen(argv[1], "rb");
	if (fp1 == NULL)
	{
		printf("file <%s> open error\n", argv[1]);
		return -1;
	}

	fp2 = fopen(argv[2], "wb");
	if (fp2 == NULL)
	{
		printf("file <%s> open error\n", argv[1]);
		return -1;
	}

	// verify that fp1 and fp2 are not NULL
	assert(fp1 && fp2);
	
	while (!feof(fp1))
	{
		int size = 512;
		char buf[size];
		int n;

		n = fread(buf, 1, size, fp1);
		fwrite(buf, 1, n, fp2);
	}
	
	fclose(fp1);
	fclose(fp2);

	return 0;
}
