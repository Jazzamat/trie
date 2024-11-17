#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The number of children for each node
// We will construct a N-ary tree and make it
// a Trie
// Since we have 26 english letters, we need
// 26 children per node (for general purpose alphabet)

//if we have id like S01, S02 then we can have 2 (S,0) + 10 (0,1,2..9) characters
#define N 12

typedef struct TrieNode TrieNode;

struct TrieNode {
	char data; 
	int occurance;
	TrieNode* children[N];
	int is_leaf;
};

static int char_to_index[256] = {0};

void init_char_to_index() {
    char_to_index['S'] = 0;
    for (int i = '0'; i <= '9'; i++) {
        char_to_index[i] = i - '0' + 1; 
    }
}

#define getPosition(c) (char_to_index[(unsigned char)c])

TrieNode* make_trienode(char data) {
	// Allocate memory for a TrieNode
	TrieNode* node = (TrieNode*) calloc (1, sizeof(TrieNode));
	node->is_leaf = 0;
	node->data = data;
	node->occurance = 0;
	return node;
}

void free_trienode(TrieNode* node) {
	for(int i=0; i<N; i++) {
		if (node->children[i] != NULL) {
			free_trienode(node->children[i]);
		}
		else {
			continue;
		}
	}
	free(node);
}

TrieNode* insert_trie(TrieNode* root, char* word) {
	TrieNode* temp = root;

	for (int i=0; word[i] != '\0'; i++) {
		int idx = getPosition(word[i]);
		if (temp->children[idx] == NULL) {
			temp->children[idx] = make_trienode(word[i]);
		}
		temp = temp->children[idx];
	}
	temp->is_leaf = 1;
	temp->occurance++;
	return root;
}

int search_trie(TrieNode* root, char* word)
{
	TrieNode* temp = root;
	for(int i=0; word[i]!='\0'; i++)
	{
		int position = getPosition(word[i]);
		if (temp->children[position] == NULL)
			return 0;
		temp = temp->children[position];
	}
	if (temp != NULL && temp->is_leaf == 1)
		return 1;
	return 0;
}

void print_trie(TrieNode* root) {
	// Prints the nodes of the trie
	if (!root)
		return;
	TrieNode* temp = root;
	printf("(%c,%d) -> ", temp->data, temp->occurance);
	for (int i=0; i<N; i++) {
		print_trie(temp->children[i]); 
	}
}

void print_search(TrieNode* root, char* word) {
	printf("Searching for %s: ", word);
	if (search_trie(root, word) == 0)
		printf("Not Found\n");
	else
		printf("Found!\n");
}

int count_occurance_of_word(TrieNode* root, char* word) {
	TrieNode* temp = root;

	for(int i=0; word[i]!='\0'; i++)
	{
		int position = getPosition(word[i]);
		if (temp->children[position] == NULL)
			return 0;
		temp = temp->children[position];
	}
	if (temp != NULL && temp->is_leaf == 1)
		return temp->occurance + 1;
	return 0;
}


TrieNode* as_trie(char** strings, int count) {
	TrieNode* root = make_trienode('\0');
	for (int i = 0; i<count; i++) {
		root = insert_trie(root,strings[i]);
	}
	return root;
}

void count_occurances(char** strings, int count) {
	init_char_to_index();
	TrieNode* root = as_trie(strings, 5);
	for (int i = 0; i < count; i++) {
		//printf("%s: %d\n", strings[i], count_occurance_of_word(root,strings[i]));
		count_occurance_of_word(root, strings[i]);
	}
	free_trienode(root);
}


int main() {
	TrieNode* root = make_trienode('\0');
	root = insert_trie(root, "S01");
	root = insert_trie(root, "S99");
	root = insert_trie(root, "S89");
	root = insert_trie(root, "S02");

	printf("The occurance of the word \"S01\" is: %d\n", count_occurance_of_word(root, "S01"));


	return 0;
}
