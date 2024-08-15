TARGET=todmap
SRCS=main.cpp
OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.d)

#CXX=clang++
CXXFLAGS=-std=c++20 -Wall -O2 -MD

CPPFLAGS=
#TARGET_ARCH=-march=native
LIBS=

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LINK.cpp) -o $@ $(OBJS) $(LIBS)

clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)
	$(RM) temp-ac.txt temp-fc.txt

run: $(TARGET)
	./$(TARGET) 1

list-ac: $(TARGET)
	@./$(TARGET) --ac `seq 1 60`

list-fc: $(TARGET)
	@./$(TARGET) --fc `seq 1 60`

test: $(TARGET)
	./$(TARGET) --ac `seq 1 60` > temp-ac.txt
	diff test-ac.txt temp-ac.txt
	./$(TARGET) --fc `seq 1 60` > temp-fc.txt
	diff test-fc.txt temp-fc.txt

sinclude $(DEPS)
