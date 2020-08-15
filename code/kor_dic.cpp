#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#pragma warning(disable: 4996)

using namespace std;

///////////////////////////////////////////////////////////////////////
// File Name : compare.cpp										     //
// Date: 2020/08/15												     //
// Os: Windows 10												     //
// Author: Shin Gyu Pyo						 					     //
///////////////////////////////////////////////////////////////////////
int main()
{
	ifstream data_1, data_2;
	ofstream out;

	string DATA_FILE_1 = "animal_1", DATA_FILE_2 = "animal_2";

	string data_1_str, data_2_str, label = "AM";

	data_1.open(DATA_FILE_1 + ".txt");
	data_2.open(DATA_FILE_2 + ".txt");
	out.open(DATA_FILE_1 +"__KOR_OUT.txt");

	if (!data_1.is_open())
	{
		cout << "Fail to open answer.txt" << endl;
		return -1;
	}

	if (!data_2.is_open())
	{
		cout << "Fail to open data.txt" << endl;
		return -1;
	}

	while (getline(data_1, data_1_str))
	{
		if (data_1_str != "#00")
			continue;

		getline(data_1, data_1_str);

		data_1_str.erase(find(data_1_str.begin(), data_1_str.end(), '-'));
		
		out << data_1_str << " " << label << endl;
	}

	while (getline(data_2, data_2_str))
	{
		if (data_2_str != "#00")
			continue;

		getline(data_2, data_2_str);

		data_2_str.erase(find(data_2_str.begin(), data_2_str.end(), '-'));

		out << data_2_str << " " << label << endl;
	}
	cout << "DONE, CHECK out.txt" << endl;

	data_1.close();
	data_2.close();
	out.close();

	system("pause");
	return 0;
}