#pragma once
#include<bits/stdc++.h>
using namespace std;
class MaxHeap
{
	struct student {
		int id;
		string name;
		double gpa;
		string department;
		student(int d, string n, double g, string de) {
			id = d;
			name = n;
			gpa = g;
			department = de;
		}
	};
	vector<student*>vec;
	void heapify(vector<student*>& vec, int n, int i) {  // o(nlog n)
		int l = 2 * i + 1;
		int r = 2 * i + 2;
		int mingpa = i;
		if (l < n && vec[l]->gpa < vec[mingpa]->gpa)mingpa = l;
		if (r<n && vec[r]->gpa<vec[mingpa]->gpa)mingpa = r;
		if (mingpa != i) {
			swap(vec[i], vec[mingpa]);
			heapify(vec, n, mingpa);
		}
	}
	void heapbuild(vector<student*>& vec, int n) { // o(n)
		for (int i = n / 2 - 1; i >= 0; i--)
			heapify(vec, n, i);
	}
	void heapSort(vector<student*>& vec, int n) { //o(nlogn) // space o(1)
		n = vec.size();
		heapbuild(vec, n);
		for (int i = n - 1; i >= 0; i--) {
			swap(vec[0], vec[i]);
			heapify(vec, i, 0);
		}
	}
public:
	void insert(int d, string na, double g, string depart) {
		student* s = new student(d, na, g, depart);
		vec.push_back(s);

	}
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
		cin.getline(sname, 1000, '\n');
		cout << "Enter your GPA : ";
		cin >> sgpa;
		cout << "Enter your Department : ";
		cin >> sdepartment;
		insert(sid, sname, sgpa, sdepartment);
		cout << "The student is added\n";

	}
	void PrintAllStudents() {
		heapSort(vec, vec.size());
		for (auto i : vec) {
			cout << "[" << i->id << " " << i->name << " " << i->gpa << " " << i->department << "]" << "\n";
		}
	}
};

