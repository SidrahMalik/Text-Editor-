#include<iostream>
#include<Windows.h>
#include"Trie.h"
#include<string>
#include<stack>
#include<fstream>
using namespace std;
int x = 15, y = 100;     // x are rows and y are columns of text box.
class Node    // Nodes of quad linked list
{
public:
	char data;
	Node* left;
	Node* right;
	Node* up;
	Node* down;
	Node()
	{
		this->data = data;
		left = NULL;
		right = NULL;
		up = NULL;
		down = NULL;
	}
};
class QuadLL
{
public:
	Node* head; 
	Node* crr;
	int lastrun = 0;
	bool iscopied = false;
	string copied;
	stack<int>x_axis;
	stack<int>y_axis;
	stack<string>datastr;
	stack<string>function;
	QuadLL()
	{
		head = NULL;
		start();

	}
	void start()
	{
		int count = 0;
		while (count != x)
		{
			if (count == 0)
			{
				for (int i = 0; i <= y; i++)
				{
					if (head == NULL)
					{
						Node* newNode = new Node();
						newNode->right = nullptr;
						newNode->data = ' ';
						newNode->down = NULL;
						newNode->left = NULL;
						newNode->up = NULL;
						head = newNode;
						continue;
					}
					else
					{
						Node* curr = head;
						while (curr->right != NULL)
						{
							curr = curr->right;
						}
						Node* newNode = new Node();
						newNode->right = nullptr;
						newNode->data = ' ';
						newNode->down = NULL;
						newNode->left = curr;
						newNode->up = NULL;
						curr->right = newNode;
						crr = curr;
					}
				}

			}
			else if (count > 0)
			{

				Node* curr = head;
				while (curr->down != NULL)
				{
					curr = curr->down;
				}
				Node* curr1 = curr->down;
				for (int i = 0; i <= y; i++)
				{
					if (i == 0)
					{
						Node* newNode = new Node();
						newNode->right = nullptr;
						newNode->data = ' ';
						newNode->down = NULL;
						newNode->left = NULL;
						newNode->up = curr;
						curr1 = newNode;
						curr->down = curr1;

						if (curr->right != NULL)
						{
							curr = curr->right;
						}
						crr = curr1;
					}
					else
					{

						Node* newNode = new Node();
						newNode->right = nullptr;
						newNode->data = ' ';
						newNode->down = NULL;
						newNode->left = curr1;
						newNode->up = curr;

						curr1->right = newNode;
						curr1 = curr1->right;
						curr->down = newNode;
						if (curr->right != NULL)
						{
							curr = curr->right;
						}
						crr = curr1;
					}
				}
			}
			count++;
		}
		fstream f1;
		f1.open("myfile.txt", ios::in);
		string str11;
		int i = 0, j = 0;
		while (!f1.eof()&&i<x)
		{
			getline(f1, str11);
			string str22 = "";
			int k2 = 0;
			for (int k1 = 1; k1 < str11.length(); k1++)
			{
				str22+= str11[k1];
			}
			insert(str22, i, j);
			i++;
		}
	}

