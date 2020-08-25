#include <iostream>
#include <vector>
#include <algorithm>

#define ll long long int
#define p 1000000007

using namespace std;

struct node
{
    ll x;
    ll y;
    ll v;
};

struct nodex
{
    ll x1;
    ll ind;
};

struct nodey
{
    ll y1;
    ll ind;
};

bool compareX (const nodex &c1, const nodex &c2)
{
    return (c1.x1 < c2.x1);
}

bool compareY (const nodey &c1, const nodey &c2)
{
    return (c1.y1 < c2.y1);
}


vector <node> graph;
vector <nodex> graphx;
vector <nodey> graphy;


ll par[3000005]; 
ll xor_val[3000005];
ll size1 = 0;

ll power1(ll a, ll b)
{
    ll ans = 1;
    b = b;
    a = a%(p-1);
    while(b>0)
    {
        if(b%2==1)
        {
            ans = (ans*a)%(p-1);
        }

        b = b/2;
        a = (a*a)%(p-1);
    }
    return ans;
}

ll power(ll a, ll b)
{
    ll ans = 1;
    a = a%p;
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
    ll z;
    ll val;
    scanf("%lld %lld %lld %lld",&n,&m,&k,&z);
    val = n + m - 1;
    for(i=0;i<3000005;i++)
    {
        par[i] = i;
        xor_val[i] = 0;
    }


    for(i=0;i<k;i++)
    {    
        scanf("%lld %lld %lld",&a,&b,&w);
        graph.push_back({a,b,w});
        graphx.push_back({a,i});
        graphy.push_back({b,i});
    }

    sort(graphx.begin(),graphx.end(),compareX);
    sort(graphy.begin(),graphy.end(),compareY);

    ll key_x = 0, key_y = 0;

    for(i=0;i<k;i++)
    {
        if(i==0)
        {
            graph[graphx[i].ind].x = key_x;
            graph[graphy[i].ind].y = key_y + 1000005;
        }
        else
        {
            if(graphx[i-1].x1 == graphx[i].x1)
            {
                graph[graphx[i].ind].x = key_x;
            }
            else
            {
                key_x++;
                graph[graphx[i].ind].x = key_x;
            }
            if(graphy[i-1].y1 == graphy[i].y1)
            {
                graph[graphy[i].ind].y = key_y + 1000005;
            }
            else
            {
                key_y++;
                graph[graphy[i].ind].y = key_y + 1000005;
            }   
        }
        
    }
    
    int flag = 1;
    ll ans = 1,res;
    for(i=0;i<k;i++)
    {
        a = graph[i].x;
        b = graph[i].y;
        w = graph[i].v;
        if((dsu(a,b,w)))
        {
            val --;
        }
        else
        {
            if(!(((xor_val[a]^xor_val[b])^w)==0))
            {
                flag = 0;
            }
        }
        res = power1(2,30);
        res = power1(res, val);
        if(flag==0)
        {
            res = 0;
        }
        ans = (ans*power(z,res))%p; 
        //printf("%lld %lld\n",res,ans);
    }
    printf("%lld \n",ans);
    
    return 0;
}