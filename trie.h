#pragma once
#include<iostream>
#include<Windows.h>
using namespace std;
#define ESCAPE 27

struct NodeTrieTree {
	char character;
	bool endWord;
	NodeTrieTree* children[26];
};

class TrieTree {
private:
	NodeTrieTree* root;
	NodeTrieTree* tempNode;
	int suggestedWords;
	
public:
	TrieTree();
	void destroyTrieTree(NodeTrieTree* rootNode);
	~TrieTree();
	int check1 = 0;
	string inputData;
	void mainMenu();
	void instruction();

	NodeTrieTree* insertInTrieTree(NodeTrieTree* rootNode, char ch, bool endOfWord);

	void readFromFile();
	void typingText();

	void findSuggestions(NodeTrieTree* rootNode, std::string input, std::string* suggestions);
	void find(NodeTrieTree* rootNode, std::string* suggestions, std::string input);

	void displaySuggestions(std::string* suggestions, int currSuggestion);
}; 
