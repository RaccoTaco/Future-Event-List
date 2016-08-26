#include <iostream>
#include <string>

using namespace std;

struct EventNode
{
	string eventType;
	int time;
	string description;
	EventNode * next;
	EventNode * prev;
};

class FEL {
private:
	EventNode * head;
	int size = 0;
public:
	EventNode * getNext(ofstream &out);
	void insertPriority(string events, int time, string script); //goes by time
	void deleteNode(string events, int time, string script, ofstream &out);
	int length();
	EventNode * peek();
	void print(ofstream &out);
};
