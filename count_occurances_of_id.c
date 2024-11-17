#include <stdlib.h>
#include <stdio.h>
#include "trie.h"

void count_occurances(char** strings, int count) {
	TrieNode* root = as_trie(strings, 5);
	for (int i = 0; i < count; i++) {
		printf("%s: %d\n", strings[i], count_occurance_in_trie(root,strings[i]));
	}
	
}

int main() {
	printf("Counting occurances of ids\n");

