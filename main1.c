#include <stdio.h>
#include "m_mem.h" 
#include "create_matrix.h"
#include "dancing_link.h"

int main()
{
    int **matrix = NULL;
    int row = 0;
    int column = 0;
    int i = 0;
    int j = 0;
    head h = NULL;
    mem_in_id = -1;
    is_check = 1;

    mem_check_init();
    init(4,5);
    get_possible(4,4,5,&row,&column);

    printf("row:%d,column:%d\n",row,column);

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

    init_matrix(matrix,4,5);

    h = matrixcvtlinks(matrix,row,column);
    search(h,0);
    //display_key(4,4,5);
    //printf("r:%d,c:%d\n",row,column);
    //matrix_display(matrix,row,column);


    free_links(h);
    free_matrix(matrix,row,column,4,4,5);
    //mem_check_write();
    return 0;
}
