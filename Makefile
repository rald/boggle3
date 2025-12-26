boggle: boggle.c trie.c trie.h
	gcc boggle.c trie.c -o boggle -g

clean:
	rm boggle
