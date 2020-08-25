#include <stdio.h>
#include <stdlib.h>

struct node *mid=NULL, *head=NULL;
struct node
{
	long long int n;
	struct node *prev, *next;
};


struct node* push (struct node* curr, long long int x)
{
	struct node* temp;
	temp = (struct node*)malloc(sizeof(struct node));
	temp->prev = curr;
	if(curr != NULL) curr->next=temp;
	temp->next = NULL;
	temp->n = x;
	return temp;
}

struct node* pop (struct node* curr)
{
	if(curr->prev != NULL)
	{
		curr->prev->next = NULL;
		curr = curr->prev;
		return curr;
	}
	else
	{
		return NULL;
	}
}

struct node* op ( struct node *curr, int size )
{
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp = mid;
	curr->next = head;
	head->prev = curr;
	mid->next->prev = NULL;
	if(size%2==0)
		mid = curr;
	else
		mid = curr->prev;
	head=temp->next;
	temp->next = NULL;
	return temp;
}


int main()
{
	int q,size=0;
	long long int x;
	char c;
	struct node *curr=NULL,*curr1=NULL;
	scanf("%d",&q);
	while(q--)
	{
		getchar();
		scanf("%c",&c);
		switch(c)
		{
			case 'a':
					scanf("%lld",&x);
					curr = push(curr,x);
					if(size==0)
					{
						curr->prev = NULL;
						head = curr;
						mid = curr;
					}
					size+=1;
					if(size%2==0)
					{
						if(size!=2)
							mid = mid->next;
					}
					break;

			case 't':
					curr = pop(curr);
					size-=1;
					if(size%2==1)
					{
						if(size!=1)
							mid = mid->prev;
						if(size==1)
							mid = head;
					}
					if(size==0)
					{
						head=NULL;
						mid = NULL;
					}
					break;

			case 'e':
					if( size!=0 && size!=1)
							curr = op(curr,size);
		}
		if(size==0)
                printf("0 ");
        curr1 = head;
        while(curr1!=NULL)
        {
                printf("%lld ",curr1->n);
                curr1 = curr1->next;
        }
        printf("\n");

	}
	if(size==0)
		printf("0 ");
	curr = head;
	while(curr!=NULL)
	{
		printf("%lld ",curr->n);
		curr = curr->next;
	}
	printf("\n");
	return 0;
}
