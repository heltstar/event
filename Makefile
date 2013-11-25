TEST= test
EVENT = event

$ALL:$TEST $EVENT

$TEST:$(EVENT).o
	gcc -o $(TEST) $(TEST).c $(EVENT).o -lpthread
$EVENT:$(EVENT).c $(EVENT).h
	gcc -c $(EVENT).c $(EVENT).h

clean:
	rm *.o $(TEST)
