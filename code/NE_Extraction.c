#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

	FILE* fpin;
	char str1[1000];
	char str2[1000];

	if (!(fpin = fopen("11111.txt", "r"))) {
		printf("파일 개방 실패 !!! \n");
		exit(100);
	}

	while (1) {
		if (fpin == NULL) break;
		strcpy(str2, fgets(str1, sizeof(str1), fpin));
		if (strcmp(str2, "            \"NE\": [\n") == 0) {
			while (1) {
				strcpy(str2, fgets(str1, sizeof(str1), fpin));
				printf("%s", str2);
				if ((strcmp(str2, "            ], \n") == 0)) break;
			}
		}
	}

	return 0;
}