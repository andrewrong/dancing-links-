#ifndef DANCE_INCLUDE
#define DANCE_INCLUDE

typedef struct head* head;

extern head matrixcvtlinks(int **matrix,int width,int height);
extern void search(head h,int k);

#endif
