#include <iostream>
#include <deque>

using namespace std;

long long int a[100005], b[100005];

struct p
{
	long long int no;
	long long int s;
};

deque <p> q;

int main()
{
	long long int n,val=0,i;
	cin >> n;

	for(i=0;i<n;i++)
		cin >> a[i];
	
	for(i=0;i<n;i++)
		cin >> b[i];

	for(i=0;i<n;i++)
	{
		
		while(!q.empty() && q.back().no < b[i] && q.back().no <= a[i])
		{
			val += q.back().s;
			q.pop_back();
		}
		if(!q.empty() && q.back().no > a[i])
                {
                        while(!q.empty())
                        {
                                val += q.back().s;
                                q.pop_back();
                        }
                }
		while (!q.empty() && q.front().no > a[i])
		{
			val += q.front().s;
			q.pop_front();
		}
		if (!q.empty() && q.back().no == b[i])
		{
			if(q.back().s==0 && a[i]!=b[i])
				q.back().s=1;
			continue;
		}
		else if (a[i]==b[i])
			q.push_back({b[i],0});
		else
			q.push_back({b[i],1});
	}
	while(!q.empty())
	{
		val += q.back().s;
		q.pop_back();
	}
	cout << val  << "\n";
}


