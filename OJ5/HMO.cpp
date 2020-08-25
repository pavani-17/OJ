#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

#define ll long long int
#define p 1000000007

struct Node *root = NULL; 

ll P,Q,X;
ll st;

struct Node
{
    ll key;

    ll self_hash;
    ll left_hash;
    ll right_hash;

    int update;

    int el_less;
    int height;
    int freq;
    int size;

    struct Node *left;
    struct Node *right;
};

  
int h(struct Node *N) 
{ 
    if (N)
    {
        return N->height;
    } 
    else
    {
        return 0;
    }
} 
  
int max(int a, int b) 
{ 
    if(a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
    
} 

ll power(ll x, ll y)
{
    if(y<0LL)
    {
        x = power(x,p-2);
        y = -y;
    }
    x = x % p;
    ll ans = 1;
    while(y)
    {
        if(y&1LL)
        {
            ans = (ans*x)%p;
        }
        y=y/2LL;
        x=(x*x)%p;
    }
    return ans;
}

struct Node* newNode(ll key) 
{ 
    struct Node* node = (struct Node*)malloc(sizeof(struct Node)); 

    node->left_hash = 0;
    node->right_hash = 0;
    node->el_less = 1;
    node->height = node->el_less;

    node->left   = NULL; 
    node->right  = node->left; 

    node->update = 0;
    node->freq = 1;
    node->size = 1;
    node->key   = key; 
    
    st += node->el_less;
    node->self_hash = ((key%p)*(power(P,st)))%p;

    return(node); 
} 

void update (struct Node* node)
{
    if(node!=NULL && node->update)
    {
        node->self_hash = ((node->self_hash)*(power(P,node->update)))%p;
        node->right_hash = ((node->right_hash)*(power(P,node->update)))%p;
        node->left_hash = ((node->left_hash)*(power(P,node->update)))%p;
        if(node->left != NULL)
        {
            node->left->update += node->update; 
        }
        if(node->right != NULL)
        {
            node->right->update += node->update; 
        }
        node->update = 0;
    }
}
 
struct Node *rightRotate(struct Node *z) 
{ 
    struct Node *y, *T3;

    if(z)
    {
        y = z->left;
    }
    if(y)
    {
        T3 = y->right;
    }

    update(z);
    update(y);
    update(T3);


    y->right = z; 
    z->left = T3; 

 

    if(T3 != NULL)
    {
        z->left_hash = (((T3->left_hash + T3->right_hash)%p + T3->self_hash)%p);
    }
    else
    {
        z->left_hash = 0;
    }

    z->height = h(z->left) > h(z->right) ? (h(z->left)+1) : (h(z->right)+1);
    y->height = h(y->left) > h(y->right) ? (h(y->left)+1) : (h(y->right)+1);

    if(T3!=NULL)
    {
        z->size = z->size - y->size + T3->size;
        z->el_less = z->freq + T3->size;
    }
    else
    {
        z->size = z->size - y->size;
        z->el_less = z->freq;
    } 

    y->size = y->el_less + z->size;     
    
    y->right_hash = ((z->left_hash + z->right_hash)%p + z->self_hash)%p;
  
    return y; 
} 
  

struct Node *leftRotate(struct Node *z) 
{
    struct Node *y, *T2;
    if(z!=NULL)
    {
        y = z->right;
    } 
    if(y)
    {
        T2 = y->left;
    } 

    update(z);
    update(y);
    update(T2);
  
    y->left = z; 
    z->right = T2; 

    if(T2!=NULL)
    {
        z->right_hash = ((T2->left_hash + T2->right_hash)%p + T2->self_hash)%p;
    }
    else
    {
        z->right_hash = 0;
    }

    y->left_hash = ((z->left_hash + z->right_hash)%p + z->self_hash)%p;

            
    z->height = h(z->left) > h(z->right) ? (h(z->left)+1) : (h(z->right)+1);
    y->height = h(y->left) > h(y->right) ? (h(y->left)+1) : (h(y->right)+1);

    
    if(T2!=NULL)
    {
        z->size = z->size - y->size + T2->size;
        y->size = y->size - T2->size + z->size;
    }
    else
    {
        z->size = z->size - y->size;
        y->size = y->size + z->size;
    }
    y->el_less = y->freq + z->size;
  
    return y; 
}
  
struct Node* insert(struct Node* node, ll key)
{ 
    if (node == NULL) 
        return(newNode(key)); 
    node->size++;
    update(node);

    if (key < node->key) 
    {
        if(node->right!=NULL)
        {
            node->right->update ++;
        }
        node->el_less ++;
        node->left  = insert(node->left, key);
        node->right_hash = ((node->right_hash)*P)%p;
        node->self_hash = ((node->self_hash)*P)%p;
        node->left_hash = ((node->left->left_hash + node->left->right_hash)%p + node->left->self_hash)%p;
    } 
    else if (key > node->key) 
    {
        st += node->el_less;
        node->right = insert(node->right, key);
        node->right_hash = ((node->right->left_hash + node->right->self_hash)%p + node->right->right_hash)%p; 
    }
    else
    {
        node->el_less ++;
        st += node->el_less;
        node->freq ++;
        node->self_hash = ((((node->key)*power(P,st))%p)*node->freq)%p;
        node->right_hash = (node->right_hash*P)%p;
        if(node->right!=NULL)
        {
            node->right->update++;
        }
        return node;
    } 

    node->height = 1 + max(h(node->left), h(node->right)); 

    int balance;
    if(node==NULL)
    {
        balance = 0;
    }
    else
    {
        balance = h(node->left) - h(node->right);
    }
    
    if (balance > 1)
    {
        if(key < node->left->key)
        { 
            return rightRotate(node);
        } 
  
        else if (key > node->left->key) 
        { 
            node->left =  leftRotate(node->left); 
            return rightRotate(node); 
        } 
    }
      
    else if (balance < -1)
    {
        if(key > node->right->key)
        {
            return leftRotate(node);
        } 
        else if (key < node->right->key) 
        { 
            node->right = rightRotate(node->right); 
            return leftRotate(node); 
        } 
    }
    update(node);
    return node; 
} 

bool findElement (struct Node* node, ll key)
{
    if(node==NULL)
    {
        return false;
    }
    if (node->key < key)
    {
        return findElement(node->right,key);
    }
    else if(node->key > key)
    {
        return findElement(node->left,key);
    }
    else
    {
        return true;
    }
    
}

struct Node * minNode(struct Node* node) 
{ 
    update(node);
    if(node->left==NULL)
    {
        return node;
    } 
    else
    {   
        //node->self_hash = (node->self_hash*P)%p;
        return minNode(node->left);
    }
} 
  
struct Node* deleteNode(struct Node* node, ll key) 
{
    if (node == NULL) 
        return node; 
    node->size--;
    update(node);

    if ( key < node->key )
    { 
        if(node->right!=NULL)
        {
            node->right->update --;
        }
        node->el_less --;
        node->left = deleteNode(node->left, key);
        node->right_hash = ((node->right_hash)*power(P,p-2))%p;
        node->self_hash = ((node->self_hash)*power(P,p-2))%p;
        if(node->left != NULL)
        {
            node->left_hash = ((node->left->left_hash + node->left->right_hash)%p + node->left->self_hash)%p;
        } 
        else
        {
            node->left_hash = 0;
        }
        
    }
    else if( key > node->key ) 
    {
        node->right = deleteNode(node->right, key);
        if(node->right!=NULL)
        {
            node->right_hash = ((node->right->left_hash + node->right->self_hash)%p + node->right->right_hash)%p; 
        }
        else
        {
            node->right_hash = 0;
        }
        
    }
    else
    { 
        node->el_less --;
        node->freq--;
        if(node->right!=NULL)
        {
            node->right->update--;
        } 
        if(node->freq==0)
        {
            if(node->left == NULL && node->right == NULL)
            {
                struct Node *temp;
                temp = node;
                node = NULL;
                free(temp);
            }
            else if( (node->left == NULL) ^ (node->right == NULL) ) 
            { 
                struct Node *temp;
                if(node->left)
                {
                    temp = node->left;
                } 
                else
                {
                    temp = node->right;
                } 
                *node = *temp;  
                free(temp); 
            } 
            else
            { 
                node->right->update++;
                struct Node* temp = minNode(node->right);
                update(temp); 
                temp->self_hash = (temp->self_hash*power(P,p-2))%p;
                node->self_hash = temp->self_hash;
                node->freq = temp->freq;
                temp->freq = 1;
                node->el_less ++;
                node->key = temp->key;
                node->right = deleteNode(node->right, temp->key);
                if(node->right!=NULL)
                {
                    node->right_hash = ((node->right->left_hash + node->right->self_hash)%p + node->right->right_hash)%p; 
                }
                else
                {
                    node->right_hash = 0;
                }
            }
        }
        else
        {
            node->self_hash = (((((node->self_hash*node->freq)%p)*power(node->freq+1,p-2))%p)*power(P,p-2))%p;
            node->right_hash = ((node->right_hash*power(P,p-2)))%p;
            return node;
        }
         
    } 
   
    if (node == NULL) 
      return node; 
   
    node->height = 1 + max(h(node->left), h(node->right)); 
  
    int balance, left_balance, right_balance;
    
    if(node==NULL)
    {
        balance = 0;
    }
    else
    {
        balance = h(node->left) - h(node->right);
    }

    if(node->right==NULL)
    {
        right_balance = 0;
    }
    else
    {
        right_balance = h(node->right->left) - h(node->right->right);
    }

    if(node->left==NULL)
    {
        left_balance = 0;
    }
    else
    {
        left_balance = h(node->left->left) - h(node->left->right);
    }
    
  
    if (balance > 1)
    {
        if(left_balance >= 0) 
        {
            return rightRotate(node);
        }
        else if(left_balance<0)
        {
            node->left =  leftRotate(node->left); 
            return rightRotate(node); 
        } 
    }

    else if (balance < -1)
    {
        if(right_balance <= 0) 
        {
            return leftRotate(node); 
        }
        else if(right_balance > 0)
        {
            node->right = rightRotate(node->right); 
            return leftRotate(node); 
        }
    } 
    update(node);  
    return node; 
} 

int main() 
{ 
    char a;
    ll b,i;
    vector <ll> hi;
    scanf("%lld %lld %lld",&Q,&P,&X);
    while(Q--)
    {
        cin >> a;
        st = 0;
        //printf("%d\n",Q);
        if(a =='A' || a=='D')
        {
            cin >> b;
        }
        if(a =='A')
        {
            root = insert(root,b);
        }
        else if (a =='D')
        {
            if(findElement(root,b))
            {
                root = deleteNode(root,b);
            }
        }
        else
        {
            update(root);
            if(root!=NULL)
            {
                hi.push_back(((root->self_hash + root->left_hash)%p + root->right_hash)%p);
            }
            else
            {
                hi.push_back(0);
            }    
        }
    }
    ll l = hi.size();
    ll ans = 1;
    for(i=0;i<l;i++)
    {
        ans = (ans*power(X,hi[i]))%p;
    }
    printf("%lld\n",ans);
    return 0; 
}