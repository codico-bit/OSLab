// c program to simulate MFT memory management technique
#include <stdio.h>
int main()
{
	int ms,bs,nob,ef,n,mp[10],tif=0,i,p=0;
	printf("Enter the total memory available in Bytes : ");
	scanf("%d",&ms);
	printf("Enter the block size in Bytes : ");
	scanf("%d",&bs);
	nob=ms/bs;
	ef=ms-nob*bs;
	printf("Enter the number of processes : ");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Enter the memory required for process %d in Bytes : ",i+1);
		scanf("%d",&mp[i]);
	}
	printf("Number of blocks available in memory is %d",nob);
	printf("\n\nPROCESS \tMEMORY REQUIRED\tALLOCATED\tINTERNAL FRAGMENTATION");
	for(i=0;i<n && p<nob;i++)
	{
		printf("\n%d\t\t%d",i+1,mp[i]);
		if(mp[i]>bs)
		printf("\t\tNO\t\t---");
		else
		{
			printf("\t\tYES\t\t%d",bs-mp[i]);
			tif=tif+bs-mp[i];
			p++;
		}
	}
	if(i<n)
	printf("\nMemory is full, remaining process cannot be accomodated");
	printf("\n\nTotal Internal Fragmentation is %d",tif);
	printf("\nTotal External Fragmentation is %d\n",ef);
	return 0;
}
