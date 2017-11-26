OBJS=libvarerr.a libvarerr.so

CFLAGS=-Wno-narrowing -O2
CC=g++

.PHONY: all clean check distclean build

build: | all clean

all: $(OBJS)

$(BUILD_DIR):
	mkdir -p $@

libvarerr.a: varerr.o unit.o stat.o
	ar rvs $@ $^

libvarerr.so: varerr.o unit.o stat.o
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
