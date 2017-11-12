OBJS=libvarerr.a libvarerr.so

CFLAGS=-Wno-narrowing -Og -ggdb
CC=g++

.PHONY: all clean check distclean

all: $(OBJS)

libvarerr.a: varerr.o unit.o
	ar rvs $@ $^

libvarerr.so: varerr.o unit.o
	$(CC) --shared -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -fpic -c -o $@ $^

clean:
	$(RM) *.o
	$(RM) a.out

distclean: clean
	$(RM) $(OBJS)
    
check: all
	g++ main.cpp $(word 1,$(OBJS))
	./a.out
