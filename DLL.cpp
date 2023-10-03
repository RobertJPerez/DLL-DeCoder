
/* Luke Fanizzi, Angelina Gargiulo, Robert Perez
 * TA : Lauren Olson
 * 4/16/2020
 * This file contains functions for the mini lab. These functions are
 * used to create, modify and destruct doubly linked list and reveal
 * secret codes as a requirement for the mini lab.
 */


/*
 * DLL.cpp
 *
 *  Created on: Apr 2, 2020
 *      Author: 13027
 */
//Part 1:(20 pts) (addFirst (3pts) ,addAtFront(4 pts),push (4 pts),pop(4 pts)) + getting secret message:5 pts
//In the DLL.cpp class, get push, pop, and addFirst and addAtFront working for a doubly linked list as specified in DLL.hpp and DLL.cpp.
//For this section I've given you the test cases.  You should get the output I've given you for part 1. When you get those methods working, running this will decode the secret code 1
//
//Once you have that working, start on part 2 (note you will have to go into Coder.cpp and toggle
//comments for lines 64-110 to run part 2)
//
//Part 2: (15 pts)(insertAt(5 pts), removeAtK(5 pts)) +secret message: 5 pts
//Get  the DLL.cpp methods insertAt and removeAtK methods working for a doubly linked list.
//I've given you the test cases and the output.  When you get them working, you should be able to run this and decode the second secret code
//
//Once you have that working, start on part 3 (note that you will have to go to Coder.cpp and toggle comments for lines 112-137 to run part 3)
//
//Part 3: (8 pts) (reverse (4 pts)) + secret message: 4 pts
//For this part, you will get the method reverse working for the DLL doubly linked list class.
//This method reverses the list.  Note: it doesn't just print out the list in reverse order, it actually reverses the list, so if the original list was 3<->2<->4<->8, with 3 being first and 8 being last, the reversed list would be 8<->4<->2<->3 with 8 being first and 3 being last.
//
//once you have that working, start on part 4 (note that you will have to go to Coder.cpp and toggle
//comments for lines 139-215 to run part 4)
//
//Part 4: (11 pts) (removeX (5 pts), call by pointer) + secret message: 6 pts
//For this part, you will get the method removeX to work.  removeX removes the value x from the linked list, and uses call by pointer to change the index parameter to be the index (count) of where x occurred in the list.  So, for instance if you had:
//7<->8<->3<->5<->2<->6<->1
//And you called: removeX(3,&ind)
//When  you leave the method, you’d have
//7<->8<->5<->2<->6<->1
//And ind would hold 2
//
//Once you have this working, start on part 5.  For this you will have to go to Coder.cpp and toggle comments for lines  217- 251
//
//Part 5: (21 pts)(skip – recursive (13 pts) + secret message: 8 pts
//For this part, you will get the method skip working for the DLL doubly linked list class. This method RECURSIVELY deletes every other node.  If the boolean flag is set to true, it will delete every even node (i.e.,if the list was
//3<->2<->4<->5<->1<->7,
//the list that would result after the skip method was called would be:
//3<->4<->1.
//If the flag is set to false, the resulting list will be
//2<->5<->7
//NOTE:  For efficiency's sake, this method SHOULD NOT call removeAtK



#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

DLL::DLL(){  // constructor - initializes an empty list
	last = NULL;
	first = NULL;
	size = 0;
}
DLL::DLL(int x){  // constructor, initializes a list with one new node with data x
	DNode *d = new DNode (x);
	first = d;
	last = d;
	size=1;
}
/***************************************************************************************************/
/*Part 1																																		*/
/***************************************************************************************************/
/* write push, pop, addAtFront */

void DLL::push(int x) {  // does what you'd think - write for part 1
	DNode *node = new DNode(x);
		if(first == NULL){ //list is empty
			first = node;
			last = node;
		}
		else{ //list not empty,adding new node to end
			DNode *temp = last;
			last->next = node;
			node->prev = temp;
			last = node;
		}
		node->next = NULL;
	size++;
}
int DLL::pop() { //does what you'd think - write for part 1
	int x;
	if(size == 0){ //empty list
		return 0;
	}
	else if(size == 1){ //list of size 1
		DNode *node = last;
		x = first->data;
		delete node;
		first = NULL;
		last = NULL;
		size--;
		return x;
	}
	else{
		DNode *node = first;
		while(node->next != last){ //couldnt get it working with last pointer so did it iteratively
			node=node->next;
		}
		x = node->next->data;
		delete last;
		last = node;
		node->next = NULL;
		size--;
	}
	return x;
}

