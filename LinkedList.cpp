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
	Node* temp = new Node(tile, nullptr);
	tail->next = temp;
	tail = tail->next;
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

// Searches through the list for the tile with the specified
// tileLabel, returning it if it is found and returning nullptr
// if it isn't
Tile* LinkedList::find(std::string tileLabel)
{
	    Node* current = head;
	    Tile* tilePtr = nullptr;
	    bool found = false;

	    if (current->tile->label != tileLabel)
	    {
            while (head != nullptr && found == false)
            {
                current = current->next;
                if (current->tile->label == tileLabel)
                {
                    tilePtr = current->tile;
                    found = true;
                }
            }
        }
	    if (current->tile->label == tileLabel)
        {
	        tilePtr = current->tile;
        }
	    return tilePtr;
}


/* Removes the specified tile from the list and returns true if
 * the tile was successfully removed*/
bool LinkedList::remove(Tile* tile)
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
	return found;
}

//Output all Tiles inside linked list
void LinkedList::display()
{
	node* temp = new node;
	temp = head;
	std::string output = "";
	
	while (temp != NULL)
	{
		output += temp->tile->label + ",";
		temp = temp->next;
	}
	output.pop_back();

	printf("%s", output);
}
