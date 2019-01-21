#ifndef _BALANCED_BINARY_TREE_H
#define _BALANCED_BINARY_TREE_H

#include "stuInfo.h"

typedef struct AVLNode AVLnode;
typedef struct AVLNode *AVLtree;
struct AVLNode{
	Stu student;
	struct AVLNode *left;
	struct AVLNode *right;
	int height;
};

AVLtree CreateTree();
AVLnode *FindInTree(AVLtree root, char *name);
int Max(int a, int b);
int Height(AVLtree root);
AVLnode *FindMin(AVLtree root);
AVLnode *FindMax(AVLtree root);
AVLtree InsertInTree(AVLtree root, Stu Student);
AVLtree DeleteInTree(AVLtree root, char *name);
AVLtree DestroyTree(AVLtree root);

AVLnode *LeftLeftRotation(AVLnode *k2);
AVLnode *RightRightRotation(AVLnode *k2);
AVLnode *LeftRightRotation(AVLnode *k3);
AVLnode *RightLeftRotation(AVLnode *k3);

#endif //!_BALANCED_BINARY_TREE_H
