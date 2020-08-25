#include <stdio.h>

void main()
{
	long long int n,i,arr[1000005],ml=0,mr=0,l=0,r=0,sum=0;
	scanf("%lld",&n);
	for(i=0;i<n;i++)
	{
		scanf("%lld",&arr[i]);
	}
	r=n-1;
	ml=arr[0];
	mr=arr[n-1];
	while(l<r)
	{
		if(arr[l]<arr[r])
		{
			if(ml<arr[l])
				ml=arr[l];
			sum+=ml;
			l++;
		}
		else
		{
			if(mr<arr[r])
				mr=arr[r];
			sum+=mr;
			r--;
		}
	}
	printf("%lld\n",sum);
}

