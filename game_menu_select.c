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

gotoxy(int x, int y) { // ���� ��ġ ���� �Լ�
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main() {
	menuDraw();

	//int keyCode = keyControl();
	//printf("�Է��� Ű ���� %d\n", keyCode);

	return 0;
}

int keyControl() {
	char temp = getch();

	if (temp == 'w' || temp == 'W') return UP; //WŰ
	else if (temp == 'a' || temp == 'A') return LEFT; //AŰ
	else if (temp == 's' || temp == 'S') return DOWN; //SŰ
	else if (temp == 'd' || temp == 'D') return RIGHT; //DŰ
	else if (temp == ' ') return SUBMIT; //�����̽���(���Ͱ��� ����)
}

int menuDraw() {
	int x = 24;
	int y = 12;

	gotoxy(x - 2, y); printf("> ���ӽ���");
	gotoxy(x, y + 1); printf("��������");
	gotoxy(x, y + 2); printf("_����_");
	while (1) {
		int n = keyControl();
		switch (n) {
		case UP:
			if (y > 12) { //���� �ö� �� �ִ� �ִ�ġ
				gotoxy(x - 2, y); printf(" ");
				gotoxy(x - 2, --y); printf(">");
			}
			break;

		case DOWN:
			if (y < 14) { //�Ʒ��� ������ �� �ִ� �ִ�ġ
				gotoxy(x - 2, y); printf(" "); //���� 45 > ����� ����
				gotoxy(x - 2, ++y); printf(">");
			}
			break;

		case SUBMIT:
			return y - 12;
		}
	}
}