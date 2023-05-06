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
	void inorder(student* root)
	{
		if (root != NULL) {
			inorder(root->before);
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
		insert(sid, sname, sgpa, sdepartment);
		/*ofstream WriteFile("input.txt",ios::app);
		WriteFile <<sid;
		WriteFile << "\n" << sname;
		WriteFile << "\n" << sgpa;
		WriteFile << "\n" << sdepartment;*/
		cout << "The student is added.\n";

	}
	void RemoveStudent() {
		int id;
		cout << "Enter your ID : ";
		cin >> id;
		if (search(id)) {
			// remove from tree
			
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
	}
	void insert(int id, string name, double gpa, string department) {
		student* newnode = new student(id, name, gpa, department);
		newnode->before = NULL, newnode->after = NULL;
		if (root == NULL)root = newnode;
		else {
			student* curr = root;
			student* prevcurr = new student();
			while (curr != NULL) {
				prevcurr = curr;
				if (curr->id == id) {
					cout << "this Student id  is already exisit duplicates id not allowed \n";
					return;
				}
				else {
					if (curr->id > id)curr = curr->before;
					else curr = curr->after;
				}
			}
			if (prevcurr->id > id)prevcurr->before = newnode;
			else prevcurr->after = newnode;
		}
	}

};