	/* Node leftious(int x, int y)
	{
		int countx = 0;
		int county = 0;
		Node* temp = head;

	}
	*/
	Node* findn(int x1, int y1)
	{

		Node* temp = head;
		Node* temp1 = head;

		for (int i = 0; i <= x1; i++)
		{
			temp = temp1;
			if (i == x1)
			{
				for (int j = 0; j < y1; j++)
				{
					temp = temp->right;
				}
			}
			temp1 = temp1->down;
		}
		return temp;
	}
	bool search1(string str)//here we are searching string for deletion and if match then will delete and return 
	{
		Node* temp = head;
		Node* temp1 = head;
		Node* temp2 = NULL;
		bool found = false;
		for (int i = 0; i <= x; i++)
		{
			temp = temp1;
			int k = 0;

			for (int j = 0; j < y; j++)
			{
				temp = temp->right;
				if (temp->data == str[k])
				{
					if (k == 0)
					{
						temp2 = temp;
						k++;
					}
					else
					{
						k++;
					}
					if (k == str.length())
					{
						found = true;
						break;
					}
				}
				else
				{
					k = 0;
				}
			}

			temp1 = temp1->down;
			if (found == true)
			{
				break;
			}
		}
		return found;
	}
	void Delete(string str)
	{
		Node* temp = head;
		Node* temp1 = head;
		Node* temp2=NULL;
		bool found = false;
		for (int i = 0; i <= x; i++)
		{
			temp = temp1;
			int k = 0;

			for (int j = 0; j < y; j++)
			{
				temp = temp->right;
				if (temp->data == str[k])
				{
					if (k == 0)
					{
						temp2 = temp;
						k++;
					}
					else
					{
						k++;
					}
					if (k == str.length())
					{
						found = true;
						break;
					}
				}
				else
				{
					k = 0;
				}
			}

			temp1 = temp1->down;
			if (found == true)
			{
				break;
			}
		}
		if (found == true)
		{
			cout << "\nMatch found:\n";
			cout << "DELETED Successfully\n";
			Node* temp3 = temp2;
			for (int i = 0; i < str.length(); i++)
			{
				if (temp2->data == str[i])
				{
					temp2->data = ' ';
					temp2 = temp2->right;
				}
			}
			while (temp2->right != NULL)
			{
				temp3->data = temp2->data;
				temp3 = temp3->right;
				temp2 = temp2->right;
			}
		}
	}
	void insert(string data, int x1, int y1)  // x and y are the positions after which we will inert right word
	{                                      // Just like Naqvi after Aiman 
		Node* newNode = new Node;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->up = NULL;
		newNode->down = NULL;
		Node* temp = findn(x1, y1);//node return by function where we sre going to write data simply rewrite the data of node
		for (int i = 0; i < data.length(); i++)//loop to go to that position and write data to that position as node was returned by the function
		{
			temp->right->data = data[i];
			temp = temp->right;
		}
	}

	

	void display()
	{
		Node* temp = head;
		Node* temp1 = head;
		
		for (int i = 0; i < y; i++)
		{
			if (i == 0)
			{
				cout << "-";
			}
			else
			{
				cout << "-";
			}
		}
		cout << endl;
		for (int i = 0; i < x; i++)
		{
			temp = temp1;
			cout << "|";
			for (int j = 0; j < y; j++)
			{
				cout << temp->data;
				temp = temp->right;
			}

			cout <<"|" << endl;
			temp1 = temp1->down;
		}
		for (int i = 0; i < y; i++)
		{
			if (i == 0)
			{
				cout << "-";
			}
			else
			{
				cout << "-";
			}
		}
		cout << endl;
	}
	string copy(int x1, int y1, int x2, int y2)
	{

		Node* temp = head;
		Node* temp1 = head;
		int count1 = 0;
		bool f1 = false;
		for (int i = 0; i <= x1; i++)
		{
			temp = temp1;
			if (i == x1)
			{
				for (int j = 0; j <= y1; j++)
				{
					temp = temp->right;
					if (j == y1)
					{
						f1 = true;
					}
				}
			}
			if (f1 != true)
			{
				count1++;
				temp1 = temp1->down;
			}
		}
		string str1 = "";
		int c1 = 0;
		for (int i = x1; i <= x2; i++)
		{
			if (i != x1)
			{
				temp = temp1;
			}
			if (x1 == x2)
			{
				for (int j = y1; j < y2; j++)
				{
					str1 += temp->data;
					temp = temp->right;
				}
			}
			else if (x1 < x2)
			{
				if (count1 == x1)
				{
					for (int j = y1; j < y; j++)
					{
						str1 += temp->data;
						temp = temp->right;
					}
					
				}
				else if(count1<x2)
				{
					for (int j = 0; j < y; j++)
					{
						str1 += temp->data;
						temp = temp->right;
					}
				}
				else if (count1 == x2)
				{
					for (int j = 0; j < y1; j++)
					{
						str1 += temp->data;
						temp = temp->right;
					}
				}
			}
			count1++;
			temp1 = temp1->down;
		}
		return str1;
	}
	void replace(string str,string s2)
	{

		Node* temp = head;
		Node* temp1 = head;
		Node* temp2 = NULL;
		bool found = false;
		for (int i = 0; i <= x; i++)//In this nested we are checking string we need to replace exist or not
		{
			temp = temp1;
			int k = 0;

			for (int j = 0; j < y; j++)
			{
				temp = temp->right;
				if (temp->data == str[k])
				{
					if (k == 0)
					{
						temp2 = temp;
						k++;
					}
					else
					{
						k++;
					}
					if (k == str.length())
					{
						found = true;
						break;
					}
				}
				else
				{
					k = 0;
				}
			}

			temp1 = temp1->down;
			if (found == true)
			{
				break;
			}
		}
		
		if (found == true)
		{
			cout << "\nMatch found:\n";
			
			Node* temp3 = temp2;
			int c111=0;
			if (str.length() >= s2.length())
			{
				for (int i = 1; i <= str.length(); i++)
				{
					if (temp2->data == str[i-1])
					{
						if (i < s2.length())
						{
							temp2->data = s2[i-1];
							c111++;
						}
						else if (i == s2.length())
						{
							temp2->data = s2[i - 1];
							c111++;
							temp3 = temp2->right;
						}
						else
						{
							temp2->data = ' ';
						}
						temp2 = temp2->right;
					}
				}
				if (str.length() > s2.length())
				{
					while (temp2->right != NULL)
					{
						temp3->data = temp2->data;
						temp3 = temp3->right;
						temp2 = temp2->right;
					}
				}
			}
			else if (str.length() < s2.length())
			{
				Node* temp4 = temp;
				while (temp4->right != nullptr)
				{
					temp4 = temp4->right;
				}
				int count12 = 0;
				Node* temp5 = temp4;
				while (temp4->data == ' ')
				{
					count12++;
					temp4 = temp4->left;
				}
				if (s2.length() <= count12 + str.length())
				{
					int c121 = s2.length() - str.length();
					int c122 = count12 - c121;
					while (c122 != 0)
					{
						temp5 = temp5->left;
						c122--;
					}
					while (temp4 != temp)
					{
						temp5->data = temp4->data;
						temp4 = temp4->left;
						temp5 = temp5->left;
					}
					for (int i = 0; i < s2.length(); i++)
					{
						temp2->data = s2[i];
						temp2 = temp2->right;
					}

				}
				else
				{
					cout << "Cannot be replced as space is less\n";
				}
			}
		}
		else
		{
			cout << "This word doesn't exist in this data set\n";
		}
	}
	void start2(TrieTree obj)//function in which we are taking inputs and calling for all the modules 
	{							
		system("pause");
		system("cls");
		obj.readFromFile();//calling a function to load upload file into trie tree
		while (true)
		{
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(h, 13);
			int x1, y1;
			int x2, y2;
			obj.mainMenu();//calling main menu to take a choice from user
			if (obj.check1 == 1)
			{
				lastrun = 1;
				string str1 = obj.inputData;
				cout << endl;
				display();

				while (true)
				{
					cout << " Enter the position of x and y where you want to Insert\n" << endl;
					cout << "Enter x: ";
					cin >> x1;
					cout << "Enter y: ";
					cin >> y1;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore();
						continue;
					}
					if (x1 < x && y1 < y)
					{
						break;
					}
					else
					{
						cout << "Invalid input\n";
						system("pause");
						system("cls");
					}
				}
				insert(str1, x1, y1);
				x_axis.push(x1);
				y_axis.push(y1);
				datastr.push(str1);
				function.push("insert");
				system("cls");
				display();
				system("pause");
				system("cls");
			}
			else if (obj.check1 == 2)
			{
				lastrun = 2;
				system("cls");
				obj.inputData = "";
				obj.typingText();//function to take input in string with suggestions
				Delete(obj.inputData);
				system("pause");
			}
			else if (obj.check1 == 3)
			{
				lastrun = 3;
				system("cls");
				obj.inputData = "";
				obj.typingText();//function to take input in string with suggestions
				bool searchinp = search1(obj.inputData);
				if (searchinp == true)
				{
					cout << "This word Exist in this data set\n";
				}
				else
				{
					cout << "This word Not Found in this data set\n";
				}
				system("pause");
				system("cls");
			}
			else if (obj.check1 == 4)
			{
				lastrun = 4;
				cout << endl;
				display();

				while (true)
				{
					cout << " Enter the Starting position position of x and y where you want to Copy\n" << endl;
					cout << "Enter x: ";
					cin >> x1;
					cout << "Enter y: ";
					cin >> y1;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore();
						continue;
					}
					if (x1 < x && y1 < y)
					{
						break;
					}
					else
					{
						cout << "Invalid input\n";
						system("pause");
						system("cls");
					}
				}
				while (true)
				{
					cout << " Enter the Ending position position of x and y where you want to Copy\n" << endl;
					cout << "Enter x: ";
					cin >> x2;
					cout << "Enter y: ";
					cin >> y2;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore();
						continue;
					}
					if (x2 < x && y2 < y && x2 == x1)
					{
						if (x2 == x1)
						{
							if (y1 < y2)
							{
								break;
							}
						}

					}

					cout << "Invalid input\n";
				}

