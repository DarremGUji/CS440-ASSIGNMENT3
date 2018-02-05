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

void merge(SortTemp *a, int low,int mid, int high, int size);
void merge_sort(SortTemp *a, int low, int high, int size);
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

Dept *Block_Dept_Read(string filename){
	Dept *temp = new Dept[11];
	Dept *Temp = Read_Dept(filename);
	int i = 0;
	while(i < 11 || Temp[i].did != ""){
		temp[i] = Temp[i];
		if(Temp[i+1].did !="")
			Temp[i] = Temp[i+1];
		i++;
	}
	if(size_dept > 11){
		size_dept -= 11;
		Write_Dept(Temp);
	}
	else
		size_dept = 0;
	return temp;
	
}

Emp *Block_Emp_Read(string filename){
	Emp *temp = new Emp[11];
	Emp *Temp = Read_Emp(filename);
	int i = 0;
	while(i < 11 || Temp[i].ename != ""){
		temp[i] = Temp[i];
		if(Temp[i+1].ename!= "")
			Temp[i] = Temp[i+1];
		i++;
	}
	if(size_emp > 11){
		size_emp -= 11;
		Write_Emp(Temp);
	}
	else
		size_emp = 0;
	
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
		newfile.open("DeptTest.csv");
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
		merge_sort(Temp1, 0, 30, 31);
		for(int i = 0; i <31; i++){
			int item = Temp1[i].sortid;
			cout << item << endl;
			dept[i] = temp1[item];
		}
	}
	
	else if(type == "emp"){
		SortTemp Temp2[51];
		for(int i=0;i < 51; i++){
			Temp2[i].itemid = emp[i].eid;
			Temp2[i].sortid = i;
		}
		merge_sort(Temp2, 0, 50, 51);
		Emp *temp2 = emp;
		for(int i = 0; i < 51; i++){
			emp[i] = temp2[Temp2[i].sortid];
		}
	}
}

int main(){
	ReadFile("department.csv", "dept");
	SortFunc("dept");
	WriteFile("dept");
	
	return 0;
}

void merge_sort(SortTemp a[], int low, int high, int size)
{
    int mid = 0;

    if(low == high)
    {
        return;
    }
    else
    {
        mid = (low + high) / 2;

        merge_sort(a, low, mid, size);

        merge_sort(a, mid + 1, high, size);

        merge(a, low, mid, high, size);
    }
}// end merge_sort()

void merge(SortTemp a[], int low, int mid, int high, int size)
{
    int i;
    int left_index = low;
    int right_index = mid + 1;
    int combined_index = low;
    SortTemp tempA[size];

    while(left_index <= mid && right_index <= high)
    {
        if(a[left_index].itemid <= a[right_index].itemid)
        {
            tempA[combined_index++] = a[left_index++];
        }
        else
        {
            tempA[combined_index++] = a[right_index++];
        }
    }

    if(left_index == mid + 1)
    {
        while(right_index <= high)
        {
            tempA[combined_index++] = a[right_index++];
        }
    }
    else
    {
        while(left_index <= mid)
        {
            tempA[combined_index++] = a[left_index++];
        }
    }

    for(i = low; i <= high; i++)
    {
        a[i] = tempA[i];
    }
}// end merge() 