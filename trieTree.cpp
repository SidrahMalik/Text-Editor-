#include"Trie.h"
#include<conio.h>
#include<fstream>
#include<iostream>
#include<Windows.h>

TrieTree::TrieTree() {
	root = new NodeTrieTree();
	root->endWord = false;
	for (int i = 0; i < 26; i++)
		root->children[i] = nullptr;
	tempNode = nullptr;
	suggestedWords = 0;
}

void TrieTree::destroyTrieTree(NodeTrieTree* rootNode) {
	for (int i = 0; i < 26; i++) {
		if (rootNode) {
			destroyTrieTree(rootNode->children[i]);
		}
	}
	delete rootNode;
	rootNode = nullptr;
}

TrieTree::~TrieTree() {
	destroyTrieTree(root);
}

NodeTrieTree* TrieTree::insertInTrieTree(NodeTrieTree* rootNode, char ch, bool endOfWord) {
	int index = ch - 97;
	if (index < 0 || index >= 25)
		return rootNode;
	if (!rootNode->children[index]) {
		NodeTrieTree* newNode;
		newNode = new NodeTrieTree();
		newNode->character = ch;
		newNode->endWord = endOfWord;

		rootNode->children[index] = newNode;
		for (int i = 0; i < 26; i++)
			rootNode->children[index]->children[i] = nullptr;
		return rootNode->children[index];
	}

	if (endOfWord == true)
		rootNode->children[index]->endWord = endOfWord;
	return rootNode->children[index];
}

void TrieTree::readFromFile() {
	std::ifstream in;
	std::string str;
	in.open("outfile.txt");
	while (!in.eof()) {
		tempNode = root;
		in >> str;
		for (int i = 0; i < str.length(); i++) {
			if (i == str.length() - 1)
				tempNode = insertInTrieTree(tempNode, str[i], true);
			else
				tempNode = insertInTrieTree(tempNode, str[i], false);
		}
		tempNode = nullptr;
	}
	in.close();
}

void TrieTree::find(NodeTrieTree* rootNode, std::string* suggestions, std::string input) {
	if (suggestedWords == 10)
		return;
	bool check = false;
	for (int i = 0; (i < 26) && suggestedWords <= 9; i++) {
		if (rootNode->children[i]) {
			rootNode = rootNode->children[i];
			suggestions[suggestedWords] += rootNode->character;
			if (rootNode->endWord == true) {
				suggestedWords++;
				if (suggestedWords == 10)
					break;
				for (int j = 0; j < 26; j++) {
					if (rootNode->children[j]) {
						check = true;
						break;
					}
				}
				if (!check)
					suggestions[suggestedWords] = input;
				else
					suggestions[suggestedWords] = suggestions[suggestedWords - 1];
			}
			find(rootNode, suggestions, input);
		}
	}
}


void TrieTree::findSuggestions(NodeTrieTree* rootNode, std::string input, std::string* suggestions) {
	if (input.length() == 0)
		return;
	suggestedWords = 0;
	tempNode = root;
	for (int i = 0; i < input.length(); i++) {
		int index = input[i] - 97;
		if (tempNode->children[index])
			tempNode = tempNode->children[index];
		else
			return;
	}
	suggestions[suggestedWords] = input;
	find(tempNode, suggestions, input);
}

