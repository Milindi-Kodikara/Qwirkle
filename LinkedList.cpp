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

// the logic and indentation need to be cleaned up here, I'll talk more about it in the tut
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

// line 101 is incorrect syntax and logic, you do not want to create a new Node here
// you should be comparing against nullptr rather than NULL
// printf is uneeded here, cout is fine
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
