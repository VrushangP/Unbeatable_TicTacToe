make all: show_node count_nodes alphatoe

ttt1.o : ttt1.c
	gcc -std=c99 -Wall -pedantic -c ttt1.c

ttt2.o : ttt2.c
	gcc -std=c99 -Wall -pedantic -c ttt2.c

show_node: show_node.o ttt1.o ttt2.o
	gcc -std=c99 -Wall -pedantic -o show_node show_node.o ttt1.o ttt2.o

count_nodes: count_nodes.o ttt1.o ttt2.o
	gcc -std=c99 -Wall -pedantic -o count_nodes count_nodes.o ttt1.o ttt2.o

alphatoe: alphatoe.o ttt1.o ttt2.o
	gcc -std=c99 -Wall -pedantic -o alphatoe alphatoe.o ttt1.o ttt2.o

clean:
	rm show_node count_nodes show_node.o count_nodes.o ttt2.o alphatoe alphatoe.o ttt1.o
