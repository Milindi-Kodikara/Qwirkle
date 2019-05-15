#include <iostream>
#include "LinkedList.h"

LinkedList::LinkedList() 
{
	head = nullptr;
	tail = nullptr;
	empty = true;
}

LinkedList::~LinkedList() 
{
	Node* curr = head;
	Node* prev;
	while (curr != nullptr)
	{
		prev = curr;
		curr = curr->next;
		delete prev;
	}
}

void LinkedList::add_back(Tile* tile)
{
	Node* temp = new Node(tile, nullptr);
	if (head == nullptr)
	{
		head = temp;
		tail = temp;
		empty = false;
	}
	else
	{
		tail->next = temp;
		tail = temp;
	}
}

Tile* LinkedList::pop_front()
{
	Tile* tempTile = nullptr;
	if (head != nullptr)
	{
		Node* tempNode = head;
		tempTile = head->tile;
		head = head->next;
		delete tempNode;
		if (head == nullptr) empty = true;
	}
	return tempTile;
}

Tile* LinkedList::find(std::string tileLabel)
{
    Node* current = head;
    Tile* tile = nullptr;
    bool found = false;

	while (current != nullptr && !found)
	{
		if (current->tile->label == tileLabel)
		{
			tile = current->tile;
			found = true;
		}
		current = current->next;
	}
	return tile;
}

void LinkedList::remove(Tile* tile)
{
	Node* current = head;
	Node* previous = nullptr;

	while (current != nullptr)
	{		
		if (current->tile == tile)
		{
			if (current == head)
			{
				head = head->next;
				delete current;
				if (head == nullptr) empty = true;
			}
			else 
			{
				if (current == tail) tail = previous;
				previous->next = current->next;
				delete current;
			}
		}
		else 
		{
			previous = current;
			current = previous->next;
		}
	}
}

Tile* LinkedList::removeAt(int index)
{
    Node* current = head;
    Node* previous = nullptr;
    Tile* tile = nullptr;

    for (int i = 0; i < index; i++)
    {
        previous = current;
        current = current->next;
    }

    tile = current->tile;
	if (previous == nullptr)
	{
		head = current->next;
		if (head == nullptr) empty = true;
	}
    else previous->next = current->next;

	delete current;
    return tile;
}

std::string LinkedList::display()
{
	Node* temp = nullptr;
	temp = head;
	std::string output = "";
	
	while (temp != nullptr)
	{
		output += temp->tile->label + ",";
		temp = temp->next;
	}
	output.pop_back();

	return output;
}

std::vector<Tile*> LinkedList::toVector()
{
	std::vector<Tile*> temp;
	Node* current = head;
	while (current != nullptr)
	{
		temp.push_back(current->tile);
	}
	return temp;
}

bool LinkedList::isEmpty()
{
	return empty;
}
