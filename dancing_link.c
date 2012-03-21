#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "m_mem.h"
#include "dancing_link.h"

struct head
{
    struct head *right,*left,*down,*up,*c;
    char name[10];
    int num;
};

head key[256] = {NULL};

void itoa(int i,char *ch)
{
    int length = strlen(ch);
    char *tmp = ch + length;

    while(i)    
    {
	int j = i % 10;
	*(--tmp) = j + '0';
	i = i / 10;
    }
}

head matrixcvtlinks(int **matrix,int width,int height)
{
    int i = 0;
    int j = 0;
    char str[256];
    head h = (head)MALLOC(sizeof(struct head));
    head array = NULL;

    assert(matrix && width >= 0 && height >= 0);
    assert(h);

    h->right = h->left = h;
    h->down = h->up = h->c = NULL;
    
    for(i = 0; i < width; i++)
    {
	head tmp = (head)MALLOC(sizeof(struct head));
	assert(tmp);

	tmp->right = h->left->right;
	h->left->right = tmp;
	tmp->left = h->left;
	h->left = tmp;
	tmp->down = tmp->up = tmp;
	itoa(i,str,10);
	strcpy(tmp->name,str);
	tmp->num = 0;
    }
    
    array = h->right;


    for(j = 0; j < height; j++)
    {
	head ptr = NULL;
	for(i = 0; i < width; i++)
	{
	    if(matrix[i][j])
	    {
		head tmp = (head)MALLOC(sizeof(head));

		tmp->down = (*(array + i)).up->down;
		(*(array + i)).up->down = tmp;
		tmp->up = (*(array + i)).up;
		(*(array + i)).up = tmp;
		
		tmp->c = array + i;

		if(ptr = NULL)
		{
		    tmp->right = tmp->left = tmp;
		}
		else
		{
		    tmp->right = ptr->right;
		    ptr->right->left = tmp;
		    ptr->right = tmp;
		    tmp->left = ptr;
		}

		ptr = tmp;

		(*(array + i)).num++;
	    }
	}
    }

    return h;
}


head choice_column(head h)
{
    head ptr = NULL;
    int min = 100000; 
    int i = 0;
    int j = 0;
    assert(h);

    ptr = h->right;

    for(;ptr != h;ptr=ptr->right)
    {
	if(min > (ptr)->num)	
	{
	    min = ptr->num; 
	    i = j;
	}
	
	j++;
    }

    return (h->right + i);
}

void cover_column(head column)
{
    //删除列定点
    head ptr = column->down;

    column->left->right = column->right;
    column->right->left = column->left;
    
    for(;ptr != column; ptr = ptr->down)
    {
	head ptr1 = ptr->right;
	for(;ptr1 != ptr; ptr1 = ptr1->right)
	{
	    ptr1->down->up = ptr1->up;
	    ptr1->up->down = ptr1->down;
	    ptr1->c->num--;
	}
    }
}

void uncover_column(head column)
{
    head ptr = column->up;

    assert(column);
    
    for(; ptr != column; ptr = ptr->up)
    {
	head ptr1 = ptr->left;
	for(;ptr1 != ptr; ptr1 = ptr1->left)
	{
	    ptr1->down->up = ptr1;
	    ptr1->up->down = ptr1;
	    ptr1->c->num++;
	}
    }

    column->right->left = column;
    column->left->right = column;
}

void search(head h,int k)
{
    assert(h);
    if(h->right == h)
    {
	int i = 0;
	while(key[i])
	{
	    head tmp = key[i];
	    for(;tmp->right != key[i];tmp = tmp->right)
		printf("%s ",tmp->c->name);

	    i++;
	}
	printf("\n");
    }
    else
    {
	head next_column = choice_column(h);
	head ptr = next_column->down;
	cover_column(next_column);

	for(;ptr != next_column; ptr = ptr->down)
	{
	    head ptr1 = ptr->right;
	    key[k] = ptr;

	    for(;ptr1 != ptr; ptr1 = ptr1->right)
	    {
		cover_column(ptr1->c);
	    }

	    search(h,k+1);

	    ptr1 = key[k]->left;
	    next_column = key[k]->c;

	    for(;ptr1 != key[k];ptr1 = ptr1->left)
	    {
		uncover_column(ptr1->c);
	    }
	    key[k] = NULL;
	}
	uncover_column(next_column);
    }
}
