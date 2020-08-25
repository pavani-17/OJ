#include <iostream>
#include <algorithm>
#include <set>
#include <limits.h>

using namespace std;


long long int arr[305][100005], dis[305],k,s=0,m;
bool sptSet[305]; 

set <int, greater <int> > map[305];

int minKey()
{
    long long int min= INT_MAX, min_index,i;
    for(i=0;i<m;i++)
    {
        if (dis[i] <= min  && sptSet[i]==false)
        {
            min = dis[i];
            min_index = i;
        }
    }
    return min_index;
}

void update(long long int a, long long int b)
{
    long long int min=INT_MAX;
    set <int, greater<int> > :: iterator i,j;
    for(i=map[a].begin();i!=map[a].end();i++)
    {
        for(j=map[b].begin();j!=map[b].end();j++)
        {
            //printf("%lld  %lld\n",*i,*j);
            long long int a = *i;
            long long int b = *j;
            long long int val = a^b;
            if ( val < min )
            {
                min = val;
            }
        }
    }
    if (min < dis[b])
    {
        dis[b] = min;
        //printf("Updated %lld to %lld \n",b,dis[b]);
    }
    return;
}

void prim ()
{
    long long int i,u,j;
    for(i=0;i<305;i++)
    {
        sptSet[i] = false;
        dis[i] = INT_MAX;
    }
    dis[0] = 0;
    for(i=0;i<m;i++)
    {

        /*for(j=0;j<m;j++)
        {
            printf("%lld  ",dis[j]);
        }*/

        u = minKey();
        s = s + dis[u];

        //printf("%lld  %lld  %lld \n",s,u,dis[u]);

        sptSet[u] = true;
        for(j=0;j<m;j++)
        {
            if(!sptSet[j])
                update(u,j);
        }

    }

    return ;
}



int main()
{
	long long int i,j;
	scanf("%lld%lld",&m,&k);
	for(i=0;i<m;i++)
	{
		for(j=0;j<k;j++)
		{
			scanf("%lld",&arr[i][j]);
		}
	}
	for(i=0;i<m;i++)
	{
		sort(arr[i],arr[i]+k,greater<long long int>());
	}
	for(i=0;i<m;i++)
	{
        	map[i].insert(arr[i][0]);
		for(j=1;j<m;j++)
		{
			arr[i][j] = __gcd(arr[i][j-1], arr[i][j]);
            		map[i].insert(arr[i][j]);
		}
	}

    /*set <int, greater<int> > :: iterator p;
    for(i=0;i<m;i++)
    {
        for(p=map[i].begin();p!=map[i].end();p++)
        {
            printf("%lld  ",*p);
        }
        printf("\n");
    }*/
	prim();
    printf("%lld\n",s);
}
