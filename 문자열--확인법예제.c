#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main()
{
	char special[100] = { 0, }; //--���θ� Ȯ���ϱ� ���� ���ڿ�
	char s1[1000] = "https://www.youtube.com/watch?v=NGM5G1mz8Vk  Zyg - Thoughts the Past --"; //--�� �ִ� ��ũ

	char *ptr = strtok(s1, " ");  // ���� " " ���� ���ڸ� �������� ���ڿ��� �ڸ�, ������ ��ȯ
	while (1)
	{
		if (ptr == NULL) break; //���� NULL�̶�� ����

		printf("%s\n", ptr); //<�׽�Ʈ�ڵ�> ����Ȯ��
		strcpy(special, ptr); //--���� Ȯ������ special�� ���ڿ��� �����Ѵ�

		ptr = strtok(NULL, " "); // ���� ���ڿ��� �߶� �����͸� ��ȯ
	}

	printf("%s", special); //<�׽�Ʈ�ڵ�> --���� Ȯ�ο�

	if (strcmp(special, "--") == 0) printf("\n\nOKOKOK");
	else printf("\n\nNO");

	return 0;
}