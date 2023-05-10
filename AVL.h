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
	bool isexist(int sid) {
		student* curr = root;
		while (curr != NULL) {
			if (curr->id == sid) {
				cout << "Student is already exist Duplication is Not Allowed\n";
				return true;
			}
			else if (curr->id > sid) curr = curr->before;
			else curr = curr->after;
		}
		return false;
	}
	student* deleteNode(student* root, int key) {
		if (root == NULL)
			return root;

		if (key < root->id)
			root->before = deleteNode(root->before, key);
		else if (key > root->id)
			root->after = deleteNode(root->after, key);
		else {
			if ((root->before == NULL) || (root->after == NULL)) {
				// ternery if 
				student* temp = root->before ? root->before : root->after;

				if (temp == NULL) {
					temp = root;
					root = NULL;
				}
				else
					*root = *temp;

				free(temp);
			}
			else {
				student* temp = root->after;

				while (temp->before != NULL)
					temp = temp->before;

				root->id = temp->id;
				root->gpa = temp->gpa;
				root->name = temp->name;
				root->department = temp->department;
				root->after = deleteNode(root->after, temp->id);
			}
		}

		if (root == NULL)
			return root;

		root->height = 1 + max(height(root->before), height(root->after));

		int balance = getBalance(root);

		if (balance > 1 && getBalance(root->before) >= 0)
			return rightRotate(root);

		if (balance > 1 && getBalance(root->before) < 0) {
			root->before = leftRotate(root->before);
			return rightRotate(root);
		}

		if (balance < -1 && getBalance(root->after) <= 0)
			return leftRotate(root);

		if (balance < -1 && getBalance(root->after) > 0) {
			root->after = rightRotate(root->after);
			return leftRotate(root);
		}

		return root;
	}
public :
	void EnterData() {
		char sname[1000];
		string sdepartment;
		int sid;
		double sgpa;
		cout << "Enter your ID : ";
		cin >> sid;
		while (isexist(sid)) {
			cout << "Enter another ID : ";
			cin >> sid;
		}
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
		while (!(sgpa > 0 && sgpa <= 4)) {
			cout << "invalid GPA , Enter correct GPA\n";
			cin >> sgpa;
		}
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
	void RemoveStudent() {
		int id;
		cout << "Enter the ID: ";
		cin >> id;
		if (!search(id))cout << "Student is not found\n";
		else {
			root=deleteNode(root, id);
			cout << "Student is deleted \n";
		}
	}
	void Search() {
		int id;
		cout << "Enter the ID: ";
		cin >> id;
		if (!search(id))cout << "Student is not found\n";
	}

};

