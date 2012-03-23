#include <stdio.h>
#include <assert.h>
#include "m_mem.h"

struct point
{
    int row,column;
};

typedef struct point point;

struct shape
{
    point form[6];
    int max_height;
};

typedef struct shape* shape;

shape myshape[5];

point possible0[4];
point possible1[4];
point possible2[4];
point possible3[4];
point possible4[4];

void init_point(point *p)
{
    int i = 0;
    
    for(i = 0; i < 4; i++)
    {
	p[i].row = -1;
	p[i].column = -1;
    }
}

void init_shape()
{
    int i = 0;

    myshape[0] = (shape)MALLOC(sizeof(struct shape));
    myshape[1] = (shape)MALLOC(sizeof(struct shape));
    myshape[2] = (shape)MALLOC(sizeof(struct shape));
    myshape[3] = (shape)MALLOC(sizeof(struct shape));
    myshape[4] = (shape)MALLOC(sizeof(struct shape));
    
    assert(myshape[0] && myshape[1] && myshape[2] && myshape[3] && myshape[4]);

    myshape[0]->form[0].row = 0;
    myshape[0]->form[0].column = 0;
    myshape[0]->form[1].row = 0;
    myshape[0]->form[1].column = 0;
    myshape[0]->form[2].row = 0;
    myshape[0]->form[2].column = 0;
    myshape[0]->form[3].row = 1;
    myshape[0]->form[3].column = 0;
    myshape[0]->form[4].row = 0;
    myshape[0]->form[4].column = 0;
    myshape[0]->form[5].row = 0;
    myshape[0]->form[5].column = 0;
    myshape[0]->max_height = 2;
    
    myshape[1]->form[0].row = 0;
    myshape[1]->form[0].column = 0;
    myshape[1]->form[1].row = 0;
    myshape[1]->form[1].column = 1;
    myshape[1]->form[2].row = 0;
    myshape[1]->form[2].column = 2;
    myshape[1]->form[3].row = 0;
    myshape[1]->form[3].column = 0;
    myshape[1]->form[4].row = 0;
    myshape[1]->form[4].column = 0;
    myshape[1]->form[5].row = 1;
    myshape[1]->form[5].column = 2;
    myshape[1]->max_height = 2;

    myshape[2]->form[0].row = 0;
    myshape[2]->form[0].column = 0;
    myshape[2]->form[1].row = 0;
    myshape[2]->form[1].column = 1;
    myshape[2]->form[2].row = 0;
    myshape[2]->form[2].column = 0;
    myshape[2]->form[3].row = 0;
    myshape[2]->form[3].column = 0; myshape[2]->form[4].row = 1;
    myshape[2]->form[4].column = 1;
    myshape[2]->form[5].row = 1;
    myshape[2]->form[5].column = 2;
    myshape[2]->max_height = 2;

    myshape[3]->form[0].row = 0;
    myshape[3]->form[0].column = 0;
    myshape[3]->form[1].row = 0;
    myshape[3]->form[1].column = 1;
    myshape[3]->form[2].row = 0;
    myshape[3]->form[2].column = 2;
    myshape[3]->form[3].row = 0;
    myshape[3]->form[3].column = 0;
    myshape[3]->form[4].row = 0;
    myshape[3]->form[4].column = 0;
    myshape[3]->form[5].row = 0; 
    myshape[3]->form[5].column = 0; 
    myshape[3]->max_height = 1;

    myshape[4]->form[0].row = 0;
    myshape[4]->form[0].column = 0;
    myshape[4]->form[1].row = 0;
    myshape[4]->form[1].column = 1;
    myshape[4]->form[2].row = 0;
    myshape[4]->form[2].column = 0;
    myshape[4]->form[3].row = 1;
    myshape[4]->form[3].column = 0;
    myshape[4]->form[4].row = 0;
    myshape[4]->form[4].column = 0;
    myshape[4]->form[5].row = 0;
    myshape[4]->form[5].column = 0;
    myshape[4]->max_height = 2;
	
    init_point(possible0);
    init_point(possible1);
    init_point(possible2);
    init_point(possible3);
    init_point(possible4);
}


int judge_border(shape s)
{
    int i = 0;
    for(i = 0; i < 6; i++)
    {
	if((s->form[i]).row >= 4 || (s->form[i]).column >= 4)
	{
	    return 0;
	}
    }
    return 1;
}