void DLL::addAtFront(int x) { // add a node to the beginning of the list (this should work whether
	// there's a node already in the list or the list is empty
	DNode *n = new DNode(x);
	n->next = first;
	first = n;
	size++;
}

void DLL::addFirst(int x) {// add the very first node to the list (Do for part 2)
	DNode *n = new DNode(x);
	first = n;
	last = n;
	first->next = NULL;
	size++;
}

/***************************************************************************************************/
/*Part 2																																		*/
/***************************************************************************************************/
/* write insertAt, removeAtK  here */
//insertAt functions to insert a number at a certain poin t of the list.
//It takes in two integers, x and index and returns nothing
void DLL::insertAt(int ind, int x) {
    if (ind == 0) { //if index is zero...
        addAtFront(x); //add at front of list
    }
    else if (ind == size) {//if the index is the size
           push(x); //add to the back of the list
       }
    else if (ind < size) {  // if index is less than the size
        DNode *temp = first; // sets a holder for the head
        for (int i = 0; i < ind-1; i++) {
            temp = temp->next; //sets the holder as the next Node
        }
        DNode *temp2 = temp->next; //adds another holder for the next node
        temp->next = new DNode(x);
        temp->next->next = temp2;
        temp->next->prev = temp;
        temp2->prev = temp->next; //sets the previous as the next
        size++; //increments size
    }
}
int DLL::removeAtK(int ind) {
    DNode *tmp = first;
    if (ind == 0) { // removing first node
        if (size == 1) {//list of size 1
            int x = tmp->data;
            first = NULL;
            last = NULL;
            delete tmp;
            size --;
            return x;
        }
        else { //list > size 1
            int x = tmp->data;
            first = tmp->next;
            first->prev = NULL;
            delete tmp;
            size--;
            return x;
        }
    }
    else if (ind == size-1) {//removing last node
        pop();
    }
    else {
        for (int i = 0; i < ind-1; i++) {//iterating to index i-1
            tmp = tmp->next;
        }
        //swapping pointers to remove node at index i
        int x = tmp->next->data;
        DNode *tmp2 = tmp->next;//node at i+1
        tmp->next = tmp->next->next; //linking node at i-1 to i+1
        tmp->next->prev = tmp; //linking note at i+1 to i-1
        tmp2->prev = NULL;
        tmp2->next = NULL;
        delete tmp2;
        size--;
        return x;
    }
    return -1;
}
/****************************************************************************************/
/* Part 3                                                                                                                       */
/****************************************************************************************/
/* write reverse here */
//This function takes in nothing and returns nothing
//This reverses a doubly linked list entirely
void DLL::reverse(){
	    DNode *value = first; //creates a holder for the head of the list
		DNode *holder = nullptr; //creates another holder and sets it to null
	    DNode *ind = first; //starts the indexing at the head of the list
	    while (true) // while loop to run until broken
	    {
//this part actually does the reversing
	    	// swaps next and previous
	        holder = ind->prev; // saves the previous node
	        ind->prev = ind->next; // replaces the previous noode with the next node
	        ind->next = holder; //saves the next node in a temp variable
	        ind = ind->prev; //sets the current index to the previos space
	        if(ind == nullptr){ //checks if the index holds a null value
	        	break; //breaks the while loop
	        }
	    }


	     if(holder != nullptr )  { //checks if the temp value is NULL or not
	        first = holder->prev; // sets head of list value to the saved previous node value
	}

	     first = last; // sets the first node to the last node
	     last = value; // sets the last node to the holder that is holding the value of the first node

}



/****************************************************************************************/
/* Part 4                                                                                                                       */
/****************************************************************************************/
/* write removeX here */
/*
 This function takes in an integer, x, and a pointer to an integer, *ind.
This functions purpose is to remove the first occurance of x from the list.

 */
