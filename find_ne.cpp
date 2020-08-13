#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <map>
#pragma warning(disable: 4996)

using namespace std;

int main()
{
	string file_name = "E2017.Wiki.001";

	ifstream data;
	ofstream out;

	string data_str, text_str, type_str;
	string::size_type morp, ne, find_end;

	vector<string> text;
	vector<string> type_a, type_b;
	
	vector<string>::iterator it;

	int type_num = 0;
	bool found_morp = 0, found_ne = 0, flag=0;
	
	data.open(file_name+".txt");
	out.open(file_name + "______OUT.txt");

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

		for (it = text.begin(); it != text.end(); it++)
		{
			if (*it == *type_a.begin() && !type_b.empty())
			{
				out << *it << " " << *type_b.begin() << endl;
			
			
				type_a.erase(type_a.begin());
				type_b.erase(type_b.begin());
			
				if (type_a.empty())
					type_a.push_back("DONE!");
			}
			else
				out << *it << " O" << endl;
		}
		out << "\n" << endl;
		type_a.clear();
		type_b.clear();
	}
	cout << "DONE, CHECK out.txt" << endl;

	data.close();
	out.close();
	system("pause");
	return 0;
}