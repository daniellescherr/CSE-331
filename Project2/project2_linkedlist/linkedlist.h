//
// Description :  Single linked list
//
#include <iostream>
#include <list>
#include "node.h"

using namespace std;

class LinkedList
{
private:
	Node *head;     // a pointer pints to a head node
	Node *tail;     // a pointer pints to a tail node

public:
	// Constructor: initial value
	LinkedList() {
		// Initial head and tail pointers
		head=NULL;
		tail=NULL;
	}

	// Destructor: deletes everything in the list.
	~LinkedList() {
		Node* node;
		while (head!=NULL) {
			node=head->next;
			delete head;
			head=node;
		}
	}

	bool isEmpty();
	void PushFront(int t);
	void PushBack(int t);
	void PrintNode(Node* n);
	void PrintList();
	void PrintList(Node* startNode);

	Node* FindKthElementFromTail(unsigned int k);
	bool Delete(Node* node);
	void ReverseList();
};

// check if a linked list is empty
bool LinkedList::isEmpty() {
	if (head==NULL) return true;
	else return false;
}
// add a new element at the beginning of a list
void LinkedList::PushFront(int t)
{
	Node* newNode = new Node(t);
	if (isEmpty()) {
		head = newNode;
		tail = newNode;
	} else {
		newNode->next = head;
		head = newNode;
	}
}
// add a new element at the end of a list
void LinkedList::PushBack(int t) 
{
	Node* newNode = new Node(t);
	if (isEmpty()) {
		head = newNode;
		tail = newNode;
	}  else {
		tail->next = newNode;
		tail = newNode;
	}
}
// print the data in a node
void LinkedList::PrintNode(Node* n) 
{
	if (n!=NULL)
		cout << n->payload << endl;
	else
		cout << "NULL" << endl;
}
// print the data in a linked list
void LinkedList::PrintList()  
{
	Node *it = head;
	while (it!=NULL)  
	{
		cout << it->payload << ' ';
		it=it->next;
	}
	cout << endl;
}
// print the data in a linked list from a specific node
void LinkedList::PrintList(Node* startNode)  
{
	Node *it = startNode;
	while (it!=NULL)  
	{
		cout << it->payload << ' ';
		it=it->next;
	}
	cout << endl;
}
// function to reverse a list
void LinkedList::ReverseList()
{
	if ((head == NULL || head->next == NULL))	//if theres nothing in the list or only 1 number
		return;									//nothing needs to be changed
	
	if (head->next == tail)						//if there is only 2 numbers in the list
	{
		Node *temp;								//creates terporary node
		temp = head;							//sets temporary node to the head
		tail->next = head;						//assigns the tail to point to the head
		head->next = NULL;						//assigns the head to point to NULL
		head = tail;							//assigns tail to the head
		tail = temp;			//assigns temp(which was head before it got changed) to the tail
		return;									//done, we don't need to do anything else
	}
	
	Node *previous = head;						//previous node is the head
	Node *current = head->next;					//current node is one after the head
	Node *current_next = current->next;			//current_next is one after current
	previous->next = NULL;						//the head will now point to NULL
	current->next = previous;		//instead of current pointing to next it will point to previous
	tail = previous;							//assigns previous to be the tail
	
	while (current_next != NULL){				//loops until the node points to NULL
		previous = current;						//current is assigned to previous
		current = current_next;					//the node after current is assigned to current
		current_next = current->next;			//changes current_next to one node further
		current->next = previous;				//assigns that node to previous and loops again
	}
	head = current;							//once node points to NULL, assign head to that node
	
	/* hints: we can define this problem as a recursion. 
	   You may create other recursive functions as need.
	*/
}
// function to find the k-th element from the back of a list
Node* LinkedList::FindKthElementFromTail(unsigned int k)
{
	Node *temp = head;							//assigns temporary node to the head
	Node *ptr;									//creates pointer node used to loop through the list
	
	if (k == 1)									//if k is 1, kth element from tail is the tail
		return tail;							//so the tail gets returned
	
	for (ptr = head; ptr != nullptr; ptr = ptr->next)	//uses the pointer starting at the head to
	{												//iterate through the list until nullptr is reached
		temp = ptr;									//assigns the node of pointer to temp
				//moves temp forward K times unless i is greater than K-1 or it would point to NULL
		for (int i = 1; (i < k-1 && temp->next != NULL); i++)
			temp = temp->next;
		if (temp->next == NULL)						//if temp would point to NULL
			return nullptr;							//return nullptr
		if (temp->next == tail)						//if the node after temp is the tail
			return ptr;								//that pointer was k nodes from the end
	}
	return nullptr;
	
	/* hints: there is an algorithm that scan through the linked list only once! 
	   One possibilty is to use two pointers scan a list. I will leave it to you to think about how to used them.
	   Feel free to come up with other algorithm.
	*/
	
}
// function to delete the specific node from a list
bool LinkedList::Delete (Node* node)
{
	Node *temp, *ptr;						//creates temporary and pointer nodes
	temp = head;							//start at the begining
	if (node != NULL)						//as long as the node isn't NULL
		if (node == head)					//if the node is the head
		{
			head = temp->next;				//update head to point to the next node
			delete temp;					//delete temp which was the head
			return true;					//delete worked
		}
		while (temp->next != NULL)			//while the node after temp isn't NULL
		{
			if (temp->next == node)			//if the next node is the one we're deleting
			{
				if (temp->next == tail)		// check if one after is the tail
				{
					temp->next = NULL;		//one after would now point to NULL
					delete node;			//delete the node which is the tail
					tail = temp;			//tail is now that temporary node
					return true;			//delete worked
				}
				else						//its not the head or tail
				{
					ptr = temp->next;		//pointer is the node after temp
					temp->next = ptr->next;	//temp points to what ptr pointed to
					delete ptr;				//delete ptr
					return true;			//delete worked
				}
			}
			temp = temp->next;				//move temp forward since it wasn't what we're deleting
		}
	return false;							//otherwise delete didn't work
	
	/* hints: don't forget to consider that there are multiple cases. Some cases take constant time, while some may take longer time.
		1. if the node is head/tail, 
		2. if there is only one element in a list (head=tail)
		3. if the node is an intermediate node (neither head nor tail) 
		please set the correct head and tail pointers after delete, otherwise your list will be in a mess
	*/
}
