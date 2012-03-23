#include <stdio.h>
#include "m_mem.h" 
#include "create_matrix.h"
#include "dancing_link.h"

int main()
{
    int **matrix = NULL;
    int row = 41;
    int column = 21;
    int i = 0;
    int j = 0;
    head h = NULL;

    matrix = MALLOC(sizeof(int *) * row);
    
    for(i = 0 ; i < row; i++)
    {
	*(matrix + i) = MALLOC(sizeof(int) * (column));
    }

    for(i = 0; i < row; i++)
	for(j = 0; j < column; j++)
	{
	    matrix[i][j] = 0;
	}

    init_shape();
    init_matrix(matrix,4,4,5,&row,&column);

    h = matrixcvtlinks(matrix,row,column);
    search(h,0);
    free_links(h);

    //printf("r:%d,c:%d\n",row,column);
    //matrix_display(matrix,row,column);

    return 0;
}
