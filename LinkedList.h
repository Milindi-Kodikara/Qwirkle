#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include <vector>
#include "Node.h"

class LinkedList {
public:

	LinkedList();
	~LinkedList();

	// Adds the supplied tile to the back of the list
	void add_back(Tile* tile);

	// Removes the tile at the start of the list and returns it
	// Returns nullptr if the list is empty
	Tile* pop_front();

	// Searches through the list for the tile with the specified
	// tileLabel, returning it if it is found and returning nullptr
	// if it isn't
	Tile* find(std::string tileLabel);

	// Removes the specified tile from the list
	void remove(Tile* tile);

	// Removes a tile from given index
    Tile* removeAt(int index);

	// Outputs all Tiles inside linked list
	std::string display();
 
	std::vector<Tile*> toVector();

	bool isEmpty();

private:
    Node* head;
    Node* tail;
    bool empty;
};

struct InvalidPopException {};


#endif // ASSIGN2_LINKEDLIST_H
