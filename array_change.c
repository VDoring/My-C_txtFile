// https://m.blog.naver.com/PostView.nhn?blogId=ndb796&logNo=221300485185&proxyReferer=https%3A%2F%2Fwww.google.com%2F

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define STRING_SIZE 256
#define MAP_SIZE 1024

//�ϳ��� ���� ���ڿ� ������ ��´�
typedef struct Word {
	char source[STRING_SIZE];
	char target[STRING_SIZE];
} Word;

Word words[MAP_SIZE];
int wordCount;

void insert(char *source, char *target) {
	Word word;
	strcpy(word.source, source); //:�� �պκ��� �ܾ word.source�� ���
	strcpy(word.target, target); //:�� �޺κ��� �ܾ word.target�� ����
	words[wordCount++] = word; //words ����ü�� word.source�� word.target�� ���� �����Ѵ�.
								//(�迭ó�� �۵��Ǵ� ����̴�.)
}

char* find(char *source) {
	int i;
	char *result = source;
	for (i = 0; i < wordCount; i++) {
		if (strcmp(words[i].source, source) == 0) { //words[i].source�� source�� ������ ���ٸ�
			return words[i].target; //words[i].target ��ȯ
		}
	}
	return result;
}

int main() {
	/* ���� �Է� ������ �޴´�. */
	FILE *inputFile = NULL;
	char inputFileName[STRING_SIZE];
	printf("�Է� ����: ");
	scanf("%s", &inputFileName); //�Է�����(��������)�� �̸��� inputFileName�� �޴´�
	inputFile = fopen(inputFileName, "r"); //inputFileName�� ����� �����̸��� fopen�ϰ� inputfile�� �����Ѵ�. (fopen ���ϰ��� FILE��ü�� ���� �������̴�)
	if (inputFile == NULL) {
		printf("�Է� ������ �������� �ʽ��ϴ�.1\n");
		return 0;
	}

	/* �̾ �� ������ �޴´�. */
	FILE *mapFile = NULL;
	char mapFileName[STRING_SIZE];
	printf("�� ����: ");
	scanf("%s", &mapFileName); //������(�ٲ��������)�� �̸��� mapFileName�� �޴´�
	mapFile = fopen(mapFileName, "r"); //mapFileName�� ����� �����̸��� fopen�ϰ� mapFile�� �����Ѵ�.
	if (mapFileName == NULL) { //mapFIle�ε� �غ���
		printf("�Է� ������ �������� �ʽ��ϴ�.2\n");
	}

	FILE *outputFile = NULL; //��ȯ�� ���ڿ��� �����ϴ� �Ǵٸ� txt������ �����ϴ� ����������
	char *outputFileName = strtok(inputFileName, "."); //inputFileName�� ���� �����̸�(infile.txt)���� .txt�κ��� ���� �и��ϰ� *outputFileName�� �����Ѵ�
	strcat(outputFileName, ".out.txt"); //infile �����̸��� .out.txt�� �߰��Ѵ�
	outputFile = fopen(outputFileName, "w"); //infile.out.txt������ ������� fopen�ϰ� outputFile�� �����Ѵ�

	//�������� ó���Ѵ�.
	char buffer[STRING_SIZE];
	while (!feof(mapFile)) { //mapfile ���ϳ����� ���� ������ while�� ����
		//���ۿ� �� ������ �Է� �޴´�
		fgets(buffer, sizeof(buffer), mapFile);
		//:�� �պκ��� �ܾ ��´�
		char *source = strtok(buffer, ":");
		//:�� �޺κ��� �ܾ ��´�
		char *target = strtok(NULL, " \n");
		insert(source, target);
	}
	fclose(mapFile);

	//�Է� ������ ó���Ѵ�
	while (!feof(inputFile)) { //inputfile ���ϳ����� ���� ������ while�� ����
		//���ۿ� �� ������ �Է� �޴´�
		fgets(buffer, sizeof(buffer), inputFile);
		//������ �������� ������ ������
		char *ptr = strtok(buffer, " ");
		//�ܾ� �ϳ��ϳ� �����Ѵ�
		while (ptr != NULL) {
			char *result = find(ptr);
			printf("%s ", result); //�ֿܼ� ���
			fprintf(outputFile, "%s ", result); 
			ptr = strtok(NULL, " \n"); //���� ���� �ܾ� ����
		}
		printf("\n");
		fprintf(outputFile, "\n");
	}
	fclose(inputFile);
	fclose(outputFile);

	return 0;
}