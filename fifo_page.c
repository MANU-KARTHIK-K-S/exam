#include<stdio.h>
void FIFO(int a[],int n,int c[],int m)
{
int i,j,f,flag,count,flag1;
f=0;
count=0;
for (i=0;i<n;i++)
{
	flag=0;
	for (j=0;j<m;j++)
	{
		if (c[j]==a[i])
		{
			flag=1;
		}
	}
	if (flag==0)
	{
		flag1=0;
		for (j=0;j<m;j++)
		{
			if (c[j]==-1)
			{
				c[j]=a[i];
				f=f+1;
				j=m;
				flag1=1;
			}
		}
		if (flag1==0)
		{
			c[count]=a[i];
			count=count+1;
			f=f+1;
			if (count==m)
				count=0;
		}
	}
	for (j=0;j<m;j++)
		printf("%d\t",c[j]);
	printf("\n");
}
printf("The Number of page faults:%d",f);
printf("\n");
}
void main()
{
int a[30],capacity[10],n,m,ch,i;
printf("Enter the number of frames:");
scanf("%d",&m);
printf("Enter the number of pages:");
scanf("%d",&n);
printf("Enter the reference string\n");
for (i=0;i<n;i++)
{
	scanf("%d",&a[i]);
}
FIFO(a,n,capacity,m);
}