void TrieTree::typingText() {
	std::string* suggestions = new std::string[10];
	int currSuggestion = -1;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Enter: " << inputData;
	if (inputData.length() != 0) {
		findSuggestions(root, inputData, suggestions);
		displaySuggestions(suggestions, currSuggestion);
	}
	while (true) {
		char getChar = 0;
		getChar = _getch();
		system("cls");
		if (getChar >= 'a' && getChar <= 'z') {
			currSuggestion = -1;
			inputData += getChar;

			int indexSpace = -1;
			for (int i = 0; i < inputData.length(); i++)
				if (inputData[i] == ' ')
					indexSpace = i + 1;

			std::string currentWord = "";
			if (indexSpace != -1) {
				for (indexSpace; indexSpace < inputData.length(); indexSpace++)
					currentWord += inputData[indexSpace];
			}
			else
				currentWord = inputData;

			findSuggestions(root, currentWord, suggestions);
			std::cout << "Enter: " << inputData;
			displaySuggestions(suggestions, currSuggestion);
		}
		else if (getChar == '/') {
			currSuggestion++;
			if (currSuggestion > suggestedWords - 1)
				currSuggestion--;
			std::cout << "Enter: " << inputData;
			displaySuggestions(suggestions, currSuggestion);
		}
		else if (getChar == ';') {
			if (currSuggestion >= 0) {
				int indexSpace = -1;
				for (int i = 0; i < inputData.length(); i++)
					if (inputData[i] == ' ')
						indexSpace = i + 1;
				if (indexSpace == -1)
					inputData = suggestions[currSuggestion] + ' ';
				else {
					inputData.resize(indexSpace);
					inputData += suggestions[currSuggestion] + ' ';
				}
			}
			findSuggestions(root, inputData, suggestions);
			currSuggestion = -1;
			std::cout << "Enter: " << inputData;
			displaySuggestions(suggestions, currSuggestion);
		}
		else if (getChar == '=') {

			std::cout << "Enter: " << inputData;
			displaySuggestions(suggestions, currSuggestion);
		}
		else if (getChar == '\b') {
			if (inputData.length() != 0) {
				std::string tempStr;
				for (int i = 0; i < inputData.length() - 1; i++)
					tempStr += inputData[i];
				inputData = tempStr;
			}

			int indexSpace = -1;
			for (int i = 0; i < inputData.length(); i++)
				if (inputData[i] == ' ')
					indexSpace = i + 1;

			std::string currentWord = "";
			if (indexSpace != -1) {
				for (indexSpace; indexSpace < inputData.length(); indexSpace++)
					currentWord += inputData[indexSpace];
			}
			else
				currentWord = inputData;

			findSuggestions(root, currentWord, suggestions);
			std::cout << "Enter: " << inputData;
			if (inputData == "")
				suggestedWords = 0;
			displaySuggestions(suggestions, currSuggestion);
		}
		else if (getChar == ESCAPE) {
			break;
			//mainMenu();
		}
		else if (getChar == ' ' && inputData.length() > 0 && inputData[inputData.length() - 1] != ' ') {
			inputData += ' ';
			std::cout << "Enter: " << inputData;
			displaySuggestions(suggestions, currSuggestion);
		}
		else {
			std::cout << "Enter: " << inputData;
			displaySuggestions(suggestions, currSuggestion);
		}
	}
}

void TrieTree::instruction() {
	std::cout << "\n\n\n\t\t\t\t\t ---------------\n";
	std::cout << "\t\t\t\t\t>| TEXT EDITOR |<\n";
	std::cout << "\t\t\t\t\t ---------------\n\n";
	std::cout << "Instructions:\n";
	std::cout << "1. Press '=' to save the current data.\n";
	std::cout << "2. Press '/' to go to the next suggestion.\n";
	std::cout << "3. Press ';' to select the suggestion.\n";
	std::cout << "4. Press Escape to return to End Typing.\n";
}

