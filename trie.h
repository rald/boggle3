#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define NUM_LETTERS 26

typedef struct Trie Trie;
struct Trie {
	bool mark;
	Trie *next[NUM_LETTERS];
};

Trie *Trie_New();
void Trie_AddWord(Trie *root,char *word);
void Trie_Walk(Trie *root, int depth);

#endif // TRIE_H
