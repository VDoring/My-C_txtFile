#include <stdio.h>
#include <Windows.h>
#include <WinInet.h>
#pragma comment(lib, "WinInet.lib")

int main() {
	DWORD dwFlag;

	if (InternetGetConnectedState(&dwFlag, 0)) {
		printf("���ͳ� �����");
	}
	else {
		printf("���ͳ� ���� �ȵ�");
	}
}