#include<stdio.h>

#define MAX 5
void fun(int n,int arr[MAX])
{
	for(int i=0;i<MAX;i++)
		printf("%d ",arr[i]);
	
	printf("\n");
}


int main()
{

	int arr[5]={0,1,2,3,4};
	
	fun(5,arr);
	
	return 0;
}
