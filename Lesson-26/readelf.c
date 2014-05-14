#include <stdio.h>
#include <assert.h>

typedef char Elf32_Char;
typedef short Elf32_Half;
typedef int Elf32_Word;
typedef int Elf32_Addr;
typedef int Elf32_Off;

#define EI_NIDENT 16

typedef struct {
    Elf32_Char  e_ident[EI_NIDENT];
    Elf32_Half  e_type;
    Elf32_Half  e_machine;
    Elf32_Word  e_version;
    Elf32_Addr  e_entry;  /** Entry point */
    Elf32_Off   e_phoff;
    Elf32_Off   e_shoff;
    Elf32_Word  e_flags;
    Elf32_Half  e_ehsize;
    Elf32_Half  e_phentsize;
    Elf32_Half  e_phnum;
    Elf32_Half  e_shentsize;
    Elf32_Half  e_shnum;
    Elf32_Half  e_shstrndx;
} Elf32_Ehdr;

// ELF Header size
#define HSIZE	(int)sizeof(Elf32_Ehdr)

struct type_string
{
	int type;
	char *string;
} s[] =
{
	{ 0, "Unknow" },
	{ 2, "EXEC" },
	{ 1, "REL" },
	{ -1, "Other Format" },
};

int get_type_index(int type)
{
	int index = 0;
	int all = sizeof(s)/sizeof(s[0]);

	for (index = 0; index < all - 1; index++)
	{
		if (s[index].type == type)
			return index;
	}

	return all - 1;
}

int readelf_main(int argc, char *argv[])
{
	FILE *fp;

	if (argc < 2)
	{
		printf("Usage: readelf elf_file \n");
		return -1;
	}

	fp = fopen(argv[1], "rb");
	if (fp == NULL)
	{
		printf("file <%s> open error\n", argv[1]);
		return -1;
	}
	// verify that fp1 not NULL
	assert(fp);
	
	char buf[HSIZE];
	int n;

	n = fread(buf, HSIZE, 1, fp);
	printf("n = %d\n", n);
	printf("HSIZE = %d\n", HSIZE);
	if (n != 1)
	{
		printf("file <%s> read error\n", argv[1]);
		return -1;
	}
	fclose(fp);

	Elf32_Ehdr * p;
	p = (Elf32_Ehdr *)buf;

	printf("type = %d\n", p->e_type);
	printf("Type: %s\n", s[get_type_index(p->e_type)].string);

	return 0;
}
