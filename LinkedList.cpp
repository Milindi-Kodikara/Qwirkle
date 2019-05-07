#include <iostream>
#include "LinkedList.h"

LinkedList::LinkedList() 
{
	head = nullptr;
	tail = nullptr;
	size = 0;
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
	tail->next = temp;
	tail = tail->next;
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
	}
	return tempTile;
}

Tile* LinkedList::find(std::string tileLabel)
{
    Node* current = head;
    Tile* tilePtr = nullptr;
    bool found = false;

    //checks if the first node contains the tile label
    if (current->tile->label != tileLabel)
    {
        while (head != nullptr && !found)
        {
            current = current->next;
            if (current->tile->label == tileLabel)
            {
                tilePtr = current->tile;
                found = true;
            }
        }
    }
    else
    {
        tilePtr = current->tile;
    }
    return tilePtr;
}

void LinkedList::remove(Tile* tile)
{
	Node* current = head;
	Node* previous = nullptr;

	while (current != nullptr && !found)
	{		
		if (current->tile == tile)
		{
			if (current == head)
			{
				head = head->next;
				delete current;
			}
			else 
			{
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

void LinkedList::display()
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

	std::cout << output << std::endl;
}
