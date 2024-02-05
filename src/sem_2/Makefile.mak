main: codes/*.c
	gcc codes/*.c -o main

output: main.o platform.o post.o comment.o reply.o
	gcc main.o platform.o post.o comment.o reply.o -o output

main.o: main.c
	gcc -c main.c

platform.o: platform.c
	gcc -c platform.c platform.h

post.o: post.c
	gcc -c post.c post.h

comment.o: comment.c
	gcc -c comment.c comment.h

reply.o: reply.c
	gcc -c reply.c reply.h