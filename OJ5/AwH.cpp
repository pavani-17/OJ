#include <iostream>
#include <vector>
#include <algorithm>

#define ll long long int

using namespace std;

vector <ll> graph[100005];
vector <ll> prefix[100005];

ll calc (ll n, ll x, ll h)
{
    printf("%lld\n",h);
    ll i,l,j,ans=0;
    vector <ll> sel;
    for(i=0;i<n;i++)
    {
        l = graph[i].size();
        if(l<h)
        {
            for(j=0;j<l;j++)
            {
                sel.push_back(graph[i][j]);
            }
        }
        else
        {
            ans += prefix[i][l-h];
            x += l - h + 1;
            for(j=l-h+1;j<l;j++)
            {
                sel.push_back(graph[i][j]);
            }
        }
    }
    if(x>=h)
    {
        return ans;
    }
    else
    {
        sort(sel.begin(), sel.end());
        i = 0;
        while(x<h)
        {
            ans += sel[i];
            i++;
            x++;
        }
        return ans;
    }    
}

int main()
{
    ll n,x,i,l,max=0,j,a,min,avg1,avg2,temp1,temp2;
    scanf("%lld %lld",&x,&n);
    for(i=0;i<n;i++)
    {
        scanf("%lld",&l);
        if(max<l)
        {
            max = l;
        }
        for(j=0;j<l;j++)
        {
            scanf("%lld",&a);
            graph[i].push_back(a);
        }
        sort(graph[i].begin(), graph[i].end());
        a = 0;
        for(j=0;j<l;j++)
        {
            a += graph[i][j];
            prefix[i].push_back(a);
        }
    }
    if(x>max)
    {
        printf("0\n");
        return 0;
    }
    else
    {
        min = x;
        max = max+1;
        while((max-min)>4)
        {
            avg1 = (max+min)/2;
            avg2 = avg1 + 1;
            temp1 = calc(n,x,avg1);
            temp2 = calc(n,x,avg2);
            if(temp1<=temp2)
            {
                max = avg2;
            }
            else
            {
                min = avg1;
            }
        }
        if(min==0)
        {
            min = 1;
        }
        avg1 = calc(n,x,min);
        for(i=min;i<=max;i++)
        {
            a = calc(n,x,i);
            if(a<avg1)
            {
                avg1 = a;
            }
        }
        printf("%lld\n",avg1);
    }
    return 0;
}