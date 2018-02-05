/*
CS440 Assignment-3
Query Processing
by Xiaoyi Yang
*/
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;



struct Dept {
	string did;
	string dname;
	string budget;
	int managerid;
};

struct Emp {
	int eid;
	string ename;
	string age;
	string salary;
};

struct SortTemp {
	int itemid;
	int sortid;
};

void Merge(SortTemp *a, int low, int high, int mid);
void MergeSort(SortTemp *a, int low, int high);
Dept dept [31];
Emp emp [51];

template <typename T>
string NumtoStr(T Number){
	ostringstream ss;
	ss << Number;
	return ss.str();
}

string CharDel(string a){
	string temp = "";
	for(int i = 0; i < a.length(); i++){
		if(a[i] != '"')
			temp += a[i];
	}
	return temp;
}

void ReadFile(string filename, string type){
	ifstream file(filename.c_str());
	string id, manid, age;
	string bud, sala;
	string name;
	if(!file.is_open()){
		cout << "Open file failed!" << endl;
		exit(1);
	}
	
	if(type == "dept"){
		int i = 0;
		while(getline(file, id, ',')){
			dept[i].did = CharDel(id);
			
			getline(file, name, ',');
			dept[i].dname = CharDel(name);
			
			getline(file, bud, ',');
			dept[i].budget = CharDel(bud);
			
			getline(file, manid);
			dept[i].managerid = atoi(CharDel(manid).c_str());
			i++;
			if(i == 31)
				break;
		}
	}
	else if(type == "emp"){
		int i = 0;
		while(getline(file, id, ',')){
			emp[i].eid = atoi(CharDel(id).c_str());
			
			getline(file, name, ',');
			emp[i].ename = CharDel(name);
			
			getline(file, age, ',');
			emp[i].age = CharDel(age);
			
			getline(file, sala);
			emp[i].salary = CharDel(sala);
			i++;
			if(i==51)
				break;
		}	
	}
}

void WriteFile(string type){
	ofstream newfile;
	if(type == "dept"){
		newfile.open("Dept.csv");
		for(int i = 0; i < 31; i++){
			string temp = "" + dept[i].did + "," + dept[i].dname + "," + dept[i].budget + "," + NumtoStr(dept[i].managerid) + "\n";
			newfile << temp;
			}
		newfile.close();
	}
	else if(type == "emp"){
		newfile.open("Emp.csv");
		for(int i=0; i < 51; i++){
			string temp = ""+NumtoStr(emp[i].eid) + "," + emp[i].ename + "," + emp[i].age + "," + emp[i].salary + "\n";
			newfile << temp;
		}
		newfile.close();
	}
	else{
		cout << "Error type.";
		exit(1);
	}
	
}

void SortFunc(string type){
	if(type == "dept"){
		SortTemp Temp1[31];
		Dept temp1[31];
		for(int i=0;i < 31; i++){
			Temp1[i].itemid = dept[i].managerid;
			Temp1[i].sortid = i;
			temp1[i] = dept[i];
		}
		MergeSort(Temp1, 0, 30);

		for(int i = 0; i <31; i++){
			dept[i] = temp1[Temp1[i].sortid];
		}
	}
	
	else if(type == "emp"){
		SortTemp Temp2[51];
		Emp temp2[51];
		for(int i=0;i < 51; i++){
			Temp2[i].itemid = emp[i].eid;
			Temp2[i].sortid = i;
			temp2[i] = emp[i];
		}
		MergeSort(Temp2, 0, 50);
		
		for(int i = 0; i < 51; i++){
			emp[i] = temp2[Temp2[i].sortid];
		}
	}
}

int main(){
	ReadFile("department.csv", "dept");
	ReadFile("employee.csv","emp");
	SortFunc("dept");
	SortFunc("emp");
	WriteFile("dept");
	WriteFile("emp");
	
	return 0;
}

void Merge(SortTemp *a, int low, int high, int mid){
	
	// We have low to mid and mid+1 to high already sorted.
	int i, j, k;
	SortTemp temp[high-low+1];
	i = low;
	k = 0;
	j = mid + 1;
	
 
	// Merge the two parts into temp[].
	while (i <= mid && j <= high)
	{
		if (a[i].itemid < a[j].itemid)
		{
			temp[k] = a[i];
			k++;
			i++;
		}
		else
		{
			temp[k] = a[j];
			k++;
			j++;
		}
	}
 
	// Insert all the remaining values from i to mid into temp[].
	while (i <= mid)
	{
		temp[k] = a[i];
		k++;
		i++;
	}
 
	// Insert all the remaining values from j to high into temp[].
	while (j <= high)
	{
		temp[k] = a[j];
		k++;
		j++;
	}
 
 
	// Assign sorted data stored in temp[] to a[].
	for (i = low; i <= high; i++)
	{
		a[i] = temp[i-low];
	}
}

void MergeSort(SortTemp *a, int low, int high){
	int mid;
	if (low < high)
	{
		mid=(low+high)/2;
		// Split the data into two half.
		MergeSort(a, low, mid);
		MergeSort(a, mid+1, high);
 
		// Merge them to get sorted output.
		Merge(a, low, high, mid);
	}
}

