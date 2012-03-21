#include <stdio.h>
#include "dancing_link.h"

int main()
{
    int matrix[6][7] = {{0,0,1,0,1,1,0},{1,0,0,1,0,0,1},{0,1,1,0,0,1,0},{1,0,0,1,0,0,0},{0,1,0,0,0,0,1},{0,0,0,1,1,0,1}};
    head h = matrixcvtlinks(matrix,6,7);
    //display(h,7); 
    search(h,0);

    return 0;

}
