#include <stdio.h>
#include <assert.h>
#include "create_matrix.h"
#include "m_mem.h"
#define BLOCKS 6

struct point
{
    int row,column;
};


struct shape
{
    struct point form[BLOCKS];
    int max_height;
};

typedef struct shape* shape;

shape myshape = NULL;
point *possiblepoint = NULL;

static void init_possiblepoint(int row,int shapenum)
{
    int i = 0; 
    int j = 0; 
    assert(row >= 0 && shapenum >= 0);

    possiblepoint = MALLOC(sizeof(point) * shapenum);

    for(i = 0 ; i < shapenum; i++)
    {
	*(possiblepoint+i) =  MALLOC(sizeof(struct point) * row);
    }

    for(i = 0; i < shapenum; i++)
    {
	for(j = 0; j < row; j++)
	{
	    possiblepoint[i][j].row = -1;
	    possiblepoint[i][j].column = -1;
	}
    }
    
}

static void init_shape(int shapenum)
{
    int i = 0;
    
    assert(shapenum >= 0);

    myshape = MALLOC(sizeof(struct shape)*shapenum);
    assert(myshape);

    myshape[0].form[0].row = 0;
    myshape[0].form[0].column = 0;
    myshape[0].form[1].row = 0;
    myshape[0].form[1].column = 0;
    myshape[0].form[2].row = 0;
    myshape[0].form[2].column = 0;
    myshape[0].form[3].row = 1;
    myshape[0].form[3].column = 0;
    myshape[0].form[4].row = 0;
    myshape[0].form[4].column = 0;
    myshape[0].form[5].row = 0;
    myshape[0].form[5].column = 0;
    myshape[0].max_height = 2;
    
    myshape[1].form[0].row = 0;
    myshape[1].form[0].column = 0;
    myshape[1].form[1].row = 0;
    myshape[1].form[1].column = 1;
    myshape[1].form[2].row = 0;
    myshape[1].form[2].column = 2;
    myshape[1].form[3].row = 0;
    myshape[1].form[3].column = 0;
    myshape[1].form[4].row = 0;
    myshape[1].form[4].column = 0;
    myshape[1].form[5].row = 1;
    myshape[1].form[5].column = 2;
    myshape[1].max_height = 2;

    myshape[2].form[0].row = 0;
    myshape[2].form[0].column = 0;
    myshape[2].form[1].row = 0;
    myshape[2].form[1].column = 1;
    myshape[2].form[2].row = 0;
    myshape[2].form[2].column = 0;
    myshape[2].form[3].row = 0;
    myshape[2].form[3].column = 0; 
    myshape[2].form[4].row = 1;
    myshape[2].form[4].column = 1;
    myshape[2].form[5].row = 1;
    myshape[2].form[5].column = 2;
    myshape[2].max_height = 2;

    myshape[3].form[0].row = 0;
    myshape[3].form[0].column = 0;
    myshape[3].form[1].row = 0;
    myshape[3].form[1].column = 1;
    myshape[3].form[2].row = 0;
    myshape[3].form[2].column = 2;
    myshape[3].form[3].row = 0;
    myshape[3].form[3].column = 0;
    myshape[3].form[4].row = 0;
    myshape[3].form[4].column = 0;
    myshape[3].form[5].row = 0; 
    myshape[3].form[5].column = 0; 
    myshape[3].max_height = 1;

    myshape[4].form[0].row = 0;
    myshape[4].form[0].column = 0;
    myshape[4].form[1].row = 0;
    myshape[4].form[1].column = 1;
    myshape[4].form[2].row = 0;
    myshape[4].form[2].column = 0;
    myshape[4].form[3].row = 1;
    myshape[4].form[3].column = 0;
    myshape[4].form[4].row = 0;
    myshape[4].form[4].column = 0;
    myshape[4].form[5].row = 0;
    myshape[4].form[5].column = 0;
    myshape[4].max_height = 2;
}

int judge_border(shape s,int row)
{
    int i = 0;
    for(i = 0; i < 6; i++)
    {
	if((s->form[i]).row >= row || (s->form[i]).column >= row)
	{
	    return 0;
	}
    }
    return 1;
}

void init(int row,int shapenum)
{
    init_possiblepoint(row,shapenum);
    init_shape(shapenum);
}

void get_possible(int row,int column,int shapenum,int *realrow,int *realcolumn)
{
    int i = 0;
    int j = 0;
    int h = 0;
    int k = 0;
    int counter = 0;

    for(i = 0; i < shapenum; i++)
    {
	counter = 0;

	for(k = 0; k < column; k++)
	{
	    shape tmp = myshape + i;

	    for(h = 0; h < BLOCKS; h++)
	    {
		tmp->form[h].row += j;
		tmp->form[h].column += k;
	    }
		
	    if(judge_border(tmp,row))
	    {
		possiblepoint[i][counter].row = j;
		possiblepoint[i][counter].column = k;
		//printf("(%d,%d),i:%d,counter:%d\n",j,k,i,counter);
		counter++;
	    }

	    for(h = 0; h < BLOCKS; h++)
	    {
		tmp->form[h].row -= j;
		tmp->form[h].column -= k;
	    }
	}

	(*realrow) += (row - myshape[i].max_height + 1) * counter;
    }
    (*realcolumn) = row * column + shapenum;
}

void init_matrix(int **matrix,int row,int shapenum)
{
    int i = 0;
    int j = 0;
    int h = 0;
    int k = 0;
    int counter = 0;

    for(i = 0; i < shapenum; i++)
    {
	k = 0;
	struct point tmp = possiblepoint[i][k++];
	while(tmp.row != -1 && tmp.column != -1)
	{
	    shape tmp1 = (myshape + i);
			
	    //printf("shape[%d]'s tmp row:%d,tmp column:%d\n",i,tmp.row,tmp.column);
	    for(j = 0; j < BLOCKS; j++)
	    {
		if(j == 0) 
		{
			int ii = 0;

			for(ii = 0; ii < (row - tmp1->max_height + 1); ii++)
			{
			    matrix[counter + ii][i] = 1;
			    matrix[counter + ii][(tmp.row + ii) * row + tmp.column + shapenum] = 1;
			}
		}
		else if((tmp1->form[j].row + tmp1->form[j].column) != 0)
		{
			int ii = 0;

			for(ii = 0; ii < (row - tmp1->max_height + 1); ii++)
			{
			    matrix[counter + ii][(tmp1->form[j].row + tmp.row + ii) * row + (tmp1->form[j].column + tmp.column) + shapenum] = 1;
			}
		}
	    }
	    counter += (row - tmp1->max_height + 1);

	    if(k < row)
	    {
		tmp = possiblepoint[i][k];
		k++;
	    }
	    else
	    {
		break;
	    }
	}
    }
}

void matrix_display(int **matrix,int row,int column)
{
    int i = 0, j = 0;

    for(i = 0 ; i < row; i++)
    {
	printf("第%d行:",i);
	for(j = 0 ; j < column; j++)
	{
	    printf("%d ",matrix[i][j]);
	}
	printf("\n");
    }
}

void free_matrix(int **matrix,int realrow,int realcolumn,int row,int column,int shapenum)
{
    int i = 0; 

    for(i = 0; i < shapenum; i++)
    {
	FREE(possiblepoint[i]);
    }
    FREE(possiblepoint);
    FREE(myshape);

    for(i = 0; i < realrow; i++)
	FREE(matrix[i]);
    FREE(matrix);
}
