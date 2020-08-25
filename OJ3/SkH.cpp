#include <iostream>
#include <vector>
#include <limits.h>
#include <stdlib.h>
#include <queue>

using namespace std;

struct node
{
	long long int vertex;
	long long int weight;
};

struct ver_dis
{
	long long int distance;
	long long int vertex;
	ver_dis(long long int distance, long long int vertex)
		: distance(distance), vertex(vertex)
	{
	}
};


struct CompareDistance 
{
    bool operator()(ver_dis const& v1, ver_dis const& v2)
    {
        return v1.distance > v2.distance;
    }
};


vector <node> graph[100005];

priority_queue <ver_dis, vector<ver_dis>, CompareDistance> q1;
priority_queue <ver_dis, vector<ver_dis>, CompareDistance> q2;

long long int A,B,V;
bool sptSet[100005], sptSet_new[100005];
long long int dist[100005];

void dijkstra (long long int src)
{
	long long int i,j,d,l,v,w;
	for(i=1;i<=V;i++)
	{
		dist[i] = INT_MAX;
		sptSet[i] = false;
	}

	dist[src] = 0;
	q1.push({0,src});
	q2.push({0,src});
	for(i=0;i<V;i++)
	{
		d = q1.top().vertex;
		if (dist[d] == INT_MAX)
			return;
		sptSet[d] =  true;
		q1.pop();
		l = graph[d].size();
		for(j=0;j<l;j++)
		{
			v = graph[d][j].vertex;
			w = graph[d][j].weight;
			
			if( !sptSet[v] && dist[v] > dist[d] + w && w <= A)
			{
				dist[v] = dist[d] + w;
				q1.push({dist[v],v});
				q2.push({dist[v],v});
			}
		}
	}
}


void dijkstra_new (long long int src)
{
	long long int i,j,d,l,v,w;
	for(i=1;i<=V;i++)
	{
		sptSet_new[i] = false;
	}

	for(i=0;i<V;i++)
	{
		d = q2.top().vertex;
		if (dist[d] == INT_MAX)
			return;
		sptSet_new[d] = true;
		l = graph[d].size();
		q2.pop();
		for(j=0;j<l;j++)
		{
			v = graph[d][j].vertex;
			w = graph[d][j].weight;

			if(!sptSet_new[v] && dist[v] > dist[d] + w && w >= B)
			{
				dist[v] = dist[d] + w;
				q2.push({dist[v],v});
			}
		}
	}
}


int main()
{
	long long int i,E,a,b,c,S,T;
	scanf("%lld%lld",&V,&E);
	for(i=0;i<E;i++)
	{
		scanf("%lld%lld%lld",&a,&b,&c);
		graph[a].push_back({b,c});
		graph[b].push_back({a,c});
	}
	scanf("%lld%lld%lld%lld",&S,&T,&A,&B);
	dijkstra(S);
	dijkstra_new(S);
	if (dist[T] == INT_MAX)
		printf("-1\n");
	else
		printf("%lld\n",dist[T]);
	return 0;
}




