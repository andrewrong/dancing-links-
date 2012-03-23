SRC_FILE=./main1.c ./mem/m_mem.c ./dancing_link.c ./create_matrix.c
HEAD_FILE=-I./mem/
OBJ_FILE=${patsubst %.c,%.o,${SRC_FILE}}

main:${OBJ_FILE}
	gcc  ${OBJ_FILE} ${HEAD_FILE} -o main
%.o:%.c
	gcc -c  $<  -o  $@  ${HEAD_FILE}
clean:
	rm *.o main ./mem/m_mem.o
