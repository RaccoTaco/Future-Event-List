#include <iostream>
#include <fstream>
#include "FEL.h"

using namespace std;

EventNode * FEL::getNext(ofstream &out)
{
	EventNode * temp;
	temp = head;

	EventNode * ret = new EventNode;
	ret->description = "NULL";
	ret->time = 0;
	ret->eventType = "NULL";

	if (size == 0)
	{
		out << "Error - Nothing in event list!";
		return ret;
	}

	ret->description = head->description;
	ret->time = head->time;
	ret->eventType = head->eventType;

	if (size == 1)
	{
		delete head;
		size--;
	}
	else
	{
		head = temp->next;
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		delete temp;
		size--;
	}
	return ret;
}

void FEL::insertPriority(string events, int time, string script)
{
	EventNode * n = new EventNode;
	n->eventType = events;
	n->time = time;
	n->description = script;

	EventNode * temp = new EventNode;
	temp = head;

	if (!head)
	{
		head = n;
		n->next = n;
		n->prev = n;
	}
	else if (size == 1)
	{
		n->next = head;
		n->prev = head;
		temp->next = n;
		temp->prev = n;

		if (temp->time < n->time)
			head = temp;
		else
			head = n;
	}
	else
	{
		if (n->time < temp->time)
			head = n;

		while (temp->time < n->time && temp->next != head)
			temp = temp->next;

		if (temp->next == head && temp->time < n->time)
			temp = temp->next;

		n->next = temp;
		temp->prev->next = n;
		n->prev = temp->prev;
		temp->prev = n;
	}
	size++;
}

void FEL::deleteNode(string event, int time, string script, ofstream &out)
{
	EventNode * temp = new EventNode;
	temp = head;

	while (temp->time < time)
		temp = temp->next;

	while (temp->time == time)
	{
		if (temp->eventType.compare(event)==0 && temp->description.compare(script)==0)
		{
			if (head == temp)
				head = temp->next;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
			size--;
		}
		else
			temp = temp->next;
	}

	if (temp->time > time)
		out << "Error - Event wanting to delete does not exist!\n" << event << " " << time << " " << script << endl;
}

int FEL::length()
{
	return size;
}

EventNode *FEL::peek()
{
	return head;
}

void FEL::print(ofstream &out)
{
	EventNode * curr = new EventNode;
	curr = head;
	out << "Currently in List: ";
	for (int i = 0; i < size; i++)
	{
		if (i > 0)
			out << " || ";
		out << curr->description;
		curr = curr->next;
	}
	out << endl;
}