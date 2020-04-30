/*
ÀÛµ¿X
#include <stdio.h>
#include <string.h>

char StringReturn(char *str)
{
	char anostr[100];
	strcpy(anostr, str);
	printf("%s", anostr);
	return anostr;
}

int main()
{
	char mainstr[100] = { "Hello!" };
	char *pastestr[100] = { 0, };

	strcpy(pastestr, StringReturn(mainstr));
	printf("%s", pastestr);

	return 0;

}*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *StrReturn(char *funcstr)
{
	char *memstr = malloc(sizeof(char) * 100);
	strcpy(memstr, funcstr);
	return memstr;
}

int main()
{
	char strvalue[100] = "Hello";
	char *str;
	str = StrReturn(strvalue);
	printf("%s", str);

	free(str);

	return 0;

}