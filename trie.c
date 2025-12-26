#include "trie.h"

Trie *Trie_New() {
	Trie *trie=malloc(sizeof(*trie));
	trie->mark=false;
	for(int i=0;i<NUM_LETTERS;i++) {
		trie->next[i]=NULL;
	}
	return trie;
}

void Trie_AddWord(Trie *root,char *word) {
  Trie *curr_node=root;
  char *curr_let;
  int next_let;
  if (word==NULL || *word=='\0') return;
  curr_let=word;
  while(*curr_let) {
    next_let=tolower(*curr_let)-'a';
    if(curr_node->next[next_let]==NULL)
      curr_node->next[next_let]=Trie_New();
    curr_node=curr_node->next[next_let];
    curr_let++;
  }
  curr_node->mark = 1;
}

void Trie_Walk(Trie *trie,int depth) {
	static char word[256];
  depth++;
  if (trie->mark) {
    word[depth]='\0';
    puts(word);
  }
  for(int i=0;i<NUM_LETTERS;i++) {
    if(trie->next[i]) {
      word[depth]=i+'a';
      Trie_Walk(trie->next[i],depth);
    }
  }
}