void init_matrix(int **matrix,int row,int column,int shapenum,int *realrow,int *realcolumn)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int h = 0;
    int possible = 0;
    int counter = 0;

    for(i = 0; i < 5; i++)
    {
	counter = 0;
	for(k = 0; k < column; k++)
	{
	    shape tmp = myshape[i];
	    for(h = 0; h < 6; h++)
	    {
		tmp->form[h].row += j;
		tmp->form[h].column += k;
	    }
		
	    if(judge_border(tmp))
	    {
		switch(i)
		{
		    case 0:
			possible0[counter].row = j;
			possible0[counter].column = k;
			break;
		    case 1:
			possible1[counter].row = j;
			possible1[counter].column = k;
			break;
		    case 2:
			possible2[counter].row = j;
			possible2[counter].column = k;
			break;
		    case 3:
			possible3[counter].row = j;
			possible3[counter].column = k;
			break;
		    case 4:
			possible4[counter].row = j;
			possible4[counter].column = k;
			break;
		}
		counter++;
	    }

	    for(h = 0; h < 6; h++)
	    {
		tmp->form[h].row -= j;
		tmp->form[h].column -= k;
	    }
	}
	//printf("shape[%d] possible is %d\n",i,counter);
	possible += counter * (row - myshape[i]->max_height + 1);
    }
    
    //printf("possible is %d\n",possible);
    counter = 0;
    
    *realrow = possible;
    *realcolumn = row*column+shapenum;

    for(i = 0; i < shapenum; i++)
    {
	switch(i)
	{
	    case 0:
		{
		    k = 0;
		    point tmp = possible0[k++]; 
		    while(tmp.row != -1 && tmp.column != -1)
		    {
			shape tmp1 = myshape[0];
			
			//printf("shape[0]'s tmp row:%d,tmp column:%d\n",tmp.row,tmp.column);
			for(j = 0; j < 6; j++)
			{
			    if(j == 0) 
			    {
				int ii = 0;

				for(ii = 0; ii < (row - tmp1->max_height + 1); ii++)
				{
				    matrix[counter + ii][0] = 1;
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
			if(k < 4)
			{
			    tmp = possible0[k];
			    k++;
			}
			else
			{
			    break;
			}
		    }
		    break;
		}
	    case 1:
		{
		    k = 0;
		    point tmp = possible1[k++]; 
		    while(tmp.row != -1 && tmp.column != -1)
		    {
			shape tmp1 = myshape[1];

			for(j = 0; j < 6; j++)
			{
			    if(j == 0) 
			    {
				int ii = 0;

				for(ii = 0; ii < (row - tmp1->max_height + 1); ii++)
				{
				    matrix[counter + ii][1] = 1;
				    matrix[counter + ii][(tmp.row + ii) * row + tmp.column + shapenum] = 1;
				}
			    }
			    else if(tmp1->form[j].row + tmp1->form[j].column != 0)
			    {
				int ii = 0;
				for(ii = 0; ii < (row - tmp1->max_height + 1); ii++)
				{
				    matrix[counter + ii][(tmp1->form[j].row + tmp.row + ii) * row + (tmp1->form[j].column + tmp.column) + shapenum] = 1;
				}
			    }
			}
			counter += (row - tmp1->max_height + 1);

			if(k < 4)
			{
			    tmp = possible1[k];
			    k++;
			}
			else
			{
			    break;
			}
		    }
		    break;
		}
		case 2:
		{
		    k = 0;
		    point tmp = possible2[k++]; 
		    while(tmp.row != -1 && tmp.column != -1)
		    {
			shape tmp1 = myshape[2];

			for(j = 0; j < 6; j++)
			{
			    if(j == 0) 
			    {
				int ii = 0;

				for(ii = 0; ii < (row - tmp1->max_height + 1); ii++)
				{
				    matrix[counter + ii][2] = 1;
				    matrix[counter + ii][(tmp.row + ii) * row + tmp.column + shapenum] = 1;
				}
			    }
			    else if(tmp1->form[j].row + tmp1->form[j].column != 0)
			    {
				int ii = 0;

				for(ii = 0; ii < (row - tmp1->max_height + 1); ii++)
				{
				    matrix[counter + ii][(tmp1->form[j].row + tmp.row + ii) * row + (tmp1->form[j].column + tmp.column) + shapenum] = 1;
				}
			    }
			}
			counter += (row - tmp1->max_height + 1);
			if(k < 4)
			{
			    tmp = possible2[k];
			    k++;
			}
			else
			{
			    break;
			}
		    }
		    break;
		}
	    case 3:
		{
		    k = 0;
		    point tmp = possible3[k++]; 
		    while(tmp.row != -1 && tmp.column != -1)
		    {
			shape tmp1 = myshape[3];

			for(j = 0; j < 6; j++)
			{
			    if(j == 0) 
			    {
				int ii = 0;

				for(ii = 0; ii < (row - tmp1->max_height + 1); ii++)
				{
				    matrix[counter + ii][3] = 1;
				    matrix[counter + ii][(tmp.row + ii) * row + tmp.column + shapenum] = 1;
				}
			    }
			    else if(tmp1->form[j].row + tmp1->form[j].column != 0)
			    {
				int ii = 0;

				for(ii = 0; ii < (row - tmp1->max_height + 1); ii++)
				{
				    matrix[counter + ii][((tmp1->form[j]).row + tmp.row + ii) * row + (tmp1->form[j].column + tmp.column) + shapenum] = 1;
				}
			    }
			}
			counter += (row - tmp1->max_height + 1);
			
			//printf("1\n");
			if(k < 4)
			{
			    tmp = possible3[k];
			    k++;
			}
			else
			{
			    break;
			}
		    }
		    break;
		}
	    case 4:
		{
		    k = 0;
		    point tmp = possible4[k++]; 
		    while(tmp.row != -1 && tmp.column != -1)
		    {
			shape tmp1 = myshape[4];

			for(j = 0; j < 6; j++)
			{
			    if(j == 0) 
			    {
				int ii = 0;
				for(ii = 0; ii < (row - tmp1->max_height + 1); ii++)
				{
				    matrix[counter + ii][4] = 1;
				    matrix[counter + ii][(tmp.row + ii) * row + tmp.column + shapenum] = 1;
				}
			    }
			    else if(tmp1->form[j].row + tmp1->form[j].column != 0)
			    {
				int ii = 0;

				for(ii = 0; ii < (row - tmp1->max_height + 1); ii++)
				{
				    matrix[counter + ii][(tmp1->form[j].row + tmp.row + ii) * row + (tmp1->form[j].column + tmp.column) + shapenum] = 1;
				}
			    }
			}
			counter += (row - tmp1->max_height + 1);

			if(k < 4)
			{
			    tmp = possible4[k];
			    k++;
			}
			else
			{
			    break;
			}
		    }
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
