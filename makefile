CC=gcc
CFLAGS=-O3 -W
TARGET=simturing
HDR=$(wildcard *.h)
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all: $(TARGET) clean
# regras para gerar o executavel
$(TARGET) : $(HDR) $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS)

# regras de compilação
.c.o:
	$(CC) -c $(SRC) $(CFLAGS)

.h:
	$(CC) -c $(HDR) $(CFLAGS)

clean:
	rm -rf $(OBJ) *.gch

clear:
	rm -rf $(TARGET)
