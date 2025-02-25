// program to detect deadlock in a multiple instance resource allocation graph
#include <stdio.h>
#include <stdbool.h>
int n,m,request[20][20],alloc[20][20],wfg[20][20],avail[20];
bool is_cycle_util(int process,bool visited[],bool stack[])
{
	visited[process]=true;
	stack[process]=true;
	for(int i=0;i<n;i++)
	{
		if(wfg[process][i])
		{
			if(!visited[i] && is_cycle_util(i,visited,stack))
			return true;
			else if(stack[i])
			return true;
		}
	}
	stack[process]=false;
	return false;
}
bool is_deadlock_detected()
{
	bool visited[n];
	for(int l=0;l<n;l++)
	visited[l]=false;
	for(int i=0;i<n;i++)
	{
		if(!visited[i])
		{
			bool stack[n];
			for(int a=0;a<n;a++)
			stack[a]=false;
			if(is_cycle_util(i,visited,stack))
			return true;
		}
	}
	return false;
}
int main()
{
	printf("Enter the number of processes : ");
	scanf("%d",&n);
	printf("Enter the number of resources : ");
	scanf("%d",&m);
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++)
	{
		request[i][j]=0;
		alloc[i][j];
	}
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
	wfg[i][j]=0;
	printf("Enter the number of available resources : ");
	for(int i=0;i<m;i++)
	scanf("%d",&avail[i]);
	printf("1. 0 for no edge");
	printf("\n2. n for edge from process to resource where n is the number of instances");
	printf("\nEnter the edges for every pair of vertices : ");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		scanf("%d",&request[i][j]);
	}
	printf("1. 0 for no edge");
	printf("\n2. n for edge from resource to process where n is the number of instances");
	printf("\nEnter the edges for every pair of vertices : ");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		scanf("%d",&alloc[i][j]);
	}
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++)
	for(int k=0;k<n;k++)
	{
		if(request[i][j]!=0 && alloc[j][k]!=0)
		wfg[i][k]=1;
	}
	int flag=0;
	if(is_deadlock_detected())
	{
		for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		if(request[i][j]>avail[j])
		{
			flag=1;
			break;
		}
		if(flag)
		printf("Deadlock may be present!\n");
		else
		printf("No deadlock possible!\n");
	}
	else
	printf("No deadlock possible!\n");
	return 0;
}
