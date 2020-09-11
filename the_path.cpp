#include<bits/stdc++.h>
typedef long int li;
using namespace std;

li abs1(li x)
{
	if(x<0)
	return -x;
	else
	return x;
}

int main()
{
	li n;
	while(cin>>n)
	{
		li one[n*n][2]={-1},three[n*n][2]={-1},oindex=0,tindex=0;
		char x;
		for(li i=0;i<n;i++)
		{
			for(li j=0;j<n;j++)
			{
				cin>>x;
				if(x=='1')
				{
					one[oindex][0]=i;
					one[oindex++][1]=j;
				}
				else if(x=='3')
				{
					three[tindex][0]=i;
					three[tindex++][1]=j;
				}
			}
		}
		li min=INT_MIN;
		for(li i=0;i<oindex;i++)
		{
			li min1=INT_MAX;
			for(li j=0;j<tindex;j++)
			{
				li z=abs1(three[j][0]-one[i][0])+abs1(three[j][1]-one[i][1]);
				
				if(z<min1)
					min1=z;
			}
			if(min1>min)
				min=min1;
			
		}
		cout<<min<<endl;
		
		
		
	}
	return 0;
}
