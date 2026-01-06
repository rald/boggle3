#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "trie.h"

#define MIN_WORD_LEN 3

char **dice=NULL;
int ndice=0;

char board[4][4];

bool graph[4][4];

Trie *root=NULL;

char **found;
int nfound=0;

int score=0;


void Word_Add(char ***words,int *nwords, char *word) {
	(*words)=realloc(*words,sizeof(**words)*((*nwords)+1));
	(*words)[(*nwords)++]=strdup(word);
}


bool Word_Find(char **words,int nwords,char *word) {
	for(int i=0;i<nwords;i++) {
		if(!strcmp(word,words[i])) {
			return true;
		}
	}
	return false;
}


void Dice_Load(char ***dice,int *ndice) {
	FILE *fp=fopen("dice.txt","r");
	char line[256];
	while(fgets(line,256,fp)) {
		line[strlen(line)-1]='\0';
		Word_Add(dice,ndice,line);
	}
	fclose(fp);
}


void Dice_Shuffle(char **dice,int ndice) {
	for(int i=ndice-1;i>0;i--) {
		int j=rand()%(i+1);
		char *k=dice[i];
		dice[i]=dice[j];
		dice[j]=k;
	}
}


void dfs(Trie *trie,int x,int y,int depth) {

	static char word[4*4+2];

	if(x<0 || x>=4 || y<0 || y>=4) return;
	if(graph[y][x]) return;

	int idx = board[y][x]-'a';

	if((trie=trie->next[idx])==NULL) return;

	depth++;

	word[depth]=board[y][x];
	word[depth+1]='\0';

	if(trie->mark && !Word_Find(found,nfound,word) && strlen(word)>=MIN_WORD_LEN) {
		Word_Add(&found,&nfound,word);
	}

	graph[y][x]=true;
	for(int j=-1;j<=1;j++) {
		for(int i=-1;i<=1;i++) {
			if(i || j) {
				dfs(trie,x+i,y+j,depth);
			}
		}
	}
	graph[y][x]=false;

	if(board[y][x]=='q') {
		idx='u'-'a';
		if((trie=trie->next[idx])) {
				depth++;

				word[depth]='u';
				word[depth+1]='\0';

				if(trie->mark && !Word_Find(found,nfound,word) && strlen(word)>=MIN_WORD_LEN) {
					Word_Add(&found,&nfound,word);
				}

				graph[y][x]=true;
				for(int j=-1;j<=1;j++) {
					for(int i=-1;i<=1;i++) {
						if(i || j) {
							dfs(trie,x+i,y+j,depth);
						}
					}
				}
				graph[y][x]=false;
		}
	}
}


int cmplen(const void *lhs,const void *rhs) {
	char *l=*(char**)lhs;
	char *r=*(char**)rhs;
	return strlen(r)-strlen(l);
}


int cmprnd(const void *lhs,const void *rhs) {
	char *l=*(char**)lhs;
	char *r=*(char**)rhs;
	return rand()%3-1;
}

int cmplenasc(const void *lhs,const void *rhs) {
	char *l=*(char**)lhs;
	char *r=*(char**)rhs;

	if(strlen(l)-strlen(r)==0) return strcmp(l,r);

	return strlen(l)-strlen(r);
}

int points(char *word) {
	int len=strlen(word);

	if(len>=8) return 11;
	else if(len==7) return 5;
	else if(len==6) return 3;
	else if(len==5) return 2;
	else if(len==4) return 1;
	else if(len==3) return 1;

	return 0;
}

int main() {

	srand((unsigned int)time(NULL));

	Dice_Load(&dice,&ndice);

	Dice_Shuffle(dice,ndice);

//	for(int i=0;i<ndice;i++) puts(dice[i]);

	int k=0;
	for(int j=0;j<4;j++) {
		for(int i=0;i<4;i++) {
			board[j][i]=dice[k][rand()%strlen(dice[k])];
			k++;
		}
	}

	for(int j=0;j<4;j++) {
		for(int i=0;i<4;i++) {
			putchar(board[j][i]);
		}
		putchar('\n');
	}
	putchar('\n');

	for(int j=0;j<4;j++) {
		for(int i=0;i<4;i++) {
			graph[j][i]=false;
		}
	}

	root=Trie_New();
	FILE *fp=fopen("wordlist.txt","r");
	char line[256];
	while(fgets(line,256,fp)) {
		line[strlen(line)-1]='\0';
		Trie_AddWord(root,line);
	}
	//Trie_Walk(root,-1);


	for(int j=0;j<4;j++) {
		for(int i=0;i<4;i++) {
			dfs(root,i,j,-1);
		}
	}

	qsort(found,nfound,sizeof(*found),cmplenasc);
//	qsort(found,nfound,sizeof(*found),cmplen);
//	qsort(found,nfound,sizeof(*found),cmprnd);

	for(int i=0;i<nfound;i++) {
		if(i!=0) printf(", ");
		printf("%s",found[i]);
		score+=points(found[i]);
	}
	printf("\n\n");

	printf("total score: %d\n",score);

	for(int i=0;i<ndice;i++) {
		free(dice[i]);
		dice[i]=NULL;
	}

	for(int i=0;i<nfound;i++) {
		free(found[i]);
		found[i]=NULL;
	}

	return 0;
}
