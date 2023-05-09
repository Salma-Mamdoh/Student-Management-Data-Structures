#pragma once
#include<bits/stdc++.h>
using namespace std;

class AVL
{
	struct student {
		int id;
		string name;
		double gpa;
		string department;
		student* before;
		student* after;
		int height;
		student(int d, string n, double g, string de) {
			id = d;
			name = n;
			gpa = g;
			department = de;

		}
		student() {};
	};
	student* root;
	map<string, int>depart;
	int height(student* s)
	{
		if (s == NULL)
			return 0;
		return s->height;
	} 
	student* rightRotate(student* y)
	{
		student* x = y->before;
		student* T2 = x->after;
		x->after = y;
		y->before = T2;
		y->height = max(height(y->before),
			height(y->after)) + 1;
		x->height = max(height(x->before),
			height(x->after)) + 1;
		return x;
	}
	student* leftRotate(student* x)
	{
		student* y = x->after;
		student* T2 = y->before;
		y->before = x;
		x->after = T2;
		x->height = max(height(x->before),
			height(x->after)) + 1;
		y->height = max(height(y->before),
			height(y->after)) + 1;
		return y;
	}
	int getBalance(student* s)
	{
		if (s == NULL)
			return 0;
		return height(s->before) - height(s->after);
	}
	student* insert(student* node, int key,string name,double gpa , string depart)
	{
		
		if (node == NULL) {
			student* newnode = new student(key,name,gpa,depart);
			newnode->before = NULL;
			newnode->after = NULL;
			newnode->height = 1;
			return newnode;
		}

		if (key < node->id)
			node->before = insert(node->before, key,name,gpa,depart);
		else if (key > node->id)
			node->after = insert(node->after, key,name,gpa,depart);
		else 
			return node;
		node->height = 1 + max(height(node->before),
			height(node->after));
		int balance = getBalance(node);
		if (balance > 1 && key < node->before->id)
			return rightRotate(node);
		if (balance < -1 && key > node->after->id)
			return leftRotate(node);
		if (balance > 1 && key > node->before->id)
		{
			node->before = leftRotate(node->before);
			return rightRotate(node);
		}
		if (balance < -1 && key < node->after->id)
		{
			node->after = rightRotate(node->after);
			return leftRotate(node);
		}
		return node;
	}
	void inorder(student* root) {
		if (root == NULL) {
			return;
		}
		inorder(root->before);
		depart[root->department]++;
		cout << "[" << root->id << " " << root->name << " " << root->gpa << " " << root->department << "]" << "\n";
		inorder(root->after);
	}
	bool search(int sid) {
		student* curr = root;
		while (curr != NULL) {
			if (curr->id == sid) {
				cout << "Student is found\n";
				cout << "[" << curr->id << " " << curr->name << " " << curr->gpa << " " << curr->department << "]" << "\n";
				return true;
			}
			else if (curr->id > sid) curr = curr->before;
			else curr = curr->after;
		}
		return false;
	}
public :
	void EnterData() {
		char sname[1000];
		string sdepartment;
		int sid;
		double sgpa;
		cout << "Enter your ID : ";
		cin >> sid;
		while (!(sid >= 0 && sid <= 100)) {
			cout << "This invalid id\n";
			cout << "Enter valid ID\n";
			cin >> sid;
		}
		cout << "Enter your Name : ";
		cin.ignore();
		cin.getline(sname, 1000, '\n');
		cout << "Enter your GPA : ";
		cin >> sgpa;
		cout << "Enter your Department : ";
		cin >> sdepartment;
		AddStudent(sid, sname, sgpa, sdepartment);
		cout << "The student is added.\n";
	}
	void AddStudent(int id,string name, double gpa,string depart) {
		root = insert(root, id,name,gpa,depart);
	}
	void printAllStudents() {
		inorder(root);
		cout << "Students per Departments:\n";
		for (auto i : depart) {
			cout << i.first << " " << i.second << " Students\n";
		}
		depart.clear();
	}
	void Search() {
		int id;
		cout << "Enter the ID: ";
		cin >> id;
		if (!search(id))cout << "Student is not found\n";
	}

};

