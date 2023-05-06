// Data Structure Assignment 3.cpp : 
#include<bits/stdc++.h>
using namespace std;
#include"BST.h";
#include"MinHeap.h";
#include"MaxHeap.h";
int main() {
	ifstream MyReadFile("input.txt");
	string Line, n;
	if (MyReadFile.good())
	{
		getline(MyReadFile, Line);
		n = Line;// first line = number of students in the file
	}
	int i = 1;
	string name, department;
	int id;
	double gpa;
	deque<string>info;
	while (getline(MyReadFile, Line)) {
		info.push_back(Line);
	}
	START:
	int ch;
	cout << "Choose Data Structure:\n";
	cout << "For BST      ------> Enter 1\n";
	cout << "For AVL      ------> Enter 2\n";
	cout << "For Min Heap ------> Enter 3\n";
	cout << "For Max Heap ------> Enter 4\n";
	cout << "For Exit Program --> Enter 5\n";
	cin >> ch;
	if (ch == 1) {
		BST b1;
		for (int i = 0; i <= info.size() - 3; i += 4) {
			b1.insert(stoi(info[i]), info[i + 1], stod(info[i + 2]), info[i + 3]);
		}
		int ch2;
		START2:
		cout << "Choose one of the following options:\n";
		cout << "For Add student      -------->Enter 1\n";
		cout << "For Remove student   -------->Enter 2\n";
		cout << "For Search student   -------->Enter 3\n";
		cout << "For Print All(sorted by id)-->Enter 4\n";
		cout << "For Return to main menu  ---->Enter 5\n";
		cin >> ch2;
		if (ch2 == 1) {
			b1.AddStudent();
			goto START2;

		}
		else if (ch2 == 2) {
			b1.RemoveStudent();
			goto START2;
		}
		else if (ch2 == 3) {
			b1.SearchStudent();
			goto START2;
		}
		else if (ch2 == 4) {
			b1.PrintAllSortedByID();
			goto START2;
		}
		else {
			goto START;
		}

	}
	else if (ch == 2) {
		int ch2;
		cout << "Choose one of the following options:\n";
		cout << "For Add student      -------->Enter 1\n";
		cout << "For Remove student   -------->Enter 2\n";
		cout << "For Search student   -------->Enter 3\n";
		cout << "For Print All(sorted by id)-->Enter 4\n";
		cout << "For Return to main menu  ---->Enter 5\n";
		cin >> ch2;
	}
	else if (ch == 3) {
		MinHeap h;
		for (int i = 0; i <= info.size() - 3; i += 4) {
			h.insert(stoi(info[i]), info[i + 1], stod(info[i + 2]), info[i + 3]);
		}
		int ch3;
		START3:
		cout << "Choose one of the following options:\n";
		cout << "For Add student      -------->Enter 1\n";
		cout << "For Print All(sorted by GPA)->Enter 2\n";
		cout << "For Return to main menu  ---->Enter 3\n";

		cin >> ch3;
		if (ch3 == 1) {
			h.AddStudent();
			goto START3;
		}
		else if (ch3 == 2) {
			h.PrintAllStudents();
			goto START3;
		}
		else {
			goto START;
		}

	}
	else if (ch == 4) {
		MaxHeap H;
		for (int i = 0; i <= info.size() - 3; i += 4) {
			H.insert(stoi(info[i]), info[i + 1], stod(info[i + 2]), info[i + 3]);
		}
		int ch4;
		START4:
		cout << "Choose one of the following options:\n";
		cout << "For Add student      -------->Enter 1\n";
		cout << "For Print All(sorted by GPA)-->Enter 2\n";
		cout << "For Return to main menu  ---->Enter 3\n";
		cin >> ch4;
		if (ch4 == 1) {
			H.AddStudent();
			goto START4;

		}
		else if (ch4 == 2) {
			H.PrintAllStudents();
			goto START4;
		}
		else {
			goto START;
		}

	}
	else {
		exit(0);
	}


}