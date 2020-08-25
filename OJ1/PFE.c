#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node
{
	long double no;
	struct node* next;
};

struct node* push (struct node* curr, long double x)
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
	char str[800005];
	long long int T;
	int i,l,j,s,sum=0,p=0,k=-1;
	long double res;
	scanf("%lld",&T);
	getchar();
	while(T--)
	{
		scanf("%[^\n]s",str);
		curr = (struct node*)malloc(sizeof(struct node));
		l=strlen(str);
		s=0;
		if(str[l-1]!=' ')
		{
			str[l]=' ';
			s=1;
		}
		curr->next = NULL;
		k=-1;
		for(i=0;i<l+s;i++)
		{
			if(str[i]==' ')
			{
				if(i-k==2)
				{
					if(str[i-1]>='0' && str[i-1]<='9')
					{
						
						curr=push(curr,str[i-1]-'0');
					}
					else if(str[i-1]=='+')
					{
						res = (curr->next->no) + (curr->next->next->no);
						curr = pop(curr);
						curr = pop(curr);
						curr = push(curr,res);
					}
					else if(str[i-1]=='-')
                			{
                        			res = -(curr->next->no) + (curr->next->next->no);
                        			curr = pop(curr);
                        			curr = pop(curr);
                        			curr = push(curr,res);
                			}
					else if(str[i-1]=='*')
                			{
                        			res = (curr->next->no) * (curr->next->next->no);
                        			curr = pop(curr);
                        			curr = pop(curr);
                        			curr = push(curr,res);
               	 			}
					else if(str[i-1]=='/')
                			{
                        			res = (curr->next->next->no) / (curr->next->no);
                        			curr = pop(curr);
                        			curr = pop(curr);
                        			curr = push(curr,res);
                			}
				}
				else
				{
					sum=0;
					p=0;
					for(j=i-1;j>k;j--)
					{
						sum+=pow(10,p)*(str[j]-'0');
						p++;
					}
					curr=push(curr,sum);
				}
				k=i;
			}
		}
		printf("%Lf\n",curr->next->no);
		getchar();
	}
	
}




