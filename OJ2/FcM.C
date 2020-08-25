#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> arr[100005];
	int m,n,mx=0,i,a,b,len,j,t;
	int cmp[100005],maxi[100005]={0},temp[100005]={0};
	cin >> n >> m;
	for(i=0;i<n;i++)
	{
		cin >> cmp[i];
	}
	for(i=0;i<m;i++)
	{
		cin >> a >> b;
		arr[cmp[a-1]].push_back(b);
		arr[cmp[b-1]].push_back(a);
	}
	for(i=0;i<100005;i++)
	{
		len = arr[i].size();
		temp[i]=1;
		for(j=0;j<len;j++)
		{
			t=arr[i][cmp[j-1]];
			if(temp[t]==0)
			{
				temp[t]=1;
				maxi[i+1]++;
			}
		}
		if(maxi[i+1]>mx)
			mx=maxi[i+1];
		for(j=0;j<len;j++)
		{
			t=arr[i][cmp[j-1]];
			if(t==1)
			{
				temp[t]=0;
			}
		}
		temp[i]=0;
	}
	for(i=1;i<100005;i++)
	{
		if(maxi[i]==mx)
		{
			cout << i << "\n";
			break;
		}
	}
	return 0;
}

				
		





