#include <stdio.h>
#include <stdlib.h>

struct node
{
	int no;
	struct node* next;
};

struct node* push (struct node* curr, int x)
{
	curr->no = x;
	struct node *temp;
	temp = (struct node*)malloc(sizeof(struct node));
	temp->next = curr;
	return temp;
}

struct node* pop (struct node* curr)
{
	if(curr->next!=NULL)
	{	
		printf("Popped element : %d\n",curr->next->no);
		return curr->next;
	}
	else
	{
		printf("Stack empty\n");
		return NULL;
	}
}


void main()
{
	struct node* curr;
	curr = (struct node*)malloc(sizeof(struct node));
	int i;
	curr->next = NULL;
	for(i=0;i<10;i++)
	{
		curr=push(curr,i);
		curr=push(curr,i+1);
		curr=pop(curr);
	}
	while(curr!=NULL)
		curr=pop(curr);
}




