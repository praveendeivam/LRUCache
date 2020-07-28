#include <stdio.h> 
#include <stdlib.h> 
int miss=0,hit=0;
struct node 
{ 
	struct node *prev; 
	int page;
	struct node *nxt; 
}; 
 
struct Queue
{ 
	int noofframes;
	struct node *front, *rear; 
}; 

struct Hash 
{
	struct Queue *hq;
	struct node *table[150];
}; 

struct node *createnode(int pageno) 
{  
	struct node* temp=(struct node*)malloc(sizeof(struct node)); 
	temp->page=pageno;  
	temp->prev=temp->nxt = NULL; 
	return temp; 
} 

struct Queue *createQueue(int no) 
{ 
	struct Queue* que=(struct Queue*)malloc(sizeof(struct Queue)); 
	que->front=que->rear=NULL;  
	que->noofframes=no; 
	return que; 
} 
 
struct Hash *createHash(int capacity,int no) 
{ 
	struct Hash* hashq=(struct Hash*)malloc(sizeof(struct Hash));
	hashq->hq=createQueue(no);
	int i; 
	for (i=0;i<capacity;i++) 
	{
	hashq->table[i+1] = NULL;
	}
	return hashq; 
} 
 
int nopages(struct node *front) 
{ 
	int count=0;
	while(front!=NULL)
	{	count++;
		front=front->nxt;
	}
	return count; 
}  

struct Queue *delete(struct Queue *queue) 
{
	if (queue->front==queue->rear) 
	{	queue->front=NULL; } 
	struct node *temp=queue->rear; 
	queue->rear=queue->rear->prev;  
	queue->rear->nxt=NULL; 
	free(temp); 
	return queue; 
} 
 
struct Hash *addnode(struct Hash *hashq, int pageno) 
{ 
	if (nopages(hashq->hq->front)==hashq->hq->noofframes) 
	{  
		hashq->table[hashq->hq->rear->page]=NULL; 
		hashq->hq=delete(hashq->hq); 
	} 
	struct node *temp=createnode(pageno); 
	temp->nxt=hashq->hq->front; 
	if ((hashq->hq->rear)==NULL) 
		hashq->hq->rear=hashq->hq->front=temp; 
	else 
	{ 
		hashq->hq->front->prev=temp; 
		hashq->hq->front=temp; 
	}  
	hashq->table[pageno]=temp; 
	return hashq;
} 
 
struct Hash* lru(struct Hash *hashq, int pageno) 
{ 
	struct node *page=hashq->table[pageno]; 
    if(page==NULL)
    { 
		printf("\n\t%d: Page Miss \n",pageno);
		printf("___________________________\n");
		hashq=addnode(hashq, pageno); 
		miss++;
	}
    else if(page!=hashq->hq->front)
     { 
		printf("\n\t%d:  Page Hit \n",pageno);
		printf("___________________________\n");
		hit++;
		if(page==hashq->hq->rear) 
		{ 
			page->prev->nxt=page->nxt; 
			hashq->hq->rear=page->prev; 
			hashq->hq->rear->nxt=NULL; 
		} 
		else
		{
			page->prev->nxt=page->nxt; 
			page->nxt->prev=page->prev; 
		}
		page->nxt=hashq->hq->front; 
		page->prev=NULL; 
		page->nxt->prev=page; 
		hashq->hq->front=page; 
	} 
    else if (page==hashq->hq->front)
     { 
		printf("\n \t%d:   Page Hit \n",pageno);
		printf("___________________________\n");
		hit++;
	}
	return hashq;
} 
 
void display(struct node *temp)
{
	while(temp->nxt!=NULL)
	{
        printf("[%d]",temp->page);
        printf("\n");
		temp=temp->nxt;
	}
	printf("[%d]\n",temp->page);
}

int main() 
{
	int fr,hsh,c,no=0,no1;
	char fle[15];
	FILE *fp;
	printf("\n Enter Frame Size:");
	scanf("%d",&fr); 
	printf("\n Enter Hash Size:"); // Hash size should be greater than or equal to the largest element in the Page Reference
	scanf("%d",&hsh);
	struct Hash* hash=createHash(hsh,fr); 
	printf("\n Enter the File name:"); // The text file which has the Page Reference
	scanf("%s",fle);
	
	fp=fopen(fle,"r");
   	if(fp==NULL) 
	{ 
        	printf("Cannot open file %s \n", fle); 
        	exit(0); 
    }
	fscanf(fp,"%d",&c); 
	while(!feof(fp)) 
	{ 
        	hash=lru(hash,c); 
		    display(hash->hq->front); 
        	fscanf(fp,"%d",&c); 
		    no++;
    }
	printf("\n  Total Page Hits: %d\n  Total Page Miss: %d\n",hit,miss);

	return 0; 
}
