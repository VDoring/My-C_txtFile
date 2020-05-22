#include <stdio.h>
int main() {
	char str[50];
	int val[50];

	scanf("%s", &str);
	for(int i = 0; str[i] != '\0'; i++) {
		val[i] = str[i] - '0';
		printf("%d\n", val[i]);
	}
	return 0;
}