				obj.inputData = copy(x1, y1, x2, y2);
				cout << "The copied Text is : " << obj.inputData << endl;
				copied = obj.inputData;
				iscopied = true;
				system("pause");
				system("cls");
			}
			else if (obj.check1 == 5)
			{
				if (iscopied == true)
				{
					while (true)
					{
						cout << " Enter the position of x and y where you want to Paste\n" << endl;
						cout << "Enter x: ";
						cin >> x1;
						cout << "Enter y: ";
						cin >> y1;
						if (cin.fail())
						{
							cin.clear();
							cin.ignore();
							continue;
						}
						if (x1 < x && y1 < y)
						{
							break;
						}
						else
						{
							cout << "Invalid input\n";
							system("pause");
							system("cls");
						}
					}
					insert(copied, x1, y1);
					system("cls");
					display();
					system("pause");
					system("cls");
				}
				else
				{
					cout << "Nothing is copied yet\n\n";
					system("pause");
					system("cls");
				}
			}
			else if (obj.check1 == 6)
			{
				lastrun = 2;
				system("cls");
				cout << "Enter word you want to replace: \n";
				obj.inputData = "";
				obj.typingText();//function to take input in string with suggestions
				string x21 = obj.inputData;
				cout << "Enter word to write in replace of "<<x21<<" :\n";
				obj.inputData = "";
				obj.typingText();//function to take input in string with suggestions
				string x22 = obj.inputData;
				replace(x21, x22);
				system("cls");
				display();
				system("pause");
				system("cls");

			}
			else if (obj.check1 == 7)
			{
				lastrun = 2;
				system("cls");
				display();
				while (!function.empty())
				{
					function.pop();
					string str1 = datastr.top();
					datastr.pop();
					Delete(str1);
					system("cls");
					display();
				}
			}
			else if (obj.check1 == 8)
			{
				
				system("cls");
				display();
				int nowords = 0;
				Node* temp = head;
				Node* temp1 = head;

				for (int i = 0; i < x; i++)
				{
					temp = temp1;

					for (int j = 0; j < y; j++)
					{
						if (temp->data>=97&&temp->data<=122)
						{
							nowords++;
						}
						temp = temp->right;
					}

					temp1 = temp1->down;
				}
				
				cout << "No of word in this data set are " << nowords<<endl;
				system("pause");
			}
			else if (obj.check1 == 9)
			{
				system("cls");
				fstream f1;
				f1.open("myfile.txt", ios::out);
				Node* temp = head;
				Node* temp1 = head;

				
				for (int i = 0; i < x; i++)
				{
					temp = temp1;
					
					for (int j = 0; j < y; j++)
					{
						f1 << temp->data;
						temp = temp->right;
					}

					f1 << endl;
					temp1 = temp1->down;
				}
				cout << "Data saved Succesfully " << endl;
				system("pause");
			}
		}
		
	}
};
int main()
{
	TrieTree objTrie;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 13);
	objTrie.instruction();
	QuadLL obj1;
	obj1.start2(objTrie);
	system("pause");
	return 0;
}