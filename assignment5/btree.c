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
		return new;
		}
	if (data < root->data)
		root->left = addnode(root->left, data);
	else
		root->right = addnode(root->right, data);
	return root;
	}
	
void preorder(struct tnode* root)
	/*to display the elements using pre-order traver­sal*/
	{
	printf("preorder->%i\n", root->data);
	if (root->left != NULL)
		preorder(root->left);
	if (root->right != NULL)
		preorder(root->right);
	}
	
void inorder(struct tnode* root)
	/*to display the elements using inorder traver­sal: sorted*/
	{
	if (root->left != NULL)
		inorder(root->left);
	printf("inorder->%i\n", root->data);
	if (root->right != NULL)
		inorder(root->right);
	}
	
int deltree(struct tnode* root)
	/*
	delete all the elements of the tree.
	The function must return the number of nodes deleted.
	Make sure not to use any pointer after it has been freed
	*/
	{
	int count = 0;
	if (root == NULL)
		return 0;
	count = deltree(root->left) + deltree(root->right);
	free(root);
	count++;
	return count;
	}

int main(void)
	{
	struct tnode *pn;
	int input[] = {3, 1, 0, 2, 8, 6, 5, 9}, input_size, i;
	//int input[] = {3, 1, 2}, input_size, i;
	input_size = sizeof(input)/sizeof(int);
	pn = talloc(input[0]);
	printf("adding %i\n", input[0]);
	for  (i = 1; i<input_size; i++)
		{
		printf("adding %i\n", input[i]);
		addnode(pn, input[i]);
		}
	preorder(pn);
	inorder(pn);
	printf("deleted %i nodes\n", deltree(pn));
	return 0;
	}
