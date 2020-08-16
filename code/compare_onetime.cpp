#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
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

	string DATA_FILE = "train1", ANSWER_FILE = "data__LAP__OUT";
	ifstream data, answer;
	ofstream out;
	string data_str, data_ch, ans_str, ans_ch, ans_label;

	string label_in[] = { "시간", "장소", "기타", "고유명일반" };
	string label_out[] = { "TM", "LC", "O", "GI" };
	int label_size = 4;

	int dock = 0, count = 0;
	bool found = 0;

	

	data.open(DATA_FILE+ ".txt");
	answer.open(ANSWER_FILE + ".txt");
	out.open(DATA_FILE + "__COMP__OUT.txt");

	if (!answer.is_open())
	{
		cout << "Fail to open answer.txt" << endl;
		return -1;
	}

	if (!data.is_open())
	{
		cout << "Fail to open data.txt" << endl;
		return -1;
	}


	while (getline(data, data_str)) 
	{
		if (data_str == "")
		{
			out << endl;
			continue;
		}
		data_ch = data_str.substr(0, data_str.find(" "));
		
		found = 0;
		while (getline(answer, ans_str))
		{
			ans_ch = ans_str.substr(0, dock = ans_str.find(" "));
			
			if (!data_ch.compare(ans_ch))
			{
				found = 1;
				ans_label = ans_str.substr(dock + 1);

				out << data_ch << " " << ans_label << endl;
				count++;
				break;
			}
		}

		if (!found)
			out << data_ch << " O"  << endl;

		answer.clear();
		answer.seekg(0, ios::beg);
	}
	cout << "  " << count << " 개의 단어가 발견되었습니다." << endl;
	cout << "DONE, CHECK out.txt" << endl;
	
	answer.close();
	data.close();
	out.close();


	
	system("pause");
	return 0;
}