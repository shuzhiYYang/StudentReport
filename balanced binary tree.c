#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "balanced binary tree.h"

AVLtree CreateTree(){
	AVLtree root=NULL;
	return root;
}

AVLnode *FindInTree(AVLtree root, char *name){
	if(root==NULL)
	return NULL;
	if(strcmp(root->student.name,name)>0)
	return FindInTree(root->left,name);
	else if(strcmp(root->student.name,name)<0)
	return FindInTree(root->right,name);
	else
	return root;
}

int Max(int a, int b){
	return a>b?a:b;
}

int Height(AVLtree root){
	if(root==NULL){
		return -1;
	}
	else{
		return 1+Max(Height(root->left),Height(root->right));
	}
}

AVLnode *FindMin(AVLtree root){
	if(root!=NULL){
		while(root->left!=NULL){
			root=root->left;
		}
	}
	return root;
}

AVLnode *FindMax(AVLtree root){
	if(root!=NULL){
		while(root->right!=NULL){
			root=root->right;
		}
	}
	return root;
}

AVLtree InsertInTree(AVLtree root, Stu Student){
	if(root==NULL){
		root=(AVLnode*)malloc(sizeof(AVLnode));
		root->student=Student;
		root->right=root->left=NULL;
		root->height=0;
	}
	else if(strcmp(root->student.name,Student.name)>0){
		root->left=InsertInTree(root->left,Student);
		if((Height(root->left)-Height(root->right))==2){
			if(strcmp(root->student.name,Student.name)>0){
				root=LeftLeftRotation(root);
			}
			else{
				root=LeftRightRotation(root);
			} 
		}
	}
	else if(strcmp(root->student.name,Student.name)<0){
		root->right=InsertInTree(root->right,Student);
		if((Height(root->right)-Height(root->left))==2){
			if(strcmp(root->student.name,Student.name)<0){
				root=RightRightRotation(root);
			}
			else{
				root=RightLeftRotation(root);
			}
		}
	}
	root->height=Max(Height(root->left),Height(root->right))+1;
	return root;
}

AVLtree DeleteInTree(AVLtree root, char *name){
	AVLnode *temp;
	if(root==NULL||name==NULL)
		return NULL;
	else if(strcmp(root->student.name,name)>0){
		root->left=DeleteInTree(root->left,name);
		if(Height(root->right)-Height(root->left)==2){
			AVLnode *r=root->right;
			if(Height(r->left)<Height(r->right)){
				root=RightRightRotation(root);
			} 
			else{
				root=RightLeftRotation(root);
			}
		}
	}
	else if(strcmp(root->student.name,name)<0){
		root->right=DeleteInTree(root->right,name);
		if(Height(root->left)-Height(root->right)==2){
			AVLnode *l=root->left;
			if(Height(l->left)>Height(l->right)){
				root=LeftLeftRotation(root);
			}
			else{
				root=LeftRightRotation(root);
			}
		}
	}
	else{
		if(root->left&&root->right){
			if(Height(root->left)>Height(root->right)){
				AVLnode *max=FindMax(root->left);
				root->student=max->student;
				root->left=DeleteInTree(root->left,max->student.name);
			}
			else{
				AVLnode *min=FindMin(root->right);
				root->student=min->student;
				root->right=DeleteInTree(root->right,min->student.name);
			}
		} 
		else{
			AVLnode *temp=root;
			root=root->left?root->left:root->right;
			free(temp);
		}
	}
	return root;
} 

AVLtree DestroyTree(AVLtree root){
	while(root!=NULL){
		root=DeleteInTree(root,root->student.name);
	}
	return NULL;
}

AVLnode *LeftLeftRotation(AVLnode *k2){
	AVLnode *k1;
	k1=k2->left;
	k2->left=k1->right;
	k1->right=k2;
	k2->height=Max(Height(k2->left),Height(k2->right))+1;
	k1->height=Max(Height(k1->left),Height(k1->right))+1;
	return k1;
}

AVLnode *RightRightRotation(AVLnode *k2){
	AVLnode *k1;
	k1=k2->right;
	k1->left=k2->right;
	k1->left=k2;
	k2->height=Max(Height(k2->left),Height(k2->right))+1;
	k1->height=Max(Height(k1->left),Height(k1->right))+1;
	return k1;	  
}

AVLnode *LeftRightRotation(AVLnode *k3){
	k3->left=RightRightRotation(k3->left);
	return LeftLeftRotation(k3);
} 

AVLnode *RightLeftRotation(AVLnode *k3){
	k3->right=LeftLeftRotation(k3->right);
	return RightRightRotation(k3);
}
