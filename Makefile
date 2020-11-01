CFLAGS  = -g -Wall

TARGET = main
PROGRAM = at_command_parser
TEST_FILES_PATH = ./test_files

all: $(TARGET)

$(TARGET): parser.o
	gcc $(CFLAGS) $(TARGET).c -o $(PROGRAM) parser.o

parser.o: parser.c parser.h
	gcc $(CFLAGS) -c parser.c

clean:
	rm $(PROGRAM) parser.o

%.txt: $(TARGET)
	./$(PROGRAM) $@
all_tests:
	$(info NOT YET IMPLEMENTED!!!)
