#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <algorithm>

using namespace std;
namespace fs = std::experimental::filesystem::v1;

int main()
{
	string folder_name = "UCORPUS";
	string path_str;
	fstream data;
	ofstream out_text, out_ne;
	string line;

	out_text.open("UCORPUS_TEXT.txt");
	out_ne.open("UCORPUS_NE.txt");


	fs::directory_iterator itr(fs::current_path() / folder_name);
	while (itr != fs::end(itr))
	{
		const fs::directory_entry& entry = *itr;
		path_str = entry.path().string();
		path_str = path_str.substr(path_str.find(folder_name) + folder_name.length() + 1);
		
		data.open(folder_name+"/"+path_str);

		if (!data.is_open())
		{
			cout << "Fail to open " << path_str << endl;
			return -1;
		}

		while (getline(data, line))
		{
			out_text << line << endl;

			while (getline(data, line))
				if (line[0] == '@')
					break;

			while (getline(data, line))
			{
				if (line == "")
					break;
															// "1-1 1-1 ¿¥¸¶´©¿¤	PS"
				line = line.substr(line.find(" ") + 1);		// "1-1 ¿¥¸¶´©¿¤	PS"
				line = line.substr(line.find(" ") + 1);		// "¿¥¸¶´©¿¤	PS"

				out_ne << line << endl;
			}
			out_ne << endl;
			// skip a line ("")
			getline(data, line);
		}
		

		cout << path_str << " done." << endl;
		data.close();
		itr++;
	}

	out_text.close();
	out_ne.close();
	cout << "Check UCORPUS_TEXT.txt & UCORPUS_NE.txt" << endl;

	system("pause");
	return 0;
}
