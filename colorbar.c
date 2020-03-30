#include <stdio.h>
#include <Windows.h>

textcolor(int num) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
}

int main() {
	for (int i = 0; i <= 255; i++)
		textcolor(i), printf("%4d", i);

	textcolor(7), puts("\nEND");

	return 0;
}