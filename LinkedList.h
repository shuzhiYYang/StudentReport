#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include "stuInfo.h"

typedef struct node Node;
typedef struct node *LinkedList;

struct node{
	Stu student;
	struct node *next;
};

LinkedList CreateList();
LinkedList InsertInList(LinkedList head, Stu student);
LinkedList DeleteInList(LinkedList head, char *name);
LinkedList FindInList(LinkedList head, char *name);
LinkedList DestroyList(LinkedList head);

#endif//!__LINKEDLIST_
