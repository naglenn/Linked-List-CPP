#include <iostream>
#include <iomanip>
#include <fstream>
#include "LinkedList.h"

using namespace std;

/****************************************************************************
* LinkedList default constructor
* Descr: constructs linked list object and initializes head and tail nodes
* Input: none
****************************************************************************/
LinkedList::LinkedList()
{
	headNode.number = -1;
	headNode.prevNode = nullptr;
	headNode.nextNode = &tailNode;

	tailNode.number = -1;
	tailNode.nextNode = nullptr;
	tailNode.prevNode = &headNode;

} // end LinkedList()

/****************************************************************************
* Function: printListForward()
* Descr: Prints the list in normal order
* Input: none
* Return: none
****************************************************************************/

void LinkedList:: printListForward()
{
	count = 0;

	currNode = headNode.nextNode;

	// displays the linked list
	while (currNode->number != -1)
	{
		cout << setw(5) << currNode->number;

		count++;
		if (count % 10 == 0)
			cout << endl;

		currNode = currNode->nextNode;

	} // end while

	cout << endl << endl;

} // end printListForward()

  /****************************************************************************
  * Function: printListBackward()
  * Descr: Prints the list in reverse order
  * Input: none
  * Return: none
  ****************************************************************************/

void LinkedList:: printListBackward()
{
	count = 0;

	currNode = tailNode.prevNode;

	while (currNode->number != -1)
	{
		cout << setw(5) << currNode->number;

		count++;
		if (count % 10 == 0)
			cout << endl;

		currNode = currNode->prevNode;
	} // end while()

	cout << endl << endl;

} // end printListBackward()

  /****************************************************************************
  * Function: addNodeToEnd
  * Descr: Adds a node to the end of the list
  * Input: int to be added
  * Return: ptr to added Node
  ****************************************************************************/
Node * LinkedList:: addNodeToEnd(int value)
{
	// insert node to end of linked list
	currNode = tailNode.prevNode;
	currNode->nextNode = new Node;
	currNode = currNode->nextNode;
	currNode->number = value;
	currNode->nextNode = &tailNode;
	currNode->prevNode = tailNode.prevNode;
	tailNode.prevNode = currNode;

	return currNode;

} // end addNodeToEnd

/****************************************************************************
* Function: addNodeToBeginning
* Descr: Adds a node to the beginning of the list
* Input: int to be added to list
* Return: ptr to new node
****************************************************************************/

Node * LinkedList::addNodeToBeginning(int value)
{
	currNode = headNode.nextNode;
	currNode->prevNode = new Node;
	currNode = currNode->prevNode;
	currNode->number = value;
	currNode->nextNode = headNode.nextNode;
	currNode->prevNode = &headNode;
	headNode.nextNode = currNode;

	return currNode;

} // end addNodeToBeginning()

/****************************************************************************
* Function: initFile
* Descr: Initializes the linked list with the files contents
* Input: none
* Return: none
****************************************************************************/

void LinkedList::initFile()
{
	file.open("Perm 50.txt");
	listSize = 0;

	while (file >> num)
	{
		currNode = addNodeToEnd(num);
		listSize++;
	} // end while()

	file.close();

} // end initFile()

  /****************************************************************************
  * Function: sort
  * Descr: Sorts the list using a bubble sort
  * Input: none
  * Return: none
  ****************************************************************************/

void LinkedList::sort()
{
	swap = true;

	while (swap) // all passes
	{
		currNode = headNode.nextNode;
		swap = false;

		while (currNode->nextNode->number != -1) // individual passes
		{
			if (currNode->number > currNode->nextNode->number) // determines switch
			{
				num = currNode->number;
				currNode->number = currNode->nextNode->number;
				currNode->nextNode->number = num;
				swap = true;
			} // end if()

			currNode = currNode->nextNode;

		} // end while()

	}//end while(swap)

} // end sort()

  /****************************************************************************
  * Function: ~LinkedList()
  * Descr: Delets dynamic mem in linked list
  * Input: none
  ****************************************************************************/
LinkedList::~LinkedList()
{
	currNode = headNode.nextNode;

	while (currNode->number != -1)
	{
		nextNode = currNode->nextNode;
		delete currNode;
		currNode = nextNode;

	} // end while()

} // end ~LinkedList()

/****************************************************************************
* Function: LinkedList [] operator
* Descr: Allows access of linked list like an array
* Input: int subscript to be changed
* Return: reference to the chosen node's number
****************************************************************************/
int & LinkedList::operator[](const int  &sub)
{
	if (sub < 0 || sub >= listSize)
	{
		cout << "\nSubscript Error\n";
		return useless;

	} // end if()

	else
	{
		currNode = headNode.nextNode;
		for (int i = 0; i < sub; i++)
			currNode = currNode->nextNode;
		return currNode->number;

	} // end else

} // end LinkedList::operator[](const int  &sub)
