#include <iostream>
#include <vector>

using namespace std;


long long int sum=0,q;
int visited[100005]={0};

struct pre
{
	long long int vertex;
	long long int cost;
};

vector<pre> map[100005];
long long int del[100005],del1[100005];

long long int binser(long long int l, long long int r, long long int x){

	long long int g,ans,l1,r1;
	r1 = q-l-1;
	l1 = q-r-1;
	g= l1 + (r1-l1)/2;
	while(l1<r1){
		if(del1[g]<=x)
			l1=g+1;
		else{
			r1=g;
		}
		g=l1 + (r1-l1)/2;

	}
	if(del1[g]>x)
		return (q-g-1);
	else 
		return -1;
}

void merge(long long int l, long long int m, long long int r)
{
	long long int i,j,k;
	
	long long int n1 = m-l+1;
	long long int n2 = r-m;

	long long int L[n1];
	long long int R[n2];

	for(i=0;i<n1;i++)
	{
		L[i] = del[l+i];
	}
	for(j=0;j<n2;j++)
	{
		R[j] = del[m+1+j];
	}
	
	i=0;
	j=0;
	k=l;

	while ( i<n1 && j<n2 )
	{
		if (L[i] > R[j] )
		{
			del[k] = L[i];
			i++;
			k++;
		}
		else
		{
			del[k] = R[j];
			j++;
			k++;
		}
	}

	while (i<n1)
	{
		del[k] = L[i];
		i++;
		k++;
	}

	while (j<n2)
	{
		del[k] = R[j];
		j++;
		k++;
	}
}



void mergeSort ( long long int l, long long int r )
{
	if( l < r )
	{
		long long int mid = l + (r-l)/2;
		
		mergeSort(l,mid);
		mergeSort(mid+1,r);
		
		merge(l,mid,r);
	}
}





void mergeVectors(long long int l, long long int m, long long int r, long long int node)
{
        long long int i,j,k;

        long long int n1 = m-l+1;
        long long int n2 = r-m;

        long long int L[n1][2];
        long long int R[n2][2];

        for(i=0;i<n1;i++)
        {
                L[i][0] = map[node][l+i].vertex;
		L[i][1] = map[node][l+i].cost;
        }
        for(j=0;j<n2;j++)
        {
                R[j][0] = map[node][m+1+j].vertex;
		R[j][1] = map[node][m+1+j].cost;
        }

        i=0;
        j=0;
        k=l;

        while ( i<n1 && j<n2 )
        {
                if (L[i][1] > R[j][1] )
                {
                        map[node][k].vertex = L[i][0];
			map[node][k].cost = L[i][1];
                        i++;
                        k++;
                }
		else
                {
                        map[node][k].vertex = R[j][0];
			map[node][k].cost = R[j][1];
                        j++;
                        k++;
                }
        }

        while (i<n1)
        {
                map[node][k].vertex = L[i][0];
		map[node][k].cost = L[i][1];
                i++;
                k++;
        }

        while (j<n2)
        {
                map[node][k].vertex = R[j][0];
		map[node][k].cost = R[j][1];
                j++;
                k++;
        }
}

void merge1(long long int l, long long int m, long long int r)
{
        long long int i,j,k;

        long long int n1 = m-l+1;
        long long int n2 = r-m;

        long long int L[n1];
        long long int R[n2];

        for(i=0;i<n1;i++)
        {
                L[i] = del1[l+i];
        }
        for(j=0;j<n2;j++)
        {
                R[j] = del1[m+1+j];
        }

        i=0;
        j=0;
        k=l;

        while ( i<n1 && j<n2 )
        {
                if (L[i] <= R[j] )
                {
                        del1[k] = L[i];
                        i++;
                        k++;
                }
                else
                {
                        del1[k] = R[j];
                        j++;
                        k++;
                }
        }
	while (i<n1)
        {
                del1[k] = L[i];
                i++;
                k++;
        }

        while (j<n2)
        {
                del1[k] = R[j];
                j++;
                k++;
        }
}



void mergeSort1 ( long long int l, long long int r )
{
        if( l < r )
        {
                long long int mid = l + (r-l)/2;

                mergeSort1(l,mid);
                mergeSort1(mid+1,r);

                merge1(l,mid,r);
        }
}




void mergeSortVectors ( long long int l, long long int r, long long int node)
{
        if( l < r )
        {
                long long int mid = l + (r-l)/2;

                mergeSortVectors(l,mid,node);
                mergeSortVectors(mid+1,r,node);

                mergeVectors(l,mid,r,node);
        }
}


void travel (long long int node, long long int l, long long int r)
{
	//printf("node is %lld\n",node);
	//printf("array indexes are %lld %lld\n",l,r);
	long long int i,j,len,k,x;
	visited[node]=1;
	len = map[node].size();
	if ( node==1 || len!=1 )
	{
		for(i=0;i<len;i++)
		{
			//printf("node call from parent %lld %lld %lld\n",map[node][i].vertex,l,r);
			if (visited[map[node][i].vertex]==1)
				continue;
			x=map[node][i].cost;
			k=binser(l,r,x);
			if(k!=-1){
				travel(map[node][i].vertex,l,k);
				l=k+1;
			}
		}
		sum = sum + node*(r-l+1);
	}
	else
	{
		sum = sum + node*(r-l+1);
		//printf("node leaf %lld\n",node);
	}
	return;
}


int main()
{
	long long int n,i,l,a,b,c,t;
	cin >> t;
	while (t--)
	{
		for(i=0;i<100005;i++)
		{
			map[i].clear();
			visited[i]=0;
		}
		
	cin >> n >> q;
	for(i=0;i<n-1;i++)
	{
		cin >> a >> b >> c;
		map[a].push_back({b,c});
		map[b].push_back({a,c});
	}
	for(i=0;i<q;i++)
	{
		cin >> del[i];
		del1[i]=del[i];
	}
	/*for(i=1;i<=n;i++)
        {
                l=map[i].size();
                for(int j=0;j<l;j++)
                {
                        cout << i << "  " << j << "  "<< map[i][j].vertex << "   " << map[i][j].cost << "\n" ;
                }
                printf("\n");
        }*/
	mergeSort(0,q-1);
	mergeSort1(0,q-1);
	//printf("Sorting done\n");
	for(i=1;i<=n;i++)
	{
		l = map[i].size();
		mergeSortVectors(0,l-1,i);
	}
	/*for(i=0;i<q;i++)
	{
		printf("%lld %lld\n",del[i],del1[i]);
	}*/
	/*for(i=1;i<=n;i++)
	{
		l=map[i].size();
		for(int j=0;j<l;j++)
		{
			cout << i << "  " << j << "  "<< map[i][j].vertex << "   " << map[i][j].cost << "\n" ;
		}
		printf("\n");
	}*/
	travel(1,0,q-1);
	cout << sum << "\n";
	}
}





