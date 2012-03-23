#include <stdio.h>
#include "m_mem.h"
#include "dancing_link.h"

int main()
{
    int matrix[6][7] = {{0,0,1,0,1,1,0},{1,0,0,1,0,0,1},{0,1,1,0,0,1,0},{1,0,0,1,0,0,0},{0,1,0,0,0,0,1},{0,0,0,1,1,0,1}};
    head h = NULL;

    mem_in_id = -1;
    is_check = 1;
    mem_check_init();
    h = matrixcvtlinks(matrix,6,7);
    search(h,0);
    free_links(h);
    mem_check_write();
    return 0;
}

