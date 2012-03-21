#ifndef MEM_H
#define MEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1024
struct _mem_info
{
    long pcode;
    char filename[128];
    int initline;
    int stopline;
    int status;
};

typedef struct _mem_info mem_info;

mem_info mem_in[MAXLEN]; 
int mem_in_id;
int is_check;

void *ck_malloc(size_t size,char *filename,int line);
void  ck_free(void *ptr,int line);

void mem_check_init();
void mem_check_write();

#define MALLOC(size) ck_malloc((size),__FILE__,__LINE__)
#define FREE(p)	     ck_free(p,__LINE__)

#endif
