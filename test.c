#include <stdio.h>

#include "trie.h"

int main() {

	Trie *root=Trie_New();

	FILE *fp=fopen("enable1.txt","r");
	char line[256];

	while(fgets(line,256,fp)) {
		line[strlen(line)-1]='\0';
		Trie_AddWord(root,line);
	}

	Trie_Walk(root,-1);

	return 0;
}
