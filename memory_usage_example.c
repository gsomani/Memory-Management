#include "memory_manage.h"

int main()
{
int a,i;
void *p[10]; 
mem_init(2048,32);
mem_dump();
p[0]=mem_alloc(96);
mem_dump();
p[1]=mem_alloc(192);
mem_dump();
p[2]=mem_alloc(64);
mem_dump();
mem_free(p[1]);
mem_dump();
p[3]=mem_alloc(64);
mem_dump();
mem_free(p[0]);
mem_dump();
mem_free(p[2]);
mem_dump();
p[4]=mem_alloc(32);
mem_dump();
p[5]=mem_alloc(64);
mem_dump();
p[6]=mem_alloc(128);
mem_dump();
p[7]=mem_alloc(64);
mem_dump();
p[8]=mem_alloc(32);
mem_dump();
p[9]=mem_alloc(64);
mem_dump();
if(!mem_exit())
	{
	printf("\nMaking memory free node by node\n");	
	for(i=0;i<10;i++)
		mem_free(p[i]);
	}
mem_dump();
mem_exit();
}