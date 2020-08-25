#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <climits>

#define ll long long int

using namespace std;

ll par[100005];
ll size1 = 0;

struct node
{
    ll vertex1;
    ll vertex2;
    ll potato;
    ll cost;
};

vector <node> graph[25];


ll res = pow(2,60)-1;

bool compareCost (const node &v1, const node &v2)
{
    return v1.cost < v2.cost;
}

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
        return 0;
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
        return 1;
    }
    
}

ll kruskal (ll V)
{
    ll i;
    ll e=0;
    int flag = 0;
    for(ll j=0;j<20;j++)
    {
        e = 0;
        ll ans = 0;
        for(i=0;i<100004;i++)
        {
            par[i] = i;
        }
        ll l = graph[j].size();
        i = 0;
        while( (e < (V - 1)) && i < l)
        {
            ll v1 = graph[j][i].vertex1;
            ll v2 = graph[j][i].vertex2;
            if(dsu(v1,v2))
            {
                ans += graph[j][i].cost;
                e++;
            }
            i++;
        }
        if (e == (V-1))
        {
            if(ans<res)
            {
                res = ans;
                flag = 1;
            }
        }
    }
    if(flag==1)
    {
        return res;
    }
    else
    {
        return -1;
    }
}

int main()
{
    ll n,m,i,a,b,c,d,x;
    ll one = 1;
    scanf("%lld %lld %lld",&n,&m,&x);
    ll t;
    t=-1;
    for(i=0;i<20;i++)
        if((1<<i) & x) t=i;
    vector <int> b_x;
    for(i=t-1;i>=0;i--)
    {
        if(x&(one<<i))
        {
            b_x.push_back(i);
        }
    }
    ll l2 = b_x.size();
    
    for(ll k=0;k<m;k++)
    {
        scanf("%lld %lld %lld %lld",&a,&b,&c,&d);
        if(c&((one<<t)))
        {
            i = 0;
            for(ll j = t-1; j >=0; j--)
            {
                if(i<l2 && b_x[i]==j)
                {
                    if(b_x[i]==j)
                    {
                        if(c&(one<<(j)))
                        {
                            continue;
                        }
                        else
                        {
                            break;
                        }
                        i++;
                    }
                    else if(c&(one<<j))
                    {
                        graph[j].push_back({a,b,c,d});
                    }  
                }  
                else
                {
                    if(c&(one<<j))
                    {
                        graph[j].push_back({a,b,c,d});
                    }
                }
                
            }
        }
        for(ll j=t+1; j < 20;j++)
        {
            if (c&((one<<j)))
            {
                graph[j].push_back({a,b,c,d});
            }            
        }
    }
    for(i=0;i<20;i++)
    {
        sort(graph[i].begin(), graph[i].end(), compareCost);
    }
    ll final = kruskal(n);
    printf("%lld\n",final);
    return 0;
}