#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#pragma warning(disable: 4996)

using namespace std;

int main()
{
	clock_t p_start, p_end, m_start, m_end;
	int times = 10;
	ifstream data;
	ifstream answer;
	ofstream out;

	string data_str, data_ch,
		ans_str, ans_ch, ans_label;

	string label_in[] = { "시간", "장소", "기타", "고유명일반" };
	string label_out[] = { "TM", "LC", "O", "GI" };
	int label_size = 4;

	double p_max = 0, p_min = 0, p_avr = 0,
			m_max = 0, m_min = 0, m_avr = 0;
	int dock = 0;
	bool found = 0;

	for (int i = 0;i < times;i++)
	{
		cout << i + 1 << " stage" << endl;
	
		p_start = clock();

		data.open("data.txt");
		answer.open("answer.txt");
		out.open("out.txt");

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

		m_start = clock();

		while (getline(data, data_str)) 
		{
			data_ch = data_str.substr(0, data_str.find(" "));
		
			found = 0;
			while (getline(answer, ans_str))
			{
				ans_ch = ans_str.substr(0, dock = ans_str.find(" "));
			
				if (!data_ch.compare(ans_ch))
				{
					found = 1;
					ans_label = ans_str.substr(dock + 1);

					for (int i = 0;i < label_size;i++)
						if (ans_label == label_in[i])
							out << data_ch << " " << label_out[i] << endl;

					break;
				}
			}

			if (!found)
				out << data_ch << " O"  << endl;

			answer.clear();
			answer.seekg(0, ios::beg);
		}
		m_end = clock();
		cout << "DONE, CHECK out.txt" << endl;
	
		answer.close();
		data.close();
		out.close();

		p_end = clock();

		if (i == 0)
		{
			p_max = (double)(p_end - p_start);
			p_min = (double)(p_end - p_start);
			p_avr += (double)(p_end - p_start);
			m_max = (double)(m_end - m_start);
			m_min = (double)(m_end - m_start); 
			m_avr += (double)(m_end - m_start);
		}
		else
		{
			p_max = p_max > (double)(p_end - p_start) ? p_max : (double)(p_end - p_start);
			p_min = p_min < (double)(p_end - p_start) ? p_min : (double)(p_end - p_start);
			p_avr += (double)(p_end - p_start);

			m_max = m_max > (double)(m_end - m_start) ? m_max : (double)(m_end - m_start);
			m_min = m_min < (double)(m_end - m_start) ? m_min : (double)(m_end - m_start);
			m_avr += (double)(m_end - m_start);

		}
	}

	p_avr /= times;
	m_avr /= times;

	cout << "Run " << times << " times" << endl;
	cout << "Program\n \tMAX : " << p_max << "ms" << ", min : " << p_min <<"ms"<< endl;
	cout << "Matching\n \tMAX : " << m_max << "ms" << ", min : " << m_min << "ms" << endl;
	cout << "Average\n \tprogram : " << p_avr << "ms" << ", matching : " << m_avr << "ms" << endl;

	system("pause");
	return 0;
}