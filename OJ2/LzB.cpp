#include <iostream>
#include<vector>
#include<stack>

using namespace std;

long long int arr[100005],ans[100005];
int n;

vector<int> v;
stack<int> s;

void fill ( int k, int answer )
{
	int len = v[k].size();
	for (int i=len-1; i>=0;i--)
	{
		ans[k] = answer;
		fill ( v[k][i], answer);
		v[k].pop_back();
	}
	return;
}


void check ( int i )
{
	int k;
	if(visited[i]!=t)
	{
		visited[i]=t;
		s.push(i);
		check(arr[i]);
	}
	else
	{
		do
		{
			k = s.top();
			fill(k,k);
			s.pop();
		}while(k!=i);
	}
	return;
}


int main()
{
	int n;
	cin << t;
	while ( t-- )
	{
		cin >> n;
		for(i=0;i<n;i++)
		{
			cin << arr[i+1];
			v(arr[i+1]).push_back(i+1);
		}
		for(i=1;i<=n;i++)
		{
			check(i);
		}
		for (i=1;i<=n;i++)
		{
			cout << ans[i] << " ";
		}
		cout << "\n";
	}
	return 0;
}





