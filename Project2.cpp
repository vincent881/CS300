/*
Vincent Messina
2/14/23
This program loads a data file from a csv file, prints a course list
in alphanumeric order, and prints a specific course and prerequisites. 
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

//function to display menu
void DisplayMenu() {
	cout << "1. Load Data Structure." << endl;
	cout << "2. Print Course List." << endl;
	cout << "3. Print Course." << endl;
	cout << "4. Exit." << endl << endl;
	cout << "What would you like to do?";
}

//defines a structure to hold course information
struct Course {
	string courseId;
	string courseName;
	vector<string> prerequisite;
};

//internal structure for tree node
struct Node {
	Course course;
	Node* left;
	Node* right;

	//default constructor
	Node() {
		left = nullptr;
		right = nullptr;
	}
	Node(Course givenCourse) : Node() {
		this->course = givenCourse;
	}
};

//class containing data members and methods to implement a binary search tree
class BinarySearchTree {

private:
	
	void Destruct(Node* node);

public:
	Node* root;
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void Insert(BinarySearchTree* tree, Node* node);
	void Search(string courseId);
	void PrintCourse(Node* node);
};

//default constructor
BinarySearchTree::BinarySearchTree() {
	root = nullptr;
};

//destructor
BinarySearchTree::~BinarySearchTree() {
	Destruct(root);
};

void BinarySearchTree::Destruct(Node* node) {
	if (node != nullptr) {
		Destruct(node->left);
		node->left = nullptr;
		Destruct(node->right);
		node->right = nullptr;
		delete node;
	}
};

//searching for a course
void BinarySearchTree::Search(string courseId) {
	Node* currentNode = root;

	while (currentNode != nullptr) {
		if (currentNode->course.courseId == courseId) {
			cout << currentNode->course.courseId << ", ";
			cout << currentNode->course.courseName << endl;
			cout << "Prerequisites: ";
			//prints prerequisites
			for (string preRequisite : currentNode->course.prerequisite) {
				if (preRequisite == currentNode->course.prerequisite.back()) {
					cout << preRequisite << endl;
				}
				else {
					cout << preRequisite << endl;
				}
			}
			return;
		}
		//searches left pointer if not found
		else if (courseId < currentNode->course.courseId) {
			if (currentNode->left != nullptr) {
				currentNode = currentNode->left;
			}
		}
		//searches right pointer if not found
		else {
			currentNode = currentNode->right;
		}
	}
	cout << "Course" << courseId << "not found." << endl;
	return;
}

//inserts a course into a list
void BinarySearchTree::Insert(BinarySearchTree* tree, Node* node) {
	if (tree->root == nullptr) {
		tree->root = node;
	}
	else {
		Node* curr = tree->root;
		while (curr != nullptr) {
			if (node->course.courseId < curr->course.courseId) {
				if (curr->left == nullptr) {
					curr->left = node;
					curr = nullptr;
				}
				else {
					curr = curr->left;
				}
			}
			else {
				if (curr->right == nullptr) {
					curr->right = node;
					curr = nullptr;
				}
				else {
					curr = curr->right;
				}
			}
		}
	}
}
//prints course list
void BinarySearchTree::PrintCourse(Node* node) {
	//traverse and print tree
	if (node == nullptr) {
		return;
	}
	//look at left node, print course id, name, and look at next node
	PrintCourse(node->left);
	cout << node->course.courseId << ", ";
	cout << node->course.courseName << endl;
	PrintCourse(node->right);
};

//load file and create course list
void loadCourse(string filename, BinarySearchTree* bst) {
	ifstream file(filename);
	if (file.is_open()) {
		cout << "File loaded" << endl;
		
		int num;
		string line;
		string word;

		while (getline(file, line)) {

			num = 0;
			Node* node = new Node();
			stringstream str(line);
			
			while (num < 2) {
				getline(str, word, ',');
				if (num == 0) {
					node->course.courseId = word;
				}
				else {
					node->course.courseName = word;
				}
				num++;
			}
			while (getline(str, word, ',')) {
				node->course.prerequisite.push_back(word);
			}
			bst->Insert(bst, node);
		}
	}
	//error message if file not found
	else {
		cout << "File error, please try again." << endl;
		return;
	}
}
void main() {
	BinarySearchTree* bst = new BinarySearchTree();
	
	string fileChoice;
	string courseChoice;
	int input = 0;

	//while loop to keep program open while choice is not exit
	while (input != 4) {
		DisplayMenu();
		cin >> input;

		switch (input) {
			//loads users file
		case 1:
			cout << endl;
			cout << "Which file do you want to load?";
			cin >> fileChoice;
			loadCourse(fileChoice, bst);
			cout << endl;
			break;

		//prints courses in alphanumeric order
		case 2:
			cout << "Here is a sample schedule:" << endl;
			bst->PrintCourse(bst->root);
			cout << endl;
			break;

		//prints course chosen and prerequisites
		case 3:
			cout << endl;
			cout << "Enter a course:";
			cin >> courseChoice;
			cout << endl;
			std::transform(courseChoice.begin(), courseChoice.end(), courseChoice.begin(), ::toupper);
			bst->Search(courseChoice);
			cout << endl;
			break;
		//exits program
		case 4:
			cout << "Thank you for using the course planner!";
			break;
		//message if one of the coices are not entered
		default:
			cout << input << " is not a valid option" << endl;
			break;
		}
	}
}