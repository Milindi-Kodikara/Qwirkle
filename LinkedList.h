#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

	LinkedList();
	~LinkedList();

	// Adds the supplied tile to the back of the list
	void add_back(Tile* tile);

	// Removes the tile at the start of the list and returns it
	Tile* pop_front();

	// Removes the specified tile from the list
	void remove(Tile* tile);

private:
    Node* head;
    Node* tail;
    int size;
};

struct InvalidPopException {};
struct TileNotFoundException {};

#endif // ASSIGN2_LINKEDLIST_H
