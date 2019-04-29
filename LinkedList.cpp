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
	//TODO
}

// Removes the tile at the start of the list and returns it
Tile* LinkedList::pop_front()
{
	Node *tempNode = head;
	if (tempNode != nullptr) {
		Tile *tempTile = head->tile;
		head = head->next;
		delete tempNode;
		return tempTile;
	}
	else {
		return nullptr;
	}
}

// Removes the specified tile from the list
void LinkedList::remove(Tile* tile)
{
	//TODO
}
