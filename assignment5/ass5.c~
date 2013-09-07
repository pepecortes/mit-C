#include <stdio.h>
#include <stdlib.h>

struct node
	{
	int data;
	struct node *next;
	};
	
struct node* create(int val)
	/*
	create a struct node with an intial value
	*/
	{
	printf("...creating a new list\n");
	struct node *ptr = (struct node*)malloc(sizeof(struct node));
	if (ptr == NULL)
		return NULL;
	ptr->data = val;
	ptr->next = NULL;
	return ptr;
	}

void addback(struct node *head, int data)
	/*
	Add a node to the end of the list.
	"head" is not changed 
	*/
	{
	printf("...adding a new node\n");	
	struct node *ptr = head;
	while (ptr->next != NULL)
		{
		ptr = ptr->next; 
		}
	struct node *pnew = create(data);
	ptr->next = pnew;
	}
	
	
void display(struct node *head)
	{
	/*
	Displays all the elements of the list.
	*/
	int i = 0;
	printf("...displaying elements of list\n");
	struct node* ptr = head;
	do
		printf("element %i, data=%i\n", i++, ptr->data);
	while ((ptr = ptr->next) != NULL);
	}
	
struct node* find(struct node* head, int data)
	{
	/*
	Returns a pointer to the element in the list having the given data.
	The function should return NULL if the item does not exist.
	*/
	struct node* ptr = head;
	do
		{
		if (ptr->data == data)
			return ptr;
		}
	while ((ptr = ptr->next) != NULL);
	return NULL;
	}
	
struct node* delnode(struct node *head, struct node *pelement)
	{
	/*
	Deletes the element pointed to by pelement
	The function should return the up­dated head node.
	Make sure you consider the case when pelement points to the head node.
	*/
	struct node* ptr = head;
	if (pelement == head)
		{
		free(head);
		head = pelement->next;
		return head;
		}
	while ((ptr = ptr->next) != NULL)
		{
		if (ptr->next == pelement)
			ptr->next = pelement->next;
		}
	free(pelement);
	return head;
	}
	
void freelistRecursive(struct node *head)
	/*
	deletes all the element of the list.
	Make sure you do not use any pointer after it is freed.
	Do it recursively
	*/
	{
	struct node *nextNode = head->next;
	if (nextNode == NULL) //the list has only one element
		{
		free(head);
		return;
		}
	free(head);
	head = nextNode;
	freelistRecursive(head);
	}
	
int main(void)
	{
	struct node *pn = create(11);
	//struct node *pfound;
	addback(pn, 13);
	addback(pn, 22);
	addback(pn, 12);
	/*
	display(pn);
	pfound = find(pn, 22);
	printf("node found: %i\n", pfound->data);
	pn = delnode(pn, pfound);
	display(pn);
	pfound = find(pn, 11);
	pn = delnode(pn, pfound);
	*/
	display(pn);
	freelistRecursive(pn);
	display(pn);
	return 0;
	}
