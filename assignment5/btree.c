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
	

int main(void)
	{
	struct tnode *pn = talloc(11);
	return 0;
	}
