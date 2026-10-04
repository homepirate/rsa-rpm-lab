CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = rsa-optimized

PREFIX ?= /usr
BINDIR = $(PREFIX)/bin

SRC = src/main.c src/rsa.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

install: $(TARGET)
	mkdir -p $(DESTDIR)$(BINDIR)
	install -m 0755 $(TARGET) $(DESTDIR)$(BINDIR)/$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all install clean