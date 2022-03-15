CC = gcc
OBJECTS = tracker.o
.PHONY: clean

tracker.exe: $(OBJECTS)
	$(CC) $(OBJECTS) -o tracker.exe

%.o: %.c
	$(CC) -c $<

clean:
	rm -f $(OBJECTS) *.exe
