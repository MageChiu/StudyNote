CC = gcc
XX = g++

INC = -I./
CFLAGS = -Wall -O0 -g --std=c++11
TARGET = test_alg
LIBS = -lpthread -lssl -lcrypto
ALG_FILE = $(in)

%.o: %.c
	$(CC) $(INC) $(CFLAGS) -c $< -o $@
%.o: %.cpp
	$(XX) $(INC) $(CFLAGS) -c $< -o $@

PUBOBJ = mychiu.o
SOURCES = $(wildcard ALG*.c ALG*.cpp)
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))
TARGETS = $(patsubst %.o,%,$(OBJ))

OBJ = $(patsubst %.cpp,%.o,$(ALG_FILE))
$(OBJ) : $(ALG_FILE)
	$(XX) $(INC) $(CFLAGS) -c $< -o $@

$(TARGET) : $(OBJ)
	@echo " make the $(TARGET)"
	$(XX) $^ $(LIBS) -g -o $(TARGET)
	rm -rf *.o

all: $(TARGETS)
	@echo "make all "

alg: $(TARGET)
	@echo "only make one target"
	@echo "make the $(TARGET) from $(ALG_FILE)"

test: $(TARGET)
	./$(TARGET)

clean:
	rm -rf *.o $(TARGET)



