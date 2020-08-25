#include <iostream>
#include <vector>

#define ll long long int
#define p 1000000007

using namespace std;

int par[100005];

ll size1 = 0;
ll cnt = 0;

ll root (ll node)
{
    size1++;
    if(node==par[node])
    {
        return node;
    }
    else
    {
        return root(par[node]);
    }
}

bool dsu (ll node1, ll node2)
{
    size1 = 0;
    ll p1 = root(node1);
    ll s1 = size1;
    size1 = 0;
    ll p2 = root(node2);
    ll s2 = size1;
    if(p1==p2)
    {
        return 1;
    }
    else
    {
        if(s1 > s2)
        {
            par[p2] = p1; 
        }
        else
        {
            par[p1] = p2;
        }
        return 0;
    }
    
}

int main()
{
    ll n,m,i,a,b;
    scanf("%lld %lld",&n,&m);
    for(i=0;i<=n;i++)
    {
        par[i] = i;
    }
    for(i=0;i<m;i++)
    {
        scanf("%lld %lld",&a,&b);
        if(dsu(a,b))
        {
            cnt = ((2*cnt)%p + 1)%p;
        }
        printf("%lld\n",cnt);
    }
    return 0;
}
