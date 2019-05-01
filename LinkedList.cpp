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

// Adds the supplied tile to the back of the list
void LinkedList::add_back(Tile* tile)
{
		if (tile != nullptr)
		{
			Node* temp = new Node(tile, nullptr);
			if (head != nullptr)
			{
				tail->next = temp;
				tail = tail->next;
			}
		}
}

// Removes the tile at the start of the list and returns it
// Returns nullptr if the list is empty
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

// Removes the specified tile from the list
void LinkedList::remove(Tile* tile)
{
	Node* current = head;
	Node* previous = nullptr;
	bool found = false;

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
			found = true;
		}
		else 
		{
			previous = current;
			current = previous->next;
		}
	}
}
