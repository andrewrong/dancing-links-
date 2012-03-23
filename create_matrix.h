#ifndef MATRIX_INCLUDE
#define MATRIX_INCLUDE

#define T point
typedef struct T* T;

extern void init(int row,int shapenum);
extern void get_possible(int row,int column,int shapenum,int *realrow,int *realcolumn);

extern void init_matrix(int **matrix,int row,int shapenum);

extern void matrix_display(int **matrix,int row,int column);

extern void free_matrix(int **matrix,int realrow,int realcolumn,int row,int column,int shapenum);

#undef T
#endif
