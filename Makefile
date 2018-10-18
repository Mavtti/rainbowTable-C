CC = clang
LDFLAGS = -lm
CFLAGS = -std=c99 -Wall -Wextra -g

BINDIR=./bin
OBJDIR=./obj
SRCDIR=./src

EXEC=$(BINDIR)/rainbowTableCracker

SRC_FILES=$(wildcard $(SRCDIR)/*.c)
OBJ_FILES=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC_FILES))

all: $(EXEC)

$(EXEC): $(OBJDIR)/Main.o $(OBJDIR)/RainbowCracker.o $(OBJDIR)/RainbowTable.o $(OBJDIR)/sha256.o
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJDIR)/Main.o: $(SRCDIR)/Main.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/RainbowCracker.o: $(SRCDIR)/RainbowCracker.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/RainbowTable.o: $(SRCDIR)/RainbowTable.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/sha256.o: $(SRCDIR)/sha256.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(EXEC) $(OBJ_FILES)

