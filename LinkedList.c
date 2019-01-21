#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

LinkedList CreateList(){
	Node *head=(Node*)malloc(sizeof(Node));
	head->next=NULL;
	return head;
}

LinkedList InsertInList(LinkedList head, Stu student){
	Node *pre=head;
	Node *temp=head->next;
	while(temp!=NULL){
		if(strcmp(student.name,temp->student.name)>0){
			pre=temp;
			temp=temp->next;
		}
		else{
			break;
		}
	}
	Node *pNode=(Node*)malloc(sizeof(Node));
	pNode->student=student;
	pNode->next=temp;
	pre->next=pNode;
	return head;
} 

LinkedList DeleteInList(LinkedList head, char *name){
	Node *pre=head;
	Node *temp=head->next;
	while(temp!=NULL){
		if(strcmp(temp->student.name,name)!=0){
			pre=temp;
			temp=temp->next;
		}
		else{
			pre->next=temp->next;
			break;
		}
	}
	free(temp);
	return head;
}

LinkedList FindInList(LinkedList head, char *name){
	Node *pre=head;
	Node *temp=head->next;
	while(temp!=NULL){
		if(strcmp(temp->student.name,name)==0){
			return temp;
		}
		else{
			pre=temp;
			temp=temp->next;
		}
	}
	return NULL;
}

LinkedList DestroyList(LinkedList head){
	Node *pre=head;
	Node *cur=head->next;
	while(cur!=NULL){
		free(pre);
		pre=cur;
		cur=cur->next;
	}
	free(pre);
	return NULL;
}
