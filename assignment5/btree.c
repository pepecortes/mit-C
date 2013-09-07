#include <stdio.h>
#include <stdlib.h>

struct tnode
	{
	int data;
	struct tnode *left;
	struct tnode *right;
	};
	
	
struct tnode* talloc(int data)
	/*allocates a new node with the given data.*/
	{
	struct tnode *output;
	output = (struct tnode*)malloc(sizeof(struct tnode));
	output->data = data;
	return output; 
	}
	
struct tnode* addnode(struct tnode* root, int data)
	/*
	add the data to the root node.
	recursive. data goes to the right of left. if position
	is not free, goes down the tree
	*/
	{
	struct tnode* new = NULL;
	if (root == NULL) // the positions is free: go ahead
		{
		new = (struct tnode*)malloc(sizeof(struct tnode));
		new->data = data;
		}
	else if (data < root->data)
		root->left = addnode(root->left, data);
	else
		root->right = addnode(root->right, data);
	return new;
	}
	
void preorder(struct tnode* root)
	/*to display the elements using pre-order traver­sal*/
	{
	if ((root->left == NULL) && (root->right == NULL))
		printf("# %i #\n", root->data);
	if (root->left != NULL) //print left first
		preorder(root->left);
	if (root->right != NULL)
		preorder(root->right);
	}

	

int main(void)
	{
	struct tnode *pn = talloc(11);
	int input[] = {3, 1, 0, 2, 8, 6, 5, 9}, input_size, i;
	input_size = sizeof(input)/sizeof(int);
	for  (i = 0; i<input_size; i++)
		{
		printf("adding %i\n", input[i]);
		addnode(pn, input[i]);
		}
	preorder(pn);
	return 0;
	}
