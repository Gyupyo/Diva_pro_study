#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
int main()
{
	ifstream data;
	ofstream out;

	string data_str, word_str, comp;
	data.open("SQuAD 한국어 QA dataset(위키피디아, 표준태깅, 339개).txt");
	
	vector<string> line, word;
	vector<string>::iterator line_it, word_it;

	while(!data.is_open())
	{
		cout << "Fail to open data.txt" << endl;
		return -1;
	}
	
	while (getline(data, data_str))
	{
		word.push_back(data_str.substr(0, data_str.find(" ")));
	}
	
	for (word_it = word.begin(); word_it != word.end();word_it++)
		cout << *word_it << endl;

	data.close();
	out.close();
	system("pause");
	return 0;
}