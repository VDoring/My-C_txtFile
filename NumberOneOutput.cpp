#include <iostream>
using namespace std;
int main() {
	int a = 1234;

	while (a != 0) { //a가 0이 아니라면 실행
		cout << a % 10 << "\n"; //10으로 나누어가며 10으로 나눈 나머지를 찾으면 뒷자리부터 한자리씩 분리할 수 있다.
		a /= 10; //a = 1234 일떄 a=123.4가 된다. int는 소숫점 무시하므로 앞자리를 제거한 효과가 된다.
	}
}