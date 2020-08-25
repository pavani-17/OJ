#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>
#include <limits.h>

using namespace std;

vector < pair <int, int> > live;
set <pair <int, int> > dead;

int main()
{
    int N,M,i,j,l,d,x1,y1,n,m,p,q,min=INT_MAX,v1,v2;
    long long int sum=0;
    scanf("%d%d",&M,&N);
    int arr[M][N][M][N];
    scanf("%d%d",&d,&l);
    for(i=0;i<d;i++)
    {
        scanf("%d%d", &x1, &y1);
        dead.insert(make_pair(x1-1,y1-1));
    }
    for(i=0;i<l;i++)
    {
        scanf("%d%d", &x1, &y1);
        live.push_back(make_pair(x1-1,y1-1));
    }

    for(m=0;m<M;m++)
    {
	    for(n=0;n<N;n++)
	    {
		    for(p=0;p<M;p++)
		    {
			    for(q=0;q<N;q++)
			    {
				    arr[m][n][p][q] = INT_MAX;
			    }
		    }
	    }
    }


    	    /*for(m=0;m<M;m++)
            {
                for(n=0;n<N;n++)
                {
                    printf("Distance for (%d,%d)\n",m,n);
                    for(p=0;p<M;p++)
                    {
                        for(q=0;q<N;q++)
                        {
                            printf("%d  ",arr[m][n][p][q]);
                        }
                        printf("\n");
                    }
                    printf("\n\n\n");
                }
            }*/



    
    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        {
		
            if(dead.count(make_pair(i,j))==1)
		    continue;
            arr[i][j][i][j] = 0;

            if(i+1<M && dead.count(make_pair(i+1,j)) == 0)
            {
                arr[i][j][i+1][j]=1;
                arr[i+1][j][i][j]=1;
		//printf("%d  %d %d %d \n",i,j,i+1,j);
            }
            if(j+1<N && dead.count(make_pair(i,j+1)) == 0)
            {
                arr[i][j+1][i][j]=1;
                arr[i][j][i][j+1]=1;
		//printf("%d  %d  %d  %d\n",i,j,i,j+1);
            }
            if(i-1>=0 && dead.count(make_pair(i-1,j)) == 0)
            {
                arr[i-1][j][i][j]=1;
                arr[i][j][i-1][j]=1;
		//printf("%d  %d  %d  %d\n",i,j,i-1,j);
            }
            if(j-1>=0 && dead.count(make_pair(i,j-1)) == 0)
            {
                arr[i][j-1][i][j]=1;
                arr[i][j][i][j-1]=1;
		//printf("%d  %d %d  %d\n",i,j,i,j-1);
            }
        }
    }

    	/*for(m=0;m<M;m++)
            {
                for(n=0;n<N;n++)
                {
                        printf("Distance for (%d,%d)\n",m,n);
                    for(p=0;p<M;p++)
                    {
                        for(q=0;q<N;q++)
                        {
                            printf("%d  ",arr[m][n][p][q]);
                        }
                        printf("\n");
                    }
                    printf("\n\n\n");
                }
            }*/

    for(i=0;i<M;i++)
    {
	    for(j=0;j<N;j++)
	    {
		    for(m=0;m<M;m++)
		    {
			    for(n=0;n<N;n++)
			    {
				    for(p=0;p<M;p++)
				    {
					    for(q=0;q<N;q++)
					    {
						    if (dead.count(make_pair(i,j)) || dead.count(make_pair(p,q)) || dead.count(make_pair(m,n)))
						    {
							    continue;
						    }
						    if(arr[i][j][p][q]==INT_MAX || arr[m][n][i][j]==INT_MAX)
							    continue;
						    if(arr[m][n][p][q] > arr[m][n][i][j] + arr[i][j][p][q])
						    {
						    	arr[m][n][p][q] = arr[m][n][i][j] + arr[i][j][p][q];
						    	//printf("Distance btw (%d,%d) and (%d,%d) updated to %d\n",m,n,p,q,arr[m][n][p][q]);
					    	    }
					    }
				    }
			    }
		     }
	    }
    }

            /*for(m=0;m<M;m++)
            {
                for(n=0;n<N;n++)
                {
		    printf("Distance for (%d,%d)\n",m,n);
                    for(p=0;p<M;p++)
                    {
                        for(q=0;q<N;q++)
                        {
                            printf("%d  ",arr[m][n][p][q]);
                        }
			printf("\n");
                    }
		    printf("\n\n\n");
                }
            }*/

    sort(live.begin(),live.end());
    
    if(l==0)
    {
	    printf("%d\n",arr[0][0][M-1][N-1]);
	    exit(0);
	}

    do
    {
        sum=0;
	//printf("\n\n The path is:\n");
        for(i=0;i<l-1;i++)
        {
	    //printf("%d %d \n",live[i].first,live[i].second);
            sum += arr[live[i].first][live[i].second][live[i+1].first][live[i+1].second];
	    if(arr[live[i].first][live[i].second][live[i+1].first][live[i+1].second] == INT_MAX)
	    {
		    sum = INT_MAX;
		    break;
	    }
        }
	if(sum!=INT_MAX && l!=0)
	{
        	sum += arr[0][0][live[0].first][live[0].second] + arr[live[l-1].first][live[l-1].second][M-1][N-1];
        }
	if(arr[0][0][live[0].first][live[0].second]==INT_MAX || arr[live[l-1].first][live[l-1].second][M-1][N-1]==INT_MAX)
		sum = INT_MAX;
        if(sum<min)
        {
            min = sum;
        } 
        
    } while (next_permutation(live.begin(),live.end()));
	
    if(min!=INT_MAX)
    {
    	printf("%d\n",min);
    }
    else
    {
	    printf("-1\n");
    }
}