void DLL::removeX(int x, int *ind){
	int counter = 0;  //counter to count how many nodes have been checked
	DNode *holder = nullptr; //holds value at position
	DNode *index = first;   //starts index at the head of the list
    bool last2 = false; //initiates a bool as false, to help with last index
	if(first->data == x){ //checks data in first node is equal to x
		DNode *nodeToDelete = first; //initiates a holder for the node we want to delete

		first=first->next; //first node equals the next node
		first->prev = NULL;  // sets the previous node to NULL

		//delete to stop memory leaks
		delete nodeToDelete; // deletes the node

		*ind = 0; //ensures the index is 0 for the first node
	}
	else if(last->data == x){ //checks if the value at the last node is equal to x

						DNode *nodeToDelete = last;  //initiates a holder for the node we want to delete

						last=last->prev; //the last node equals the previous node
						last->next = NULL; //Sets the next node to NULL

						//delete to stop memory leaks
						delete nodeToDelete; //deletes node

						*ind = size; //ensures index is correct
						last2 = true; //sets the boolean to true to help with correct indexing later in the function

					}


	else{
		while(true){//while loop that will continuously run until broken

			 if(index -> data == x){ //checks if data at index is equal to x
				holder = index; //holder for current index
				holder->prev->next = holder->next; //adjusts links around holder
				holder->next->prev = holder->prev; //adjusts links around holder

				break; //breaks while loop
			}

			 if(counter == size -1 ){ //checks the counter against the size (minus 1) (not in list)

							*ind = -1; //ensures index is correct for something not in the list

						    break; // breaks while loop

						}

			else {
				counter++; //increments counter

				index = index -> next; // moves index over 1 to go further through list
			}


		}

	}

if(counter == size){ // checks if counter is equal to size

	*ind = -1; // double checks that the index is set correctly
}


else if(counter < size && *ind != -1){// checks parameters

*ind = counter; //double checks index is correct for given parameters
delete holder; // deletes the node with the value of x
	size--; //decreases size
}
if(last2){ //checks if the last node was deleted
	*ind = size; //ensures the index is correct
}

}


/****************************************************************************************/
/* Part 5                                                                                                                     */
/****************************************************************************************/
/* write skip here */
//For this part, you will get the method skip working for the DLL doubly linked list class. This method RECURSIVELY
//deletes every other node.

void DLL::skip(bool flag, int ct, DNode *tmp){
	DNode *holder = nullptr;  // Sets nullptr to a tmp value
	if(flag == false){ //condition if flag is false
		if (ct >= size-1){// base case that stops loop if ct >= size-1
			return;
		}
		DNode *tempvle=tmp->next; //tempvle set to the next node
		if(tempvle->next == holder){ // if the next node is null sets last to the last node
			last = tempvle->prev;
			last->next = holder; // sets it to nullptr
		}
		else{ // sets each node equal to eachother
			tempvle->next->prev = tempvle->prev;
			tempvle->prev->next = tempvle->next;
		}
		free(tempvle); //deletes node
		size = size-1; //adjusts the size by -1
		skip(flag,ct+1,tmp->next); //recursively calls the skip function deleting every other
	}
	 else if (flag == true){ //condition if flag is true
	 		DNode *tempvle = tmp; // Sets nullptr to a tmp value
	 		if(tempvle->prev == holder){ // if the next node is null sets last to the last node
	 			first = tempvle->next; // first is set to the next value
	 			first->prev=holder; // sets the value before to holder
	 		}
	 		else if (tempvle->next == holder){ // if the next node is null
	 			last = tempvle->prev; // last will equal prev
	 			last->next = holder; // sets next to holder
	 		}
	 		else{// sets each node equal to eachother
	 			tempvle->next->prev = tempvle->prev;
	 			tempvle->prev->next = tempvle->next;
	 		}
	 		free(tempvle); //deletes node
	 		size = size-1; //adjusts the size by -1
	 		if(ct >= size-1){ // base case that stops loop if ct >= size-1
	 			return;
	 		}
	 		skip(flag,ct+1,tempvle->next->next); //recursively calls the skip function deleting even numbers
	 	}
}




/***************************************************************************************************/
/*End of your part																														*/
/***************************************************************************************************/

void DLL::printList() {
	DNode *tmp = first;
	while (tmp != NULL) {
		cout << tmp->data << ", ";
		tmp = tmp->next;
	}
	cout << endl;
}
void DLL::printCode() {
	DNode *tmp = first;
	while (tmp != NULL) {
		cout << alpha[tmp->data];
		tmp = tmp->next;
	}
	cout << endl;
}

DLL::~DLL(){
        DNode *tmp = first;
        DNode *tmp2 = first->next;
        while (tmp != NULL) {
                delete tmp;
                tmp = tmp2;
                if (tmp != NULL) {
                        tmp2 = tmp2->next;
                }
        }
}

