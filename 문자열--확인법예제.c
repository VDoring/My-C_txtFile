#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main()
{
	char special[100] = { 0, }; //--여부를 확인하기 위한 문자열
	char s1[1000] = "https://www.youtube.com/watch?v=NGM5G1mz8Vk  Zyg - Thoughts the Past --"; //--가 있는 링크

	char *ptr = strtok(s1, " ");  // 먼저 " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
	while (1)
	{
		if (ptr == NULL) break; //만약 NULL이라면 종료

		printf("%s\n", ptr); //<테스트코드> 동작확인
		strcpy(special, ptr); //--여부 확인위해 special로 문자열을 복사한다

		ptr = strtok(NULL, " "); // 다음 문자열을 잘라서 포인터를 반환
	}

	printf("%s", special); //<테스트코드> --여부 확인용

	if (strcmp(special, "--") == 0) printf("\n\nOKOKOK");
	else printf("\n\nNO");

	return 0;
}