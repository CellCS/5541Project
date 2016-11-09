/*
LinkedList.h
LineedLIst class declaration
prevent multiple inclusions of header
@reference files from Prof.'s "Comp5421BB The Message class we wrote in class ", May 11,2016
@reference book of DataStruncture & Algorithms in C++, Michael T Goodrich etc.
*/

#pragma once
#include <iostream>
#include "Line.h"

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class LinkedList {
private:
	int theSize{ 0 };
	struct ListNode;
	
	ListNode* head{ nullptr };
	ListNode* tail{ nullptr };

public:
	LinkedList();
	virtual ~LinkedList();
	LinkedList(const LinkedList& rhs);
	const LinkedList& operator=(const LinkedList& rhs);
	void push_front(const Line&);
	void push_back(const Line&);

	void pop_front();
	void pop_back();

	int size() const;
	bool empty() const;
	void insert(const Line& line, int k);
	void print(int);
	void remove(int k); //remove index k node
	//void removeNode(ListNode* k); // remove node k
	//void add(ListNode* v, const Line& k);// insert new node before v


private:
	const Line& front() const;
	void removeAll();
	void deepCopy(const LinkedList&);
	void checkIndex(int i) const;
	LinkedList::ListNode* find(int) const;

};

#endif
