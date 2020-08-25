#include <stdio.h>
#include <stdlib.h>

long long int arr[1000005],L[1000005],R[1000005],temp[1000005],temp1[1000005]; 

void main()
{
	long long int i,n,max,res,k=0;
	scanf("%lld",&n);
	for(i=0;i<n;i++)
	{
		scanf("%lld",&arr[i]);
	}
	for(i=0;i<n;i++)
	{
		if(i==0)
		{
			L[i]=0;
			temp[k]=arr[i];
			k++;
		}
		else
		{
			while(temp[k-1]<=arr[i] && k>0)
			{
				k--;
			}
			if(k==0)
				L[i]=0;
			else
				L[i]=temp[k-1];
			temp[k]=arr[i];
			k++;
		}
	}
	k=0;
	for(i=n-1;i>=0;i--)
	{
		if(i==n-1)
		{
			R[i]=0;
			temp1[k]=arr[i];
			k++;
		}
		else
		{
			while(temp1[k-1] <= arr[i] && k>0)
			{
				k--;
			}
			if(k==0)
				R[i]=0;
			else
				R[i]=temp1[k-1];
			temp1[k]=arr[i];
			k++;
		}
	}
	max = L[0]*R[0];
	for(i=1;i<n;i++)
	{
		res=L[i]*R[i];
		if(res>max)
			max=res;
	}
	printf("%lld\n",max);
}






