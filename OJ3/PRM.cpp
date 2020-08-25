#include <vector>
#include <iostream>
#include <algorithm>
#include <limits.h>

#define INF 1e15 

using namespace std;

struct node
{
    long long int weight;
    int v1;
    int v2;
};

long long int dis_en[1005], dis_st[1005];
int main()
{
    long long int t,n,m,a,b,i,j,l;
    long long int w;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&n,&m);
        vector <node> start;
        vector <node> finish;

        for(i=0;i<=n;i++)
        {
            dis_st[i] = 0;
            dis_en[i] = 0;
        }
        for(i=0;i<m;i++)
        {
            scanf("%lld %lld %lld",&a,&b,&w);
            start.push_back({w,a,b});
            finish.push_back({w,b,a});
        }

        for(i=0;i<2*n;i++)
        {
            for(j=0;j<m;j++)
            {
                w = start[j].weight;
                a = start[j].v1;
                b = start[j].v2;
                if((dis_st[a]+w < dis_st[b]))
                {
                       dis_st[b] = dis_st[a] + w;
                }
                w = finish[j].weight;
                a = finish[j].v1;
                b = finish[j].v2;
                if((dis_en[a]+w < dis_en[b]))
                {
                    dis_en[b] = dis_en[a] + w;
                }
            }
        }

        for(i=0;i<2*n;i++)
        {
            for(j=0;j<m;j++)
            {
                w = start[j].weight;
                a = start[j].v1;
                b = start[j].v2;
                if((dis_st[a]+w < dis_st[b]))
                {
                       dis_st[b] = -INF;
                }
                w = finish[j].weight;
                a = finish[j].v1;
                b = finish[j].v2;
                if((dis_en[a]+w < dis_en[b]))
                {
                    dis_en[b] = -INF;
                }
            }
        }

        for(i=1;i<=n;i++)
        {
            if(dis_en[i]==-INF || dis_st[i]==-INF)
            {
                printf("INF\n");
            }
            else
            {
                printf("%lld\n",dis_st[i]+dis_en[i]);
            }
        }
    }
    return 0;
}
