#include <iostream>
#include <vector>
#include <algorithm>

#define ll long long int
#define p 1000000007

ll arr[100005];

using namespace std;

struct node
{
    struct node *children[2];
    int n;
    int un;
};

ll power(int b)
{
    ll ans = 1;
    ll a = 100000000;
    while(b>0)
    {
        if(b&1)
        {
            ans = (ans*a)%p;
        }
        a =(a*a)%p;
        b = b/2;
    }
    return ans;
}

struct node* getNode()
{
    struct node* temp = NULL;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->children[0] = NULL;
    temp->children[1] = NULL;
    temp->n = 0;
    temp->un = 0;
    return temp;
}

bool find (struct node* root, int temp)
{
    struct node *pCrawl = root;
    int i;
    bool index;
    for (i = 0; i <= 30; i++)
    {
        index = (temp)&(1<<(30-i));
        if (pCrawl->children[index]==NULL)
        {
            return false;
        }
        pCrawl = pCrawl->children[index];
    }
    return true;
}

int findFreq (struct node* root, int temp)
{
    struct node *pCrawl = root;
    int i;
    bool index;
    for (i = 0; i <= 30; i++)
    {
        index = (temp)&(1<<(30-i));
        pCrawl = pCrawl->children[index];
    }
    return pCrawl->n;
}

void insertNode(struct node *root,int temp)
{
    int i;
    bool index;
    bool un = find(root,temp);
    struct node *pCrawl = root;
 
    for (i = 0; i <= 30; i++)
    {
        index = (temp)&(1<<(30-i));
        if (pCrawl->children[index]==NULL)
        {
            pCrawl->children[index] = getNode();
        }
        pCrawl->n ++;
        pCrawl->un += !un;
        pCrawl = pCrawl->children[index];
    }
    pCrawl->n ++;
    pCrawl->un += !un;
}

void deleteNode(struct node* root, int temp)
{
    int i;
    bool index;
    
    struct node *pCrawl = root;
    
    int freq = findFreq(root,temp);
    for(i=0;i<=30;i++)
    {
        index = (temp)&(1<<(30-i));
        pCrawl->children[index]->n--;
        if(freq==1)
        {
            pCrawl->children[index]->un--;
        }
        if(pCrawl->children[index]->n==0)
        {
            free(pCrawl->children[index]);
            pCrawl->children[index] = NULL;
            return;
        }
        pCrawl = pCrawl->children[index];
    }
    pCrawl->n--;
    if(freq==1)
    {
        pCrawl->un--;
    }
}

int mex (struct node* root, int x)
{
    struct node* temp = root;
    int ans = 0,i;
    bool val;
    for(i=0;i<=30;i++)
    {
        val = (x&(1<<(30-i)));
        if(temp->children[val]==NULL)
        {
            return ans;
        }
        else if(temp->children[val]->un != (1<<(30-i)))
        {
            temp = temp->children[val];
        }
        else if(temp->children[!val]==NULL)
        {
            ans += (1<<(30-i));
            return ans;
        }
        else
        {
            ans += (1<<(30-i));
            temp = temp->children[!val];
        }
    }
    return ans;
}

int main()
{
    int n,q,i,a,b,x=0;
    ll ans=1;
    struct node* root;
    root = getNode();
    scanf("%d %d",&n,&q);
    for(i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
        insertNode(root,arr[i]);
    }
    for(i=0;i<q;i++)
    {
        scanf("%d",&a);
        if(a==1)
        {
            scanf("%d",&a);
            x = x^a;
            b = mex(root,x);
            ans = (ans*power(b))%p;
        }
        else
        {
            scanf("%d %d",&a,&b);
            deleteNode(root,arr[a-1]);
            insertNode(root,b^x);
            arr[a-1] = b^x;
            b = mex(root,x);
            ans = (ans*power(b))%p;
        }
    }
    printf("%lld\n",ans);
}