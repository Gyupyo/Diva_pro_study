#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <queue>
#pragma warning(disable: 4996)

///////////////////////////////////////////////////////////////////////
// File Name : compare.cpp										     //
// Date: 2020/08/15												     //
// Os: Windows 10												     //
// Author: Shin Gyu Pyo						 					     //
///////////////////////////////////////////////////////////////////////
using namespace std;

int main()
{
	string file_name = "E2017.Wiki.001";

	ifstream data;
	ofstream out;

	string data_str, text_str, type_str;
	string::size_type morp, ne, find_end;

	vector<string> text, type_a, type_b;
	
	vector<string>::iterator text_it, a_it, b_it;

	bool flag = 0, match = 0;
	
	data.open(file_name+".txt");
	out.open(file_name + "__NE__OUT.txt");

	if (!data.is_open())
	{
		cout << "Fail to open data.txt" << endl;
		return -1;
	}

	while (getline(data, data_str))
	{
		flag = 0;
		while (getline(data, data_str))
		{
			morp = data_str.find("\"morp\"");

			if (morp != string::npos)
			{
				flag = 1;
				break;
			}
		}
		if (!flag)
			break;

		while (getline(data, data_str))
		{
			find_end = data_str.find("],");

			if (find_end != string::npos)
				break;
	
			// morp 시작
			text_str = data_str.substr(data_str.find("\"lemma\"") + 10);
			text_str = text_str.substr(0, text_str.find("\""));
			
			text.push_back(text_str);
		}
	
		while (getline(data, data_str))
		{
			ne = data_str.find("\"NE\"");

			if (ne != string::npos)
				break;
		}
	
		while (getline(data, data_str))
		{
			find_end = data_str.find("],");

			if (find_end != string::npos)
				break;

			// type 시작
			text_str = data_str.substr(data_str.find("\"text\"") + 9);
			text_str = text_str.substr(0, text_str.find("\""));
			type_a.push_back(text_str);
		
			type_str = data_str.substr(data_str.find("\"type\"") + 9);
			type_str = type_str.substr(0, type_str.find("\""));
			type_b.push_back(type_str);
		}
		
			// 매칭 시작
		for (text_it = text.begin(); text_it != text.end(); text_it++)
		{
			match = 0;
			for (a_it = type_a.begin(), b_it = type_b.begin(); a_it != type_a.end(); a_it++, b_it++)
				if (*text_it == *a_it)
				{
					match = 1;
					break;
				}

			if (match)
				out << *text_it << " " << *b_it << endl;
			else
				out << *text_it << " O" << endl;
		}

		out << endl;

		text.clear();
		system("pause");
	}
	cout << "DONE, CHECK out.txt" << endl;

	data.close();
	out.close();
	system("pause");
	return 0;
}