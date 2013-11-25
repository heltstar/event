
TEST= test
EVENT = event

$ALL:$TEST $EVENT
$TEST:$(EVENT).o
	gcc -o test test.c event.o -lpthread
$EVENT:
	gcc -c event.c event.h

clean:
	rm *.o test
