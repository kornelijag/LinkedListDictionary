#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

struct node {
	string englishWord;
	string lithuanianWord;
	struct node *next;
	struct node *previous;
};

class List {
private:

	struct node *head = NULL;

public:

	void addWord(string englishWord, string lithuanianWord) {
		struct node *tmp; 


		if (head == NULL) {

			head = new node();  
								 

			englishWord[0] = toupper(englishWord[0]);
			lithuanianWord[0] = toupper(lithuanianWord[0]);

			head->englishWord = englishWord;
			head->lithuanianWord = lithuanianWord;
			head->next = NULL;  
			head->previous = NULL; 
		}
		else {

			tmp = head; 

						
			while (tmp->next != NULL) { 
																
				tmp = tmp->next; 
			}

			
			tmp->next = new node(); // 2 things happen: 1) another node is created; 2) the pointer "next" of the previous node now points to the newly created one;


			englishWord[0] = toupper(englishWord[0]); 
			lithuanianWord[0] = toupper(lithuanianWord[0]);

			tmp->next->englishWord = englishWord; 
			tmp->next->lithuanianWord = lithuanianWord;
			tmp->next->next = NULL; 
			tmp->next->previous = tmp; 
		}
	}

	void remove(struct node *n) 
	{
		if (head == n) 
		{
			if (head->next == NULL) 
			{
				head = NULL; 
				return;  
			}
			
			head = head->next; 
							   
			head->previous = NULL; 
								   
			free(n); 
			return;
		}


		struct node *prev = n->previous; 
								
		prev->next = n->next; 
							  
		free(n); // deletes the node which "n" was pointing to - frees the address space in which the node was
		return;
	}

	bool wordsMatch(string wordToSearchIn, string wordSearchedFor) {
		size_t wordPosition = wordToSearchIn.find(wordSearchedFor); // size_t is a data type for representing size in bytes, but it is also suitable for counting elements in an array; it counts indexes in the array;
																	// the string class has built-in functions, among them a find function
																	// syntax of find function: stringToSearchIn.find(stringSearchedFor)

		if (wordPosition != string::npos && wordToSearchIn.length() == wordSearchedFor.length()) { // string::npos is a constant which stands for the largest possible index in a string;
																								   // if the function find() cannot find the searched string within the other string, it returns npos 

			return true;
		}
		else {
			return false;
		}
	}

	void searchEngWord(string word)
	{
		word[0] = toupper(word[0]);

		struct node *current;
		current = head; 

		while (current != NULL) { 
			if (wordsMatch(current->englishWord, word) == true) { 
				cout << "Word '" << current->englishWord << "' found!" << " Lithuanian meaning: " << current->lithuanianWord << '\n';
				return;
			}
			current = current->next; 
		}

		cout << "Word not found\n";
	}

	void searchLtWord(string word)
	{
		word[0] = toupper(word[0]);

		struct node *current;
		current = head;

		while (current != NULL) {
			if (wordsMatch(current->lithuanianWord, word) == true) {
				cout << "Word '" << current->lithuanianWord << "' found!" << " English meaning: " << current->englishWord << '\n';
				return;
			}
			current = current->next;
		}

		cout << "Word not found\n";
	}

	void removeEngWord(string word) 
	{
		word[0] = toupper(word[0]);
		struct node *current;
		current = head; 

		while (current != NULL) { 
			if (wordsMatch(current->englishWord, word)) {
				cout << "Word '" << current->englishWord << "' was removed with its translation!" << '\n';
				remove(current); 
				return;
			}
			current = current->next;
		}

		cout << "Word not found\n";
	}

	void removeLtWord(string word)
	{
		word[0] = toupper(word[0]);
		struct node *current;
		current = head;

		while (current != NULL) {
			if (wordsMatch(current->lithuanianWord, word)) {
				cout << "Word '" << current->lithuanianWord << "' was removed with its translation!" << '\n';
				remove(current);
				return;
			}
			current = current->next;
		}

		cout << "Word not found\n";
	}

	void printList()
	{
		struct node *current;
		current = head;
		if (current != NULL)
		{
			//Loops until the end of the list
			while (current != NULL)
			{
				cout << current->englishWord << " - " << current->lithuanianWord << "\n";
				current = current->next;
			}
			
			cout << "\n";
		}

		else {
			printf("The list is empty \n");
		}
	}

	void destroyList()
	{
		struct node *current, *tmp;
		current = head->next; // current takes the address of what "next" is pointing to; thus "current" now points to 2nd node
		head->next = NULL; // "next" of 1st node is set to point to NULL instead of to the 2nd node

		while (current != NULL) { 
			tmp = current->next; // 1st round: tmp set to point to 3rd node;    2nd round: tmp points to 4th node
			free(current); // 1st round: as "current" was set to point to 2nd node, 2nd node is now cleared;    2nd round: 3rd node cleared
			current = tmp; // 1st round: current is now set to point to 3rd node;    2nd round: current points to 4th node
		}
		free(head); 
		head = NULL;
	}


};


class Menu {
public:
	void showMenu() {

		List dictionary;
		dictionary.addWord("Hi", "Labas");
		dictionary.addWord("Bye", "Ate");
		dictionary.addWord("My", "Mano");


		int choice;
		string input;
		string input2;

		do {
			cout << "Menu:\n";
			cout << "1 - Search in English\n";
			cout << "2 - Search in Lithuanian\n";
			cout << "3 - Add entry\n";
			cout << "4 - Remove entry in English\n";
			cout << "5 - Remove entry in Lithuanian\n";
			cout << "6 - Show all words\n";
			cout << "7 - Exit dictionary\n\n";
			cin >> choice;

			switch (choice) {
			case 1:
				cout << "\nType word in Eng and get the LT translation\n\n";
				cin >> input;
				dictionary.searchEngWord(input);
				cout << "\n\n";
				break;
			case 2:
				cout << "\nType word in LT and get the Eng translation\n\n";
				cin >> input;
				dictionary.searchLtWord(input);
				cout << "\n\n";
				break;
			case 3:
				cout << "Input English word\n";
				cin >> input;
				cout << "Input Lithuanian word\n";
				cin >> input2;
				cout << "\n";
				dictionary.addWord(input, input2);
				break;
			case 4:
				cout << "Input English word to remove\n";
				cin >> input;
				dictionary.removeEngWord(input);  
				break;
			case 5:
				cout << "Input Lithuanian word to remove\n";
				cin >> input;
				dictionary.removeLtWord(input);
				break;
			case 6:
				cout << "==========ALL WORDS==========\n\n";
				dictionary.printList();
				cout << "=============================\n\n\n";
				break;
			case 7:
				dictionary.destroyList();
				return;

			default:
				cout << "Menu:\n";
				cout << "1 - Search in English\n";
				cout << "2 - Search in Lithuanian\n";
				cout << "3 - Add\n";
				cout << "4 - Remove entry in English\n";
				cout << "5 - Remove entry in Lithuanian\n";
				cout << "6 - Show all words\n";
				cout << "7 - Exit dictionary\n\n";
				cin >> choice;
			}
		} while (choice != 7);


	}
};

int main()
{
	Menu menu;
	menu.showMenu();

	return 0;
}

