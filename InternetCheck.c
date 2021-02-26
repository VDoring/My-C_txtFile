#include <stdio.h>
#include <Windows.h>
#include <WinInet.h>
#pragma comment(lib, "WinInet.lib")

int main() {
	DWORD dwFlag;

	if (InternetGetConnectedState(&dwFlag, 0)) {
		printf("인터넷 연결됨");
	}
	else {
		printf("인터넷 연결 안됨");
	}
}