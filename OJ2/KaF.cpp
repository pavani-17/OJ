#include <iostream>
#include <vector>

#define p 1000000007

using namespace std;

struct pi
{
	long long int v1;
	long long int v2;
	long long int cost;
};

long long int arr[100005],vis1[100005]={0},vis[100005]={0},sub0[100005],sub1[100005];

vector <int> gr[100005];
vector<pi> map;

long long int cal_sub (long long int node )
{
	long long int l,i;
	l = gr[node].size();

	vis[node]=1;
	sub0[node]=1;

	for(i=0;i<l;i++)
	{
		if(vis[gr[node][i]]==0)
		{
			sub0[node] += cal_sub(gr[node][i]);
		}
	}
	return sub0[node];
}

long long int cal_sub1 (long long int node )
{
	long long int l,i;
	l = gr[node].size();

	if (arr[node]==1)
		sub1[node] = 1;
	vis1[node]=1;
	
	for(i=0;i<l;i++)
	{
		if(vis1[gr[node][i]]==0)
			sub1[node] += cal_sub1(gr[node][i]);
	}
	return sub1[node];
}

	

int main()
{
	long long int i,n,a,b,w,l,n1=0,n2=0,res=0;
	cin >> n;
	for(i=0;i<n;i++)
	{
		cin >> arr[i];
		if(arr[i]==0)
			n1++;
		else
			n2++;

	}
	for(i=0;i<n-1;i++)
	{
		cin >> a >> b >> w;
		gr[a].push_back(b);
		gr[b].push_back(a);
		map.push_back({a,b,w});
	}
	cal_sub(0);
	cal_sub1(0);
	for(i=0;i<100005;i++)
	{
		sub0[i]-=sub1[i];
	}
	l = map.size();
	for(i=0;i<l;i++)
	{
		a = map[i].v1;
		b = map[i].v2;
		w = map[i].cost;
		if (sub0[a] < sub0[b])
			res = (res%p + (((sub0[a]%p)*((n1-sub0[a])%p)%p)*w)%p)%p;
		else
			res = (res%p + (((sub0[b]%p)*((n1-sub0[b])%p)%p)*w)%p)%p;

		if (sub1[a] < sub1[b])
			res = (res%p + (((sub1[a]%p)*((n2-sub1[a])%p)%p)*w)%p)%p;
		else
			res = (res%p + (((sub1[b]%p)*((n2-sub1[b])%p)%p)*w)%p)%p;
	}
	cout << res << "\n";
}
	






