#include <stdio.h>

int main(){
	//Declaring Variables necessary for the algorithm
	int i,j,k,n=10, p,r;
	int temp;
	int adjmat[100][100];
	int reqmatrix[10][10], allocmatrix[10][10], t_allocmatrix[10][10];
	//Input number of processes and resources from user
	printf("Enter the number of processes:");
	scanf("%d", &p);
	printf("Enter the number of resources:");
	scanf("%d", &r);
	int t_res[r],alloc_res[r],a_res[r];
	//Create a file pointer to the input file
	FILE *input;
	input = fopen("input4.txt", "r");
	//Read the total resources from the file
	for (i = 0; i < r; i++)
	{
		fscanf(input, "%d", &t_res[i]);
	}
	printf("Total resources\n");
	for(i=0;i<r;i++)
	{
		printf("%d ", t_res[i]);
	}
	//Loop to read the adjacency matrix
	for(i=0;i<(p+r);i++)
	{
		for(j=0;j<(p+r);j++)
		{
			fscanf(input, "%d", &adjmat[i][j]);
		}	
	}
	printf("\nAdjacency Matrix\n");
	for(i=0;i<(p+r);i++)
	{
		for(j=0;j<(p+r);j++)
		{
			printf("%d ", adjmat[i][j]);
		}	
		printf("\n");
	}
	//Loop to extract the request matrix from the adjacency matrix
	for(i=0;i<p;i++)
	{
		temp=0;
		for(j=p;j<(p+r);j++)
		{
			reqmatrix[i][temp]=adjmat[i][j];
			temp++;
		}
	}
	printf("Request Matrix\n");
	for(i=0;i<p;i++)
	{
		for(j=0;j<r;j++)
			{
				printf("%d ", reqmatrix[i][j]);
			}
			printf("\n");
	}
	temp=0;
	//loop to extract the allocation matrix from adjacency matrix
	for(i=p;i<(p+r);i++)
	{
		for(j=0;j<p;j++)
		{
			allocmatrix[temp][j]=adjmat[i][j];
		}
		temp++;
	}
	printf("Allocation Matrix\n");
	for(i=0;i<r;i++)
	{
		for(j=0;j<p;j++)
			{
				printf("%d ", allocmatrix[i][j]);
			}
			printf("\n");
	}
	/*Loop to find the transpose of the resource allocation matrix*/
	for(i=0;i<p;i++)
	{
		for(j=0;j<r;j++)
		{
			t_allocmatrix[i][j]=allocmatrix[j][i];
		}
	}
	printf("Transpose of Allocation Matrix\n" );
	for(i=0;i<p;i++)
	{
		for(j=0;j<r;j++)
			{
				printf("%d ", t_allocmatrix[i][j]);
			}
			printf("\n");
	}
	printf("Assigned resources\n");
	/*Loop to find the number of assigned resources in the present graph state*/
	for (i = 0; i < r; i++)
	{
		alloc_res[i]=0;
		for(j=0;j<p;j++)
		{
			alloc_res[i]=alloc_res[i]+allocmatrix[i][j];
		}
	}
	for(i=0;i<r;i++)
	{
		printf("%d ", alloc_res[i]);
	}
	printf("\nAvailable Resources\n");
	/*Loop to find the availabe resources at the present graph state*/
	for(i=0;i<r;i++)
	{
		a_res[i]=(t_res[i]-alloc_res[i]);
		printf("%d ", a_res[i]);
	}
	printf("\n");

	/*recursive loop to perform graph reduction for the given state*/
	for(k=0;k<p;k++)//first decides number of reductions which is equal to the number of processes
	{
		for(i=0;i<p;i++)//Second loop to search through processes 
		{
			temp=0;
			if(reqmatrix[i][0]<0)
				continue;
			for(j=0;j<r;j++)//Third loop to search if the needed resources is satisfied by the available resources
			{
				if(reqmatrix[i][j]<=a_res[j])
				{
					temp++;
				}
			}
			/*if the needed resources of a process less than available resources finish the process and
			free up the resources */
			if(temp==r)
			{
				printf("Process %d completed\n", i+1);
				printf("Updated Available resources\n");
				for(j=0;j<r;j++)
				{
					a_res[j]+=t_allocmatrix[i][j];//add the resources allocated to process to available resources
					reqmatrix[i][j]=-1;
					printf("%d ", a_res[j]);
				}
				printf("\n");
				break;
			}
		}
	}
	/*Print the processes that are in deadlock to the console*/
	for (i = 0; i < p; i++)
	{
		if (reqmatrix[i][0]>=0)
			printf("Process %d is in deadlock\n", i+1);
	}
	return 0;
}