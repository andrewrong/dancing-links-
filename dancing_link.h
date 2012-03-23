#ifndef DANCE_INCLUDE
#define DANCE_INCLUDE

typedef struct head* head;

extern head matrixcvtlinks(int **matrix,int row,int column);
extern void search(head h,int k);
extern void display(head h,int num);
extern void free_links(head h);

#endif
