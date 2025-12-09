CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJS = main.o tsp.o
TARGET = pvv_app

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c tsp.h
	$(CC) $(CFLAGS) -c main.c

tsp.o: tsp.c tsp.h
	$(CC) $(CFLAGS) -c tsp.c

clean:
	rm -f $(TARGET) $(OBJS) $(TARGET).exe