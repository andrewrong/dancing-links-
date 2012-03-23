#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "m_mem.h"
#include "dancing_link.h"

struct head
{
    struct head *right,*left,*down,*up,*c;
    int name; 
    int num;
};

head key[1024] = {NULL};
head *array = NULL;
/*
 * 1. 只是值传递从而导致了指针没有变化
 * 2. 没有对初始化字符串最后的\0
 * 3. 没有判断i=0的情况*/

char *m_itoa(int i,char *ch,int num)
{
    
    char *tmp = ch + num - 1;
    *tmp = '\0';
    if( i == 0)
    {
	*(--tmp) = i + '0';
    }
    else
    {
	while(i)    
    	{
    	    int j = i % 10;
    	    *(--tmp) = j + '0';
    	    i = i / 10;
    	}
    }

    return tmp;
}

/*
 * 1.关于二维数组在参数传递的时候发生的变化已经忘记
 * 2.链表和数组的地址问题犯错了,以为链表的下一个和数组的下一个是一样的
 * 3.if判断的时候用=替代了==这个错误很初级*/

head matrixcvtlinks(int **matrix,int row,int column)
{
    int i = 0;
    int j = 0;

    //char str[10];
    //char *strname = str;

    head h = (head)MALLOC(sizeof(struct head));
    array = (head*)MALLOC(sizeof(head) * column);

    assert(matrix && row >= 0 && column >= 0);
    assert(h);
    assert(array);

    h->right = h->left = h;
    h->down = h->up = h->c = NULL;
   
    for(i = 0; i < column; i++)
    {
	//strname = str;
	head tmp1 = (head)MALLOC(sizeof(struct head));
	assert(tmp1);

	tmp1->right = h->left->right;
	h->left->right = tmp1;
	tmp1->left = h->left;
	h->left = tmp1;
	tmp1->down = tmp1->up = tmp1;
	//strname = m_itoa(i,strname,10);
	tmp1->name = i;
	tmp1->num = 0;
	tmp1->c = tmp1;
	array[i] = tmp1;
    }

    for(j = 0; j < row ; j++)
    {
	head ptr = NULL;
	for(i = 0; i < column; i++)
	{
	    if(matrix[j][i])
	    {
		head tmp = (head)MALLOC(sizeof(struct head));
		assert(tmp);
		//strname = str;
		//strname = m_itoa(j,strname,10);
		
		tmp->c = array[i];
		tmp->name = j;
		tmp->down = array[i]->up->down;
		array[i]->up->down = tmp;
		tmp->up = array[i]->up;
		array[i]->up = tmp;

		if(ptr == NULL)
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

		(array[i]->num)++;
	    }
	}
    }

    return h;
}


head choice_column(head h)
{
    head ptr = NULL;
    head tmp = h->right;
    int min = 100000; 
    assert(h);

    ptr = h->right;

    for(;ptr != h;ptr=ptr->right)
    {
	if(min > (ptr)->num)	
	{
	    min = ptr->num; 
	    tmp = ptr;
	}
    }
    printf("choice name:%d\n",tmp->name);
    return (tmp);
}

void cover_column(head column)
{
    //删除列顶点
    head ptr = column->down;
    printf("cover column is %d\n",column->name);

    column->left->right = column->right;
    column->right->left = column->left;
    
    //printf("name:%s,num:%d\n",column->right->name,column->right->num);

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
    printf("uncover column is %d\n",column->name);

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
	    printf("key %d is : ",i);
	    printf("第%d行的:",tmp->name);
	    for(;tmp->right != key[i];tmp = tmp->right)
		printf("%d ",tmp->c->name);
	    printf("%d ",tmp->c->name); 
	    i++;

	    printf("\n");
	}
	display_key(4,4,5);
    }
    else
    {
	head next_column = choice_column(h);
	head ptr = next_column->down;
	cover_column(next_column);
	
	for(;ptr != next_column; ptr = ptr->down)
	{
	    printf("现在正在处理第%d行.\n",ptr->name);
	    head ptr1 = ptr->right;
	    key[k] = ptr;

	    for(;ptr1 != ptr; ptr1 = ptr1->right)
	    {
		cover_column(ptr1->c);
	    }

	    printf("---------------------------------\n");

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
#if 0	
	test = h->right;
	for(;test != h; test = test->right)
	{
		printf("addr:%p\n",test);
	}
#endif
    }
}


void display(head h,int num)
{
    int i = 0;
    head ptr = array[0]->down;
    head ptr1 = ptr->right;

    head ptr2 = h->right;
    for(;ptr2 != h; ptr2 = ptr2->right)
    {
	printf("2 head addr is %p\n",ptr2);
    }
    for(i = 0; i < num; i++)
    {
	printf("head addr %d is %p\n",i,array[i]);
    }


    for(;ptr != array[0]; ptr = ptr->down)
    {
	printf("c:%p,ptr:%p,array[0]:%p\n",ptr->c,ptr,array[0]);
    }

    for(;ptr1 != array[0]->down;ptr1 = ptr1->right)
    {
	printf("ptr1 addr is %p\n",ptr1);
    }
}

void free_links(head h)
{
    head ptr = h->right;

    while(ptr != h) 
    {
	head tmp1 = ptr;
	head tmp2 = ptr->down;
	ptr = ptr->right;
	
	while(tmp2 != tmp1)
	{
	    head tmp3 = tmp2;
	    tmp2 = tmp2->down;
	    FREE(tmp3);
	}

	FREE(tmp1);
    }

    FREE(h);
    h = NULL;

    FREE(array);
}

void display_key(int row,int column,int shapenum)
{
    int **matrix = NULL;
    int i = 0;
    int j = 0;
    matrix = MALLOC(sizeof(int*) * row);

    for(i = 0;i < row; i++)
    {
	matrix[i] = MALLOC(sizeof(int) * column);	
    }

    for(i = 0; i < row; i++)
	for(j = 0; j < column; j++)
	{
	    matrix[i][j] = 0;
	}

    i = 0;
    while(key[i])
	{
	   head tmp = key[i]; 
	   for(;tmp->right != key[i];tmp = tmp->right)
	   {
	       //printf("name:%d\n",tmp->c->name);
		if(tmp->c->name >= shapenum)	
		{
		    int tmprow = (tmp->c->name - shapenum) / row;
		    int tmpcolumn = (tmp->c->name - shapenum) % row;
		    matrix[tmprow][tmpcolumn] = i;
		}
	   }

	   if(tmp->c->name >= shapenum)	
	    {
		    int tmprow = (tmp->c->name - shapenum) / row;
		    int tmpcolumn = (tmp->c->name - shapenum) % row;
		    matrix[tmprow][tmpcolumn] = i;
	    }
	   i++;
	}

    for(i = 0; i < row; i++)
    {
	for(j = 0; j < column; j++)
	{
	    printf("%d ",matrix[i][j]);
	}
	printf("\n");
    }

    for(i = 0; i < row; i++)
	FREE(matrix[i]);
    FREE(matrix);
}
