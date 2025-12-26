#include <stdio.h>

int main() {

	FILE *fp=fopen("enable1.txt","r");
	char line[256];

	while(fgets(line,256,fp)) {
		line[strlen(line)-1]='\0';
		if(strlen(line)>=3 && strlen(line)<=16) puts(line);
	}

	fclose(fp);

	return 0;
}