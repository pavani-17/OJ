#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <functional>


using namespace std;

#define ll long long int


int visited[1000005];

ll indegree[1000005];

vector <ll> graph[1000005];

vector <ll> s;

int main()
{
    ll k,n,i,j,l,flag,temp,l1,l2,m=0;
    scanf("%lld %lld",&n,&k);
    for(i=1;i<=k;i++)
    {
        indegree[i] = 0;
    }
    vector <ll> arr[n];
    vector <ll> t;
    for(i=0;i<n;i++)
    {
        scanf("%lld",&l);
        for(j=0;j<l;j++)
        {
            scanf("%lld",&temp);
            arr[i].push_back(temp);            
        }
        if(i)
        {
            l1 = arr[i].size();
            l2 = arr[i-1].size();
            j = 0;
            flag = 0;
            while(j<l1 && j<l2)
            {
                if(arr[i][j] != arr[i-1][j])
                {
                    graph[arr[i-1][j]].push_back(arr[i][j]);
                    indegree[arr[i][j]]++;
                    flag = 1;
                    break;
                }
                j++;
            }
            if(flag==0)
            {
                if(l1<l2)
                {
                    m = 1;
                }
            } 
        }
    }
    if(m)
    {
        printf("-1\n");
        return 0;
    }
    for(i=1;i<=k;i++)
    {
        if(indegree[i]==0)
        {
            t.push_back(i);
            visited[i] = 1;
        }
    }
    make_heap(t.begin(),t.end(), greater<ll>{});
    while(t.size()!=0)
    {
        pop_heap(t.begin(),t.end(), greater<ll>{});
        temp = t.back();
        visited[temp] = 1;
        s.push_back(temp);
        t.pop_back();
        l = graph[temp].size();
        for(i=0;i<l;i++)
        {
            if(!visited[graph[temp][i]])
            {
                indegree[graph[temp][i]]--;
                if(indegree[graph[temp][i]]==0)
                {
                    t.push_back(graph[temp][i]);
                    visited[graph[temp][i]] = 1;
                }
            }
        }
        make_heap(t.begin(), t.end(), greater<ll>{});
    }
    for(i=1;i<=k;i++)
    {
        if(indegree[i])
        {
            printf("-1\n");
            return 0;
        }
    }
    l = s.size();
    for(i=0;i<l;i++)
    {
        printf("%lld ",s[i]);
    }
    printf("\n");
    return 0;
}