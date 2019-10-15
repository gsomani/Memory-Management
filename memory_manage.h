#include<stdlib.h>
#include<stdio.h>

struct block_node{
	int node;
	struct block_node *nxt_node ;
	char data[0];
};

typedef struct block_node block;
block *start;
int blocks_in_chunk;

void mem_init(int no_of_bytes,int chunk_size){	
   block *free_start;		
   start = (block *) malloc(no_of_bytes);
   blocks_in_chunk=chunk_size/sizeof(block);
   free_start=start+1;//free_start pointer is one block_node ahead of used_start
   start->nxt_node=free_start;
   free_start->nxt_node=NULL;
   start->node=-1;// for used blocks node is negative integer noting the size of node including header and data
   free_start->node=(no_of_bytes/sizeof(block))-1;//for free blocks node is positive integer noting the size of node including header and data 		 
}

void *mem_alloc(int no_of_bytes){

int diff,blocks_required,chunks_required,size_chunk;
size_chunk=sizeof(block)*blocks_in_chunk;
chunks_required=(no_of_bytes/size_chunk)+((no_of_bytes % size_chunk)>0);
blocks_required=chunks_required*blocks_in_chunk;

block *cur,*new_node;

cur=start;
while(cur!=NULL)
{	
	diff = cur->node - 1 - blocks_required;
	if(diff >0)
	{   
		new_node = cur+1+blocks_required;
		new_node->nxt_node=cur->nxt_node;	
		cur->nxt_node = new_node;             
		new_node->node = diff;	
		cur->node = - (1 + blocks_required);
		return (void *)(cur+1);
	}
	if(diff == 0)
	{
		cur->node *= -1;
		return (void *)(cur+1);
	}
	cur=cur->nxt_node;
}
			
return NULL;				
}

void mem_free(void *ptr){

block *ptr_block_header,*cur,*last;
ptr_block_header=(block *)ptr ;
ptr_block_header--;

last=NULL;cur=start;
while(cur!=NULL)
{	
	if(ptr_block_header==cur && cur->node < 0)
	{
		cur->node=-cur->node;
		if(last->node > 0)
		{
			last->nxt_node=cur->nxt_node;
			last->node+=cur->node;
			cur=last;
		}
		if((cur->nxt_node)->node > 0)
		{
			cur->node+=(cur->nxt_node)->node;
			cur->nxt_node=(cur->nxt_node)->nxt_node;
		}
		return ; 
	}
	last=cur;	
	cur=last->nxt_node;	
}			

};

void mem_dump(){

block *cur;int node_size,i;char status;

cur=start;
printf("Memory status from start of heap : 'u' denotes used and 'f' denotes free and size is printed in number of chunks\n");
while(cur!=NULL)
{	
	if(cur->node > 0) {status='f';node_size=cur->node;}
	else {status='u';node_size=-(cur->node);}
	node_size=(node_size-1)/blocks_in_chunk;
	printf("%c\t%i\t|",status,node_size);	
	if(status=='u') 
	for(i=0;i<node_size;i++)printf("u");
	else
	for(i=0;i<node_size;i++)printf("f");
	printf("|\n");	
	cur=cur->nxt_node;			
}
printf("\n");
}

int mem_exit(){

block *cur;int used_nodes=0;

cur=start;
while(cur!=NULL)
{	
	if(cur->node < -1) used_nodes++;
	cur=cur->nxt_node;			
}
if(used_nodes > 0) 
{ printf("\nError: Free the used nodes\n"); return 0;}
printf("\nDeallocating heap\n");
free(start);
printf("\nHeap deallocated\n");
return 1;
}