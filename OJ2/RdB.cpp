#include <vector>
#include <iostream>

using namespace std;

struct gr
{
	long long int vertex;
	long long int price;
};

vector <gr> map[100005];
int visited[100005];
long long int sum=1;

void dfs (long long int node, long long int cost)
{
	long long int i,l;
	visited[node]=1;
	//printf("Started\n");
	//printf("Reached2\n");
	l = map[node].size();
	//cout << l; 
	for(i=0;i<l;i++)
	{
		//printf("Loop started");
		if(visited[map[node][i].vertex]==0 && (map[node][i].price)<=cost)
		{
			dfs(map[node][i].vertex,cost);
			sum++;
		}
	}
	return;
}
	


long long int check(long long int var, long long int n)
{
	long long int i,j=0,res=0,k,pres=0;
	for(i=0;i<100005;i++)
	{
		visited[i]=0;
	}
	//printf("Reached1\n");
	for(i=1;i<=n;i++)
	{
		sum=1;
		if(visited[i]==0)
		{
			//cout << i << "\n";
			dfs(i,var);
			//cout << "Done";
			res+=pres*sum;
			pres+=sum;
		}
	}
	return res;
}


int main()
{
	long long int n,m,i,j,a,b,c,max=0,min,mid,k1,k2,l;
	cin >> n >> m;
	for(i=0;i<m;i++)
	{
		cin >> a >> b >> c;
		map[a].push_back({b,c});
		map[b].push_back({a,c});
		if(c > max)
			max = c;
	}
	cin >> j;
	min = 1;
	mid = min + (max-min)/2;
	while(min < max)
	{
	/*	//printf("Reached\n");
		if(mid!=1)		
			k1 = check(mid-1,n);
		else
			k1 = m*(m-1)/2;
		//printf("k1 is %lld\n",k1);
		k2 = check(mid,n);
		//printf("k2 is %lld\n",k2);
		if( (k1>j) && (k2<=j))
			break;*/
		k2=check(mid,n);
		if (k2 > j)
			min = mid + 1;
		else
			max = mid;

		mid = min + (max-min)/2;
	}	
	cout << mid << "\n"; 
}
		
	





