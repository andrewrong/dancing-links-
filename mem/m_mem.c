#include "m_mem.h"

void *ck_malloc(size_t size,char *filename,int line)
{
    void *p = malloc(size);

    if(!is_check)
    {
	return p;
    }
    else if((mem_in_id + 1)>= MAXLEN)
    {
	printf("mem_in already overflow!\n");
	return p;
    }
    else
    {
	mem_in_id++;

	mem_in[mem_in_id].pcode = (long)p;
	strcpy(mem_in[mem_in_id].filename,filename);
	mem_in[mem_in_id].initline = line;
	mem_in[mem_in_id].stopline = -1;
	mem_in[mem_in_id].status = 0;

	return p;
    }
}

void ck_free(void *ptr,int line)
{
    int i = 0;
    for(i = 0 ; i <= mem_in_id; i++)
    {
	if(mem_in[i].pcode == (long)ptr)
	{
	    mem_in[i].status = 1;
	    mem_in[i].stopline = line;
	    break;
	}
    }

    free(ptr);
    ptr = NULL;
}

void mem_check_init()
{
    int i = 0;
    for(i = 0; i < MAXLEN; i++)
    {
	mem_in[i].pcode = 0;
	strcpy(mem_in[i].filename,"init");
	mem_in[i].initline = -1;
	mem_in[i].stopline = -1;
	mem_in[i].status = -1;
    }
}

void mem_check_write()
{
    int i = 0;
    for(i = 0; i <= mem_in_id; i++)
    {
	printf("pointer:%x,FILENAME:%s,init_line:%d,stop_line:%d,status:%d\n",mem_in[i].pcode,mem_in[i].filename,mem_in[i].initline,mem_in[i].stopline,mem_in[i].status);
    }
}
