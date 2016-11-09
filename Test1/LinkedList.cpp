/*
LinkedList.cpp
LinkedList class member-function definitions.
@reference Lecture Notes from Prof.'s "Comp5421BB The Message class we wrote in class ", May 11,2016
@reference book of DataStruncture & Algorithms in C++, Michael T Goodrich etc.
*/

#include <iostream>
#include "LinkedList.h"
#include "Line.h"

struct LinkedList::ListNode {
	//data element
	//pointer to previous node
	//pointer to next node
	Line data;
	ListNode* prev;
	ListNode* next;

	//ctor
	ListNode(const Line& data1, ListNode* prev1, ListNode* next1)
		: data(data1), prev(prev1), next(next1) {}

// constructor sets and gets
	void ListNode::setData(const Line& data) {
		this->data = data;
	}
	void ListNode::setPrev(ListNode* prev) {
		if (prev = nullptr) prev = nullptr;
		this->prev = prev;
	}
	void ListNode::setNext(ListNode* next) {
		if (next = nullptr) next = nullptr;
		this->next = next;
	}

	const Line& ListNode::getData() const {
		return data;
	}
	ListNode* ListNode::getPrev() const {
		return prev;
	}
	ListNode* ListNode::getNext() const {
		return next;
	}
};


//ctor
LinkedList::LinkedList(): theSize(0),
	head(new ListNode(*new Line(""), nullptr, nullptr)),
	tail(new ListNode(*new Line(""), head, nullptr))
	{head->next = tail;}

LinkedList::~LinkedList() {
	//cout << "Destructor is called" << endl;
	removeAll();
}

//copy
LinkedList::LinkedList(const LinkedList& rhs) {
	deepCopy(rhs);
}

//copy assignment
const LinkedList& LinkedList::operator=(const LinkedList& rhs) {
	if (this != &rhs) {
		removeAll();
		deepCopy(rhs);
	}
	return *this;
}

//inserts line at the front of the this list
void LinkedList::push_front(const Line& line) {
	ListNode *temp = new ListNode(line, head, head->next);
	head->next->prev = temp;
	head->next = temp;
	theSize++;
}

//inserts line at the end of the this list
void LinkedList::push_back(const Line& line) {
	ListNode *temp = new ListNode(line, tail->prev, tail);
	tail->prev->next = temp;
	tail->prev = temp;
	theSize++;
}

//remove the rst node in this list
void LinkedList::pop_front() {
	if (empty()) { return; }
	ListNode *temp = head->next;
	head->next->next->prev = head;
	head->next = head->next->next;
	delete temp;
	theSize--;
}

//remove the last node in this list
void LinkedList::pop_back() {
	ListNode * temp = tail->prev;
	tail->prev->prev->next = tail;
	tail->prev = tail->prev->prev;
	delete temp;
	theSize--;
}

//returns the size of this list
int LinkedList::size() const {
	return theSize;
}

//returns whether this list is empty
bool LinkedList::empty() const {
	return (head->next == tail);
	//return theSize == 0;
}

//inserts a new node with line at position k in this list
void LinkedList::insert(const Line& line, int k) {
	checkIndex(k);
	if (k == 1) {
		push_front(line);
	}
	else if (k == size()) {
		push_back(line);
		return;
	}
	else {
		ListNode* prev = find(k - 1);
		ListNode* temp = new ListNode(line, prev, prev->next);
		prev->next->prev = temp;
		prev->next = temp;
		++theSize;
	}
}

//removes node at position k in this list
void LinkedList::remove(int k) {
	checkIndex(k);

	ListNode* prev = find(k - 1);
	ListNode* temp = prev->next;
	temp->next->prev = prev;
	prev->next = temp->next;
	delete temp;
	--theSize;
}

//remove all by using pop
void LinkedList::removeAll() {
	while (!empty()) pop_front();
}

// Deep copies the supplied list into this list
//@param rhs the list to copy from
void LinkedList::deepCopy(const LinkedList& rhs) {
	head=(new ListNode(*new Line(""), nullptr, nullptr));
	tail = (new ListNode(*new Line(""), head, nullptr));
	head->next = tail;
	theSize = rhs.theSize;
	if (rhs.empty()) return;
	head->next = new ListNode(rhs.front(), head, tail);
	ListNode* curr = head->next;
	tail->prev = curr;
	ListNode* temp = rhs.head->next->next;
	while (temp != rhs.tail) {
		ListNode *newTemp = new ListNode(temp->data, curr, tail);
		curr->next = newTemp;
		tail->prev = newTemp;
		curr = newTemp;
		temp= temp->next;
	}
}

// Check whether an elemnet exists at a given index before attempting to access that element
void LinkedList::checkIndex(int i) const {
	if ((i<1) || (i>size())) {
		cout << "Error, Out_Of_range" << endl;
		return;
	}
}

//print
void LinkedList::print(int lineNum) {
	checkIndex(lineNum);
	ListNode* temp = find(lineNum);
	cout << temp->data;
}

// return a pinter to the node at a given position in the list
//@param i means index, the postion of the node
LinkedList::ListNode * LinkedList::find(int i) const {
	if (i<1 || i>size()) {
		return nullptr;
	}
	else {
		ListNode *current = head->next;
		for (int j = 1; j < i; j++) {
			current = current->next;
		}
		return current;
	}
}

// return a constant reference to the firt element in the list
const Line& LinkedList::front() const {
	return this->head->next->data;
	//return head->next->data;
}

/*
// add a node in a given node position
// will be figured out....
void LinkedList::add(ListNode * v, const Line& k) {
ListNode* temp = new ListNode(k, head->next, tail->prev);
temp->data = k;
temp->next = v;
temp->prev = v->prev;
v->prev->next = temp;
v->prev = temp;
}

// remove a given value node node
void LinkedList::removeNode(ListNode *v) {
ListNode* u = v->prev;
ListNode* w = v->next;
u->next = w;
w->prev = u;
delete v;
}

*/
