CC = gcc
CFLAGS = -Wall -Wextra -O2 -MMD -MP

PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin

TARGET = cfetch

SOURCES = main.c \
          os.c \
          system.c \
          cpu.c \
          memory.c \
          uptime.c \
          output.c \
          gpu.c \
          logo.c \
          shell.c \
          packages.c \
          timeinfo.c

OBJECTS = $(SOURCES:.c=.o)
DEPENDS = $(OBJECTS:.o=.d)

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPENDS)

clean:
	rm -f $(OBJECTS) $(DEPENDS) $(TARGET)

install: $(TARGET)
	install -Dm755 $(TARGET) $(BINDIR)/$(TARGET)

uninstall:
	rm -f $(BINDIR)/$(TARGET)
