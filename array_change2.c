#include <stdio.h>  
#include <string.h>  

char * change_word(char *string, char *old_word, char *new_word);

int main()
{
	char string[100];
	char old_word[30];
	char new_word[30];

	printf("Input string: ");
	fgets(string, sizeof(string), stdin); //�������ڿ� �Է�

	printf("Input old word: ");
	scanf("%s", old_word); //�ٲٰ���� ���ڿ� �Է�

	printf("Input new word: ");
	scanf("%s", new_word); //�ٲܹ��ڿ� �Է�

	strcpy(string, change_word(string, old_word, new_word));
	printf("change string: %s\n", string);

	return 0;
}

char * change_word(char *string, char *old_word, char *new_word)
{
	char *token;
	char temp[100]; //�ٲ� ���ڿ� ����

	memset(temp, 0, sizeof(temp)); //�޸��Ҵ� & �ʱ�ȭ
	token = strtok(string, " "); //���⸦ �������� ���ڿ��� �ڸ�. token�� ����

	while (token != NULL) //�߶��� ���ڿ� ���� ������� {
	{
		if (0 == strcmp(token, old_word)) //token�̶� old_word�� �������(�ٲ� ���ڿ����� Ȯ��)
		{
			strcat(temp, new_word); //temp�� new_word���� �����̱�
		}
		else //token�̶� old_word�� �ٸ����(�ٲ� ���ڿ����� Ȯ��)
		{
			strcat(temp, token); //temp�� token(����)���� �����̱�
		}
		strcat(temp, " "); //temp�� ���� �߰�
		token = strtok(NULL, " "); //���� �������ڿ��� �̵�(token�� �������̴�)
	}
	temp[strlen(temp) - 1] = 0; //temp�迭 ���κ��� ���� ����

	return temp;
}