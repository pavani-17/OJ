#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long int blob_size = 1;


long long int parent[200005], size[200005];

long long int root(long long int node)
{
	if (parent[node]==node)
		return node;
	else
		return (root(parent[node]));
}

void merge(long long int node1, long long int node2)
{
	long long int d1,d2,s1,s2;
	d1 = root(node1);
	d2 = root(node2);
	if(d1 != d2)
	{
		if ( size[d1] > size[d2] )
		{
			parent[d2] = d1;
			size[d1] += size[d2];
			if (size[d1] > blob_size)
				blob_size = size[d1];
		}
		else
		{
			parent[d1] = d2;
			size[d2] += size[d1];
			if (size[d2] > blob_size)
                                blob_size = size[d2];
		}
	}
}

int main()
{
	long long int m,n,a,b,s=0,i;
	cin >> n >> m;
	for(i=1;i<=n;i++)
	{
		parent[i] = i;
		size[i] = 1;
	}
	for(i=0;i<m;i++)
	{
		cin >> a >> b;
		merge(a,b);
		s += blob_size;
	}
	cout << s << "\n";
}








