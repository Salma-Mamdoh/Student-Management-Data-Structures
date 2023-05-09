#pragma once
#include<bits/stdc++.h>
using namespace std;

class BST
{
	struct student {
		int id;
		string name;
		double gpa;
		string department;
		student* before;
		student* after;
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
	void inorder(student* root)
	{
		if (root != NULL) {
			inorder(root->before);
			depart[root->department]++;
			cout << "[" << root->id << " " << root->name << " " << root->gpa << " " << root->department << "]" << "\n";
			inorder(root->after);
		}
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
	void deletestudent(student*& node) {
		if (node == NULL) return;

		if (node->before == NULL && node->after == NULL) {
			delete node;
			node = NULL;
		}
		else if (node->before == NULL) {
			student* temp = node;
			node = node->after;
			delete temp;
		}
		else if (node->after == NULL) {
			student* temp = node;
			node = node->before;
			delete temp;
		}
		else {
			student* curr = node->after;
			while (curr->before != NULL) {
				curr = curr->before;
			}
			node->id = curr->id;
			node->name = curr->name;
			node->gpa = curr->gpa;
			node->department = curr->department;
			deletestudent(curr);
		}
	}
	
public:
	BST() {};
	void AddStudent() {
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
		cin.getline(sname,1000,'\n');
		cout << "Enter your GPA : ";
		cin >> sgpa;
		cout << "Enter your Department : ";
		cin >> sdepartment;
		while (!insert(sid, sname, sgpa, sdepartment)) {
			cin >> sid;
		}
		cout << "The student is added.\n";

	}
	void RemoveStudent() {
		int id;
		cout << "Enter your ID : ";
		cin >> id;
		if (search(id)) {
			// remove from tree
			student* curr; 
			student* prevcurr;
			// if node is root 
			if (root->id == id)
			{
				deletestudent(root);
				return;
			}
			// if node is not a root 
			prevcurr = root;
			if (root->id > id)
				curr = root->before;
			else
				curr = root->after;

			//get the item that will be deleted 
			while (curr != NULL)
			{
				if (curr->id == id)
					break;
				else
				{
					prevcurr = curr;
					if (curr->id > id)
						curr = curr->before;
					else
						curr = curr->after;
				}
			}
			if (prevcurr->id > id)
				deletestudent(prevcurr->before);
			else
				deletestudent(prevcurr->after);

			cout << "Student is deleted.\n";
		}
		else {
			cout << "Student is Not found\n";
		}
		
	}
	void SearchStudent() {
		int id;
		cout << "Enter your ID : ";
		cin >> id;
		if (!search(id)) cout << "Student is Not found\n";
	}
	void PrintAllSortedByID() {
		inorder(root);
		cout << "Students per Departments:\n";
		for (auto i : depart) {
			cout << i.first << " " << i.second <<" Students\n";
		}
		depart.clear();
	}
	bool insert(int id, string name, double gpa, string department) {
		student* curr; 
		student* prevcurr = new student(); //pointer behind current
		student* newNode=new student(id,name,gpa,department);  
		newNode->before=NULL;
		newNode->after= NULL;

		if (root == NULL)
			root = newNode;
		else
		{
			curr = root;
			while (curr != NULL)
			{
				prevcurr = curr;

				if (curr->id == id)
				{
					cout << "this ID is already exist in the tree , Duplication is Not allowed\n";
					cout << "Enter another ID\n";
					return 0;
				}
				else
					if (curr->id> id)
						curr = curr->before;
					else
						curr = curr->after;
			}//end while

			if (prevcurr->id > id)
				prevcurr->before = newNode;
			else
				prevcurr->after = newNode;
		}

		return 1;
	}


};

