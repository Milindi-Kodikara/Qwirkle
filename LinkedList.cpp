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
	if (head == nullptr)
	{
		head = temp;
		tail = temp;
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
	}
	return tempTile;
}

Tile* LinkedList::find(std::string tileLabel)
{
    Node* current = head;
    Tile* tilePtr = nullptr;
    bool found = false;

	while (current != nullptr && !found)
	{
		current = current->next;
		if (current->tile->label == tileLabel)
		{
			tilePtr = current->tile;
			found = true;
		}
	}
	return tilePtr;
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

Tile* LinkedList::removeAt(int index)
{
    Node* current = head;
    Tile* tile = nullptr;

    if (index == 0)
    {
        head = head->next;
        tile = head->tile;
        delete current;
    }

    else
    {
        for (int i = 0; i < index - 1; ++i)
        {
            current = current ->next
        }

        if (current != nullptr)
        {
            if (current->next != nullptr)
            {
                Node* previous = current->next;
                current->next = current->next->next;
                tile = previous->tile;
                delete previous;
            }
        }
    }
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
