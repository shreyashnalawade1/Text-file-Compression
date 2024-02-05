OBJS	= main.o input_output.o functions.o error.o algorithms.o
SOURCE	= main.c input_output.c functions.c error.c algorithms.c
HEADER	= input_output.h functions.h errro.h common.h algorithms.h
OUT	= project
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c 

input_output.o: input_output.c
	$(CC) $(FLAGS) input_output.c 

functions.o: functions.c
	$(CC) $(FLAGS) functions.c 

error.o: error.c
	$(CC) $(FLAGS) error.c 

algorithms.o: algorithms.c
	$(CC) $(FLAGS) algorithms.c 


clean:
	rm -f $(OBJS) $(OUT)