void TrieTree::mainMenu() {
	char input;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 13);
	srand((time(0)));
	while (true) {
		SetConsoleTextAttribute(h, 4);
		std::cout << "\t\t\t\t\t\t\t\t\t\tCreated By:";
		SetConsoleTextAttribute(h, 4);
		std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t1.";
		SetConsoleTextAttribute(h, 13);
		std::cout << " 21F-9308.";
		SetConsoleTextAttribute(h, 4);
		std::cout << "\n\n\n\t\t\t\t\t ---------------\n";
		std::cout << "\t\t\t\t\t>| ";
		SetConsoleTextAttribute(h, 13);
		std::cout << "TEXT EDITOR";
		SetConsoleTextAttribute(h, 4);
		std::cout << " |<\n";
		std::cout << "\t\t\t\t\t ---------------\n\n";
		std::cout << "\t\t\t ---------------------------------------------\n";
		std::cout << "\t\t\t>| ";
		SetConsoleTextAttribute(h, 13);
		std::cout << "BETTER COMMUNICATION FOR BETTER FUTURE";
		SetConsoleTextAttribute(h, 2);
		std::cout << " :)";
		SetConsoleTextAttribute(h, 4);
		std::cout << " |<\n";
		std::cout << "\t\t\t ---------------------------------------------\n\n";
		std::cout << "\t -------------\n";
		std::cout << "\t>|";
		SetConsoleTextAttribute(h, 13);
		std::cout << " MAIN MENU";
		SetConsoleTextAttribute(h, 4);
		std::cout << " |<\n";
		std::cout << "\t -------------\n\n";
		std::cout << "\t1.";
		SetConsoleTextAttribute(h, 13);
		std::cout << " Add Text.\n";
		SetConsoleTextAttribute(h, 4);
		std::cout << "\t2.";
		SetConsoleTextAttribute(h, 13);
		std::cout << " Delete Text.\n";
		SetConsoleTextAttribute(h, 4);
		std::cout << "\t3.";
		SetConsoleTextAttribute(h, 13);
		std::cout << " Search Words.\n";
		SetConsoleTextAttribute(h, 4);
		std::cout << "\t4.";
		SetConsoleTextAttribute(h, 13);
		std::cout << " Copy Text.\n";
		SetConsoleTextAttribute(h, 4);
		std::cout << "\t5.";
		SetConsoleTextAttribute(h, 13);
		std::cout << " Paste Text.\n";
		SetConsoleTextAttribute(h, 4);
		std::cout << "\t6.";
		SetConsoleTextAttribute(h, 13);
		std::cout << " Find a word and replace It.\n";
		SetConsoleTextAttribute(h, 4);
		std::cout << "\t7.";
		SetConsoleTextAttribute(h, 13);
		std::cout << " Undo Text.\n";
		SetConsoleTextAttribute(h, 4);
		std::cout << "\t8.";
		SetConsoleTextAttribute(h, 13);
		std::cout << " Count Total Words.\n";
		SetConsoleTextAttribute(h, 4);
		std::cout << "\t9.";
		SetConsoleTextAttribute(h, 13);
		std::cout << " Save txt.\n";
		SetConsoleTextAttribute(h, 4);
		std::cout << "\t10.";
		SetConsoleTextAttribute(h, 13);
		std::cout << " Similarity Cheacker.\n";
		std::cout << "\tPress any key to exit.\n";
		SetConsoleTextAttribute(h, 2);
		std::cout << "\tInput: ";
		SetConsoleTextAttribute(h, 13);
		std::cin >> input;
		switch (input) {
		case '1':
			system("cls");
			typingText();
			check1 = 1;
			return;
			break;
		case '2':
		
			check1 = 2;
			return;
			break;
		case '3':

			check1 = 3;
			return;
			break;
		case '4':

			check1 = 4;
			return;
			break;
		case '5':

			check1 = 5;
			return;
			break;
		case '6':

			check1 = 6;
			return;
			break;
		case '7':

			check1 = 7;
			return;
			break;
		case '8':

			check1 = 8;
			return;
			break;
		case '9':

			check1 = 9;
			return;
			break;
		case '10':

			check1 = 10;
			return;
			break;
		default:
			for (int i = 5; i >= 0; i--) {
				system("cls");
				std::cout << "Editor will shut down in " << i << " seconds\n";
				Sleep(1000);
			}
			system("cls");
			exit(0);
		}
		system("pause");
		system("cls");
	}
}

void TrieTree::displaySuggestions(std::string* suggestions, int currSuggestion) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 6);
	std::cout << "\nSuggestions:\n";
	SetConsoleTextAttribute(h, 4);
	if (suggestedWords == 0)
		std::cout << "\tNo Suggestions Available.\n";
	for (int i = 0; i < suggestedWords; i++) {
		if (i == currSuggestion) {
			SetConsoleTextAttribute(h, 2);
			std::cout << "    --->";
			SetConsoleTextAttribute(h, 9);
		}
		else
			std::cout << "\t";
		std::cout << i + 1 << ". ";
		std::cout << suggestions[i] << "\n";
	}
	SetConsoleTextAttribute(h, 2);
}