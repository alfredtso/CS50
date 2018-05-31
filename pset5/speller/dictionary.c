// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
// Global variables
unsigned int wordcount = 0;
// define tries typestruct
typedef struct node{
	bool is_word;
	struct node *children[27];
}node;

// Define root tries, not sure
struct node *firstnode;
// initialize node to NULLS
struct node *newnode(void){
	struct node *pNode = NULL;

	pNode = (struct node *)malloc(sizeof(struct node));

	if (pNode){
		pNode->is_word = false;
		for (int i = 0; i<27; i++){
			pNode->children[i] = NULL;
		}
	}
	return pNode;
}

//function to insert key
void insert(struct node *root, const char *key){
	// for tracking the latest level
	struct node *current = root;
	int index;
	// for loop over key and add new node if not present already
	for (int i = 0; i < strlen(key); i++){
		if (key[i] == '\''){
			index = CHAR_TO_INDEX('z') + 1;
		}
		else{
			index = CHAR_TO_INDEX(key[i]);
		}
		if(!current->children[index])
			current->children[index] = newnode();

		current = current->children[index];
	}
	// mark the last node 
	current->is_word = true;
}
// function to free node
void freenode(struct node *root){
	// Traverse children node
	for (int i = 0; i < 27; i++){
		if (root->children[i]){
			// calling recursively
			freenode(root->children[i]);
		}
	}
	// free the root
	free(root);
}
//function to search key

// bool search(struct node *root, const char *key){
// 	// for tracking
// 	struct node *current = root;
// 	for ( int i = 0; i < strlen(key); i++){
// 		int index = CHAR_TO_INDEX(key[i]);
// 		if(current->children[index])
// 			current = current->children[index];
// 		else
// 			return false;
// 	}
// 	// check if is_word is true
// 	return (current->is_word);
// }
// 
// load words from dictionary
// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
	// create char array to temp store
	char ch; 
	// for tracking current node
	struct node *current = firstnode;
	//For loop convert word to lowercase to store in temp
	int i = 0;
	int index;
	while (word[i] != '\0'){
		ch  = word[i];
		//handle apostrophe
		if (ch == '\''){
			index = CHAR_TO_INDEX('z')+1;
		} 
		else{
			// to lower
			ch = tolower(ch);
			// convert word[i] to index
			index = CHAR_TO_INDEX(ch);
		}
		// check if the children node alerady exit
		if (current->children[index]){
			current = current->children[index];
			i++;
		}
		else{
			return false;
		}
	}
	// check if isword is true
	if (current->is_word == true){
		return true;
	}
	else{
		return false;
	}
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
	// open dictionary
	FILE *inptr = fopen(dictionary, "r");
	if (inptr == NULL){
		fprintf(stderr, "Could not open %s.\n", dictionary);
		return 2;
	}

	//read words from dictionary into buffer
	char buffer[LENGTH+1];

	//initialize root node
	firstnode = newnode();

	// return 1 meaning successful read
	while (fscanf(inptr, "%s", buffer) == 1){
	//read from buffer and build tries
		insert(firstnode, buffer);
		printf("inserting %s\n", buffer);
		wordcount++;
	}
	
	if (feof(inptr)){

		// close dictionary file
		printf("Word count: %d.\n", wordcount);
		printf("Closing dictionary file\n");
		fclose(inptr);
		return true;
	}
	else{
		printf("Couldn't reach the end of file.Closing dictionary file\n");
		fclose(inptr);
		return false;
	}
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
	
    return wordcount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
	struct node *current = firstnode;
	freenode(current);
	
    return true;
}
