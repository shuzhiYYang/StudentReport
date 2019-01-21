#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "balanced binary tree.h"
#include "LinkedList.h"

#define LIST (0)
#define TREE (1)

void menu();
void IntroduceStudent(int mode);
void RemoveStudent(int mode);
void IntroduceMark(int mode);
void PrintReport(int mode);
void PrintAllReport(int mode);
void PrintAllTree(AVLtree tree);
void SaveToFile(int mode);
void PrintToFile(FILE *fp,AVLtree tree);
void RetrieveData(int mode);

LinkedList list;
AVLtree tree;

int main(int argc, int *argv[]){
	if(argc!=2||strcmp(argv[1],"list")!=0 && strcmp(argv[1],"tree")!=0){
		printf("Usage: %s <option>\n",argv[0]);
		printf("<Option>\n  list-use a linked list sructure\n  tree-use a balanced binary tree structure\n");
		return 0;
	}
	int mode;
	if(strcmp(argv[1],"list")==0){
		mode=LIST;
		printf("Using a ordered linked list structure\n");
	}
	else{
		mode=TREE;
		printf("Using a balanced binary tree structure\n");
	} 
	list=CreateList();
	tree=CreateTree();
	int opt;
	do{
		menu();
		scanf("%d",&opt);
		getchar();
		if(opt<=0||opt>=9){
			printf("You have entered invalid value!\n");
			continue;
		}
		switch(opt){
			case 1:
				IntroduceStudent(mode);
				break;
			case 2:
				RemoveStudent(mode);
				break;
			case 3:
				IntroduceMark(mode);
				break;
			case 4:
				PrintReport(mode);
				break;
			case 5:
				PrintAllReport(mode);
				break;
			case 6:
				SaveToFile(mode);
				break;
			case 7:
				RetrieveData(mode);
				break;
			case 8:
				printf("You have exited!");
				break;
		}
			
	} while (opt != 8);
	return 0;
}

void menu(){
	printf(" %d) Introduce student\n",1);
	printf(" %d) Remove student\n",2);
	printf(" %d) Introduce marks\n",3);
	printf(" %d) Print students report\n",4);
	printf(" %d) Print report for all students\n",5);
	printf(" %d) Save to file\n",6);
	printf(" %d) Retrieve data from file\n",7);
	printf(" %d) Exit\n",8);
}

void IntroduceStudent(int mode){
	Stu student;
	printf("Enter a student name\n");
	gets_s(student.name,30);
	printf("Enter the student ID\n");
	scanf("%d",&student.id);
	printf("Enter the mark\n");
	scanf("%f",&student.mark);
	if(mode==LIST){
		list=InsertInList(list,student);
	}
	else{
		tree=InsertInTree(tree,student);
	}
}

void RemoveStudent(int mode){
	char name[30];
	printf("Enter the name\n");
	gets_s(name,30);
	if(mode==LIST){
		list=DeleteInList(list,name);
	}
	else{
		tree=DeleteInTree(tree,name);
	}
}

void IntroduceMark(int mode){
	char name[30];
	printf("Enter the name\n");
	gets_s(name,30);
	if(mode==LIST){
		Node *stu=FindInList(list,name);
		if(stu==NULL){
			printf("No such student exist!\n");
			return;
		}
		else{
			printf("Enter the new mark\n");
			scanf("%f",&stu->student.mark);
		}
	} 
	else{
		AVLnode *stu=FindInTree(tree,name);
		if(stu==NULL){
			printf("No such student exist!\n");
			return; 
		} 
		else{
			printf("Enter the new mark\n");
			scanf("%f",&stu->student.name);
		}
	}
}

void PrintReport(int mode){
	char name[30];
	printf("Enter the name\n");
	gets_s(name,30);
	Stu s;
	if(mode==LIST){
		Node *stu=FindInList(list,name);
		if(stu==NULL){
			printf("No such student exist!\n");
			return; 
		} 
		s=stu->student;
	}
	else{
		AVLnode *stu=FindInTree(tree,name);
		if(stu==NULL){
			printf("No such student exist!\n");
			return; 
		} 
		s=stu->student;
	}
	printf("%-20s %-6s %-6s\n","Name","ID","Mark");
	printf("%-20s %-6d %-6.2f\n",s.name,s.id,s.mark);
}

void PrintAllReport(int mode){
	printf("%-20s %-6s %-6s\n","Name","ID","Mark");
	if(mode==LIST){
		Node *node=list->next;
		while(node!=NULL){
			printf("%-20s %-6d %-6.2f\n",node->student.name,node->student.id,node->student.mark);
			node=node->next;
		}	
	}
	else{
		PrintAllTree(tree);
	}
}

void PrintAllTree(AVLtree tree){
	if(tree==NULL)
		return;
	PrintAllTree(tree->left);
	printf("%-20s %-6d %-6.2f\n",tree->student.name,tree->student.id,tree->student.mark);
	PrintAllTree(tree->right);
}

void SaveToFile(int mode){
	char filename[30];
	printf("Enter the file name\n");
	gets_s(filename,30);
	FILE *fp;
	if((fp=fopen(filename,"w"))==NULL){
		printf("Error occurs when saving to the file\n");
		return;
	}
	if(mode==LIST){
		Node *node=list->next;
		while(node!=NULL){
			fprintf(fp,"%s\n %d\n %.f\n",node->student.name,node->student.id,node->student.mark);
			node=node->next;
		}
	}
	else{
		if(tree!=NULL)
		PrintToFile(fp,tree);
	}
	printf("Success!\n");
	fclose(fp);
} 

void PrintToFile(FILE *fp,AVLtree tree){
	if(tree==NULL)
		return;
	PrintToFile(fp,tree->left);
	fprintf(fp,"%s\n %d\n %.f\n",tree->student.name,tree->student.id,tree->student.mark);
	PrintToFile(fp,tree->right);
}

void RetrieveData(int mode){
	char filename[30];
	printf("Enter the file name\n");
	gets_s(filename,30);
	FILE *fp;
	if((fp=fopen(filename,"r"))==NULL){
		printf("Error occurs when retrieving from the file");
		return;
	}
	if(mode==LIST){
		list=DestroyList(list);
		list=CreateList();
		Stu student;
		while((fgets(student.name,30,fp))!=NULL){
			fscanf(fp,"%d %f",&student.id,&student.mark);
			student.name[strlen(student.name)-1]='\0';
			fgetc(fp);
			list=InsertInList(list,student);
		}
	}
	else{
		tree=DestroyTree(tree);
		tree=CreateTree();
		Stu student;
		while((fgets(student.name,30,fp))!=NULL){
			fscanf(fp,"%d %f",&student.id,&student.mark);
			student.name[strlen(student.name)-1]='\0';
			fgetc(fp);
			tree=InsertInTree(tree,student);
		}
	}
	printf("Success!\n");
}



