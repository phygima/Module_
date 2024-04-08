queue: main.o
	gcc -o queue main.o PriorityQueue.o QueueElement.o 

main.o: main.c
	gcc -c main.c PriorityQueue.c QueueElement.c 


clear:
	rm -f *.o queue
