// https://m.blog.naver.com/PostView.nhn?blogId=ndb796&logNo=221300485185&proxyReferer=https%3A%2F%2Fwww.google.com%2F

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define STRING_SIZE 256
#define MAP_SIZE 1024

//하나의 매핑 문자열 정보를 담는다
typedef struct Word {
	char source[STRING_SIZE];
	char target[STRING_SIZE];
} Word;

Word words[MAP_SIZE];
int wordCount;

void insert(char *source, char *target) {
	Word word;
	strcpy(word.source, source);
	strcpy(word.target, target);
	words[wordCount++] = word;
}

char* find(char *source) {
	int i;
	char *result = source;
	for (i = 0; i < wordCount; i++) {
		if (strcmp(words[i].source, source) == 0) {
			return words[i].target; 
		}
	}
	return result;
}

int main() {
	/* 먼저 입력 파일을 받는다. */
	FILE *inputFile = NULL;
	char inputFileName[STRING_SIZE];
	printf("입력 파일: ");
	scanf("%s", &inputFileName); //입력파일(원본파일)의 이름을 inputFileName에 받는다
	inputFile = fopen(inputFileName, "r"); //inputFileName에 저장된 파일이름을 fopen하고 inputfile에 저장한다. (fopen 리턴값은 FILE객체에 대한 포인터이다)
	if (inputFile == NULL) {
		printf("입력 파일이 존재하지 않습니다.1\n");
		return 0;
	}

	/* 이어서 맵 파일을 받는다. */
	FILE *mapFile = NULL;
	char mapFileName[STRING_SIZE];
	printf("맵 파일: ");
	scanf("%s", &mapFileName); //맵파일(바꿔넣을파일)의 이름을 mapFileName에 받는다
	mapFile = fopen(mapFileName, "r"); //mapFileName에 저장된 파일이름을 fopen하고 mapFile에 저장한다.
	if (mapFileName == NULL) { //mapFIle로도 해보기
		printf("입력 파일이 존재하지 않습니다.2\n");
	}

	FILE *outputFile = NULL;
	char *outputFileName = strtok(inputFileName, "."); //inputFileName에 들은 파일이름(infile.txt)에서 .txt부분을 따로 분리하고 *outputFileName에 저장한다
	strcat(outputFileName, ".out.txt"); //infile 파일이름에 .out.txt를 추가한다
	outputFile = fopen(outputFileName, "w"); //infile.out.txt파일을 쓰기모드로 fopen하고 outputFile에 저장한다

	//맵파일을 처리한다.
	char buffer[STRING_SIZE];
	while (!feof(mapFile)) { //mapfile 파일내용이 끝날 때까지 while을 돌림
		//버퍼에 한 라인을 입력 받는다
		fgets(buffer, sizeof(buffer), mapFile);
		//:의 앞부분의 단어를 담는다
		char *source = strtok(buffer, ":");
		//:의 뒷부분의 단어를 담는다
		char *target = strtok(NULL, " \n");
		insert(source, target);
	}
	fclose(mapFile);

	//입력 파일을 처리한다
	while (!feof(inputFile)) { //inputfile 파일내용이 끝날 때까지 while을 돌림
		//버퍼에 한 라인을 입력 받는다
		fgets(buffer, sizeof(buffer), inputFile);
		//공백을 기준으로 문장을 나눈다
		char *ptr = strtok(buffer, " ");
		//단어 하나하나 접근한다
		while (ptr != NULL) {
			char *result = find(ptr);
			printf("%s ", result);
			fprintf(outputFile, "%s ", result);
			ptr = strtok(NULL, " \n");
		}
		printf("\n");
		fprintf(outputFile, "\n");
	}
	fclose(inputFile);
	fclose(outputFile);

	return 0;
}