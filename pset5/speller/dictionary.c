// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
// Global variables
unsigned int wordcount;
// define tries typestruct
typedef struct node{
	bool is_word;
	struct node *children[27];
}node;

// Define root tries, not sure
struct node *tries;
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
	// for loop over key and add new node if not present already
	for (int i = 0; i < strlen(key); i++){
		int index = CHAR_TO_INDEX(key[i]);
		if(!current->children[index])
			current->children[index] = newnode();

		current = current->children[index];
	}
	// mark the last node 
	current->is_word = true;
}

//function to search key

bool search(struct node *root, const char *key){
	// for tracking
	struct node *current = root;
	for ( int i = 0; i < strlen(key); i++){
		int index = CHAR_TO_INDEX(key[i]);
		if(current->children[index])
			current = current->children[index];
		else
			return false;
	}
	// check if is_word is true
	return (current->is_word);
}

// load words from dictionary
// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
	int len = strlen(word);
	// create char array to temp store
	char temp[LENGTH+1];
	//For loop convert word to lowercase to store in temp
	for(int i = 0; i < len; i++ ){
		temp[i] = tolower(word[i]);
		i++;
	}
	// need
	return false; // temporary	
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
	tries = newnode();

	// return 1 meaning successful read
	while (fscanf(inptr, "%s", buffer) == 1){
	//read from buffer and build tries
		insert(tries, buffer);
	}
	
	if (feof(inptr)){

		// close dictionary file
		fclose(inptr);
		return true;
	}
	else{
		fclose(inptr);
		return false;
	}
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
	
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
