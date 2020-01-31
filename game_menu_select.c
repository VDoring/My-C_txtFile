// https://blog.geundung.dev/15

#include <stdio.h>
#include <Windows.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define SUBMIT 5


int keyControl();
int menuDraw();

gotoxy(int x, int y) { // 글자 위치 조정 함수
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main() {
	menuDraw();

	//int keyCode = keyControl();
	//printf("입력한 키 값은 %d\n", keyCode);

	return 0;
}

int keyControl() {
	char temp = getch();

	if (temp == 'w' || temp == 'W') return UP; //W키
	else if (temp == 'a' || temp == 'A') return LEFT; //A키
	else if (temp == 's' || temp == 'S') return DOWN; //S키
	else if (temp == 'd' || temp == 'D') return RIGHT; //D키
	else if (temp == ' ') return SUBMIT; //스페이스바(엔터같은 역할)
}

int menuDraw() {
	int x = 24;
	int y = 12;

	gotoxy(x - 2, y); printf("> 게임시작");
	gotoxy(x, y + 1); printf("게임정보");
	gotoxy(x, y + 2); printf("_종료_");
	while (1) {
		int n = keyControl();
		switch (n) {
		case UP:
			if (y > 12) { //위로 올라갈 수 있는 최대치
				gotoxy(x - 2, y); printf(" ");
				gotoxy(x - 2, --y); printf(">");
			}
			break;

		case DOWN:
			if (y < 14) { //아래로 내려갈 수 있는 최대치
				gotoxy(x - 2, y); printf(" "); //라인 45 > 출력을 지움
				gotoxy(x - 2, ++y); printf(">");
			}
			break;

		case SUBMIT:
			return y - 12;
		}
	}
}