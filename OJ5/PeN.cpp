#include <iostream>
#include <cstring>

#define ll long long int

using namespace std;

char str[100005];
ll len;
char m[55];

struct node
{
    struct node* children[26];
};

struct node* createNode()
{
    struct node* temp = NULL;
    temp = (struct node*)malloc((sizeof(struct node)));

    if(temp)
    {
        int i;
        for(i=0;i<26;i++)
        {
            temp->children[i] = NULL;
        }
    }
    return temp;
}

void insert (struct node *root, char *key)
{
    ll i,length;
    length = strlen(key);
    struct node* temp = root;
    for(i=0;i<length;i++)
    {
        if(temp->children[key[i]-'a']==NULL)
        {
            temp->children[key[i]-'a'] = createNode();
        }
        temp = temp->children[key[i]-'a'];
    }
}

ll search (struct node* root, ll index)
{
    ll i,k=index-1;
    struct node* temp = root;
    for(i=index;i<len;i++)
    {
        if(temp->children[str[i]-'a']==NULL)
        {
            return k;
        }
        temp = temp->children[str[i]-'a'];
        k++;
    }
    return k;
}

int main()
{
    scanf("%s",str);
    ll i,k=0,p,n,j,prev,ans=0;
    len = strlen(str);
    struct node* root = createNode();
    scanf("%lld",&n);
    for(i=0;i<n;i++)
    {
        scanf("%s",m);
        insert(root,m);
    }
    i = 0;
    j = 0;
    prev = -1;
    k = 0;
    for(j=0;j<len;j++)
    {
        p = search(root,j);
        if(p > prev)
        {
            k = 1;
            prev = p;
        }
        if(j==i)
        {
            if(k==1)
            {
                i = prev + 1;
                ans++;
                k = 0;
            }
            else
            {
                printf("-1\n");
                return 0;
            }
        }
        if(i==(len))
        {
            break;
        }
    }
    printf("%lld\n",ans);
    return 0;
}