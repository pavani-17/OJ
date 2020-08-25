#include <iostream>
#include <vector>
#include <algorithm>

#define ll long long int
#define p 1000000007

using namespace std;

ll par[2005]; 
ll xor_val[2005];
ll size1 = 0;

ll power(ll a, ll b)
{
    ll ans = 1;
    while(b>0)
    {
        if(b%2==1)
        {
            ans = (ans*(a%p))%p;
        }

        b = b/2;
        a = (a*a)%p;
    }
    return ans;
}


ll root ( ll node )
{
    size1 ++ ;
    if (node == par[node])
    {
        return node;
    }
    else
    {
        ll parent = par[node];
        par[node] = root(parent);
        xor_val[node] = xor_val[node] ^ xor_val[parent];
        return (par[node]);
    }   
}

bool dsu(ll node1, ll node2, ll val)
{
    ll p1,p2,s1,s2;

    size1 = 0;
    p1 = root(node1);
    s1 = size1;

    size1 = 0;
    p2 = root(node2);
    s2 = size1;

    if ( p1 == p2 )
    {
        return 0;
    }
    else
    {
        if ( s1 < s2 )
        {
            par[p1] = p2;
            xor_val[p1] = val ^ xor_val[node1] ^ xor_val[node2];
        }
        else
        {
            par[p2] = p1;
            xor_val[p2] = val ^ xor_val[node1] ^ xor_val[node2];
        }
        return 1;        
    }
}

int main()
{
   ll n,m,k,i,a,b,w;
   ll val;
   scanf("%lld %lld %lld",&n,&m,&k);
   val = n + m - 1;
   for(i=0;i<2005;i++)
   {
       par[i] = i;
       xor_val[i] = 0;
   }
   int flag = 1;
   for(i=0;i<k;i++)
   {
       scanf("%lld %lld %lld",&a,&b,&w);
       if((dsu(a,b+n+1,w)))
       {
           val --;
       }
       else
       {
           if(!(((xor_val[a]^xor_val[b+n+1])^w)==0))
           {
               flag = 0;
           }
       }
   }
   ll res = power(2,30);
   res = power(res, val);
   if(flag==1)
   {
        printf("%lld\n",res);
   }
   else
   {
       printf("0\n");
   }
   
   return 0;
}