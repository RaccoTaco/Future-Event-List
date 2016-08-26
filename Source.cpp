#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "FEL.h"

using namespace std;

vector<string> split(string);

int main()
{
	string line;
	vector<string> words; //type = 0, event = 1, time = 2, script = 3;
	int time;

	ifstream infile;
	infile.open("infile.txt");

	ofstream out;
	out.open("outfile.txt");

	FEL EL;

	while (!infile.eof())
	{
		getline(infile, line);
		words = split(line);

		out << "----------------------------------------" << endl;
		out << "Event: " << words[0] << endl;

		if (words[0] == "insert with priority")
		{
			words[1].erase(0, 1);
			words[2].erase(0, 1);
			words[3].erase(0, 1);

			time = atoi(words[2].c_str());
			EL.insertPriority(words[1], time, words[3]);
			out << "Added: " << words[3] << endl;
		}
		else if (words[0] == "delete")
		{
			words[1].erase(0, 1);
			words[2].erase(0, 1);
			words[3].erase(0, 1);

			time = atoi(words[2].c_str());
			EL.deleteNode(words[1], time, words[3], out);
			out << "Deleted: " << words[3] << endl;
		}
		else if (words[0] == "get next")
		{
			EventNode *next = EL.getNext(out);
			out << "Next Event Removed: " << next->description << endl;
		}
		else if (words[0] == "length")
		{
			out << "Length of Event List: " << EL.length() << endl;
		}
		else if (words[0] == "peek")
		{
			EventNode *head = EL.peek();
			out << "Next Event: " << head->description << endl;
		}
		else
		{
			out << "Error in system. Stopping program." << endl;
			system("pause");
			return 1;
		}
		EL.print(out);
	}

	infile.close();
	out.close();
	system("pause");
	return 0;
}

vector<string> split(string line)
{
	vector<string> words;
	string word;

	stringstream stream(line);
	while (getline(stream, word, ','))
		words.push_back(word);

	return words;
}