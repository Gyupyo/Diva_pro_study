#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

///////////////////////////////////////////////////////////////////////
// File Name : compare.cpp										     //
// Date: 2020/08/15												     //
// Os: Windows 10												     //
// Author: Shin Gyu Pyo						 					     //
///////////////////////////////////////////////////////////////////////

int main()
{
	string DATA_FILE = "단문질문 QA dataset",
		ANSWER_FILE = "세분류_수정";

	ifstream data, answer;
	ofstream out;

	string data_str, answer_str, word, ner;
	
	vector<string> answer_vec;
	vector<string>::iterator answer_it;
	map<string, string> result;
	map<string, string>::iterator result_it;
	int dock;
	
	data.open(DATA_FILE + ".txt");
	answer.open(ANSWER_FILE + ".txt");
	out.open(DATA_FILE + "__LAP__OUT.txt");

	while(!data.is_open())
	{
		cout << "Fail to open data.txt" << endl;
		return -1;
	}

	while (!answer.is_open())
	{
		cout << "Fail to open answer.txt" << endl;
		return -1;
	}

	while (getline(answer, answer_str))
		answer_vec.push_back(answer_str);
	
	while (getline(data, data_str))
	{
		for (answer_it = answer_vec.begin(); answer_it != answer_vec.end(); answer_it++)
			if ( data_str.find(*answer_it) != string::npos)
			{
				dock = data_str.find(*answer_it);
				break;
			}

		word = data_str.substr(0, dock-1);
		ner = data_str.substr(dock);
		
		result.insert(make_pair(word, ner));
	}

	for (result_it = result.begin(); result_it != result.end();result_it++)
		out << result_it->first << " " << result_it->second << endl;

	cout << "DONE, CHECK out.txt" << endl;

	data.close();
	out.close();
	system("pause");
	return 0;
}