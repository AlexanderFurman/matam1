CC = gcc
OBJS = tool/AsciiArtTool.o tool/main.o RLEList.o
EXEC = AsciiArtTool
STD = -std=c99
COMP_FLAG = -Wall -pedantic-errors -Werror
DEBUG_FLAG = -DNDEBUG
FILE_FLAG = -I/home/mtm/public/2223a/ex1 -Itool/

$(EXEC) : $(OBJS)
	$(CC) -o $@ $(DEBUG_FLAG) $(OBJS)

tool/main.o : tool/main.c tool/AsciiArtTool.h RLEList.h
	$(CC) $(STD) -c $(DEBUG_FLAG) $(FILE_FLAG) $(COMP_FLAG) $*.c -o $@

RLEList.o : RLEList.c
	$(CC) $(STD) -c $(DEBUG_FLAG) $(FILE_FLAG) $(COMP_FLAG) $*.c -o $@

tool/AsciiArtTool.o : tool/AsciiArtTool.c tool/AsciiArtTool.h
	$(CC) $(STD) -c $(DEBUG_FLAG) $(FILE_FLAG) $(COMP_FLAG) $*.c -o $@

clean:
	rm -f $(OBJS) $(EXEC)
