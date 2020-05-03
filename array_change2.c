#include <stdio.h>  
#include <string.h>  

char * change_word(char *string, char *old_word, char *new_word);

int main()
{
	char string[100];
	char old_word[30];
	char new_word[30];

	printf("Input string: ");
	fgets(string, sizeof(string), stdin); //원본문자열 입력

	printf("Input old word: ");
	scanf("%s", old_word); //바꾸고싶은 문자열 입력

	printf("Input new word: ");
	scanf("%s", new_word); //바꿀문자열 입력

	strcpy(string, change_word(string, old_word, new_word));
	printf("change string: %s\n", string);

	return 0;
}

char * change_word(char *string, char *old_word, char *new_word)
{
	char *token;
	char temp[100]; //바꾼 문자열 저장

	memset(temp, 0, sizeof(temp)); //메모리할당 & 초기화
	token = strtok(string, " "); //띄어쓰기를 기준으로 문자열을 자름. token에 저장

	while (token != NULL) //잘랐던 문자열 값이 없을경우 {
	{
		if (0 == strcmp(token, old_word)) //token이랑 old_word가 같을경우(바꿀 문자열인지 확인)
		{
			strcat(temp, new_word); //temp에 new_word값을 덧붙이기
		}
		else //token이랑 old_word가 다를경우(바꿀 문자열인지 확인)
		{
			strcat(temp, token); //temp에 token(원본)값을 덧붙이기
		}
		strcat(temp, " "); //temp에 띄어쓰기 추가
		token = strtok(NULL, " "); //다음 원본문자열로 이동(token은 포인터이다)
	}
	temp[strlen(temp) - 1] = 0; //temp배열 끝부분의 값을 제거

	return temp;
}