DEFAULT_CC= gcc
CC= $(DEFAULT_CC)
AR= ar

SRCDIR= src
INCDIR= inc
OBJDIR= build
TARGET= $(OBJDIR)/dalek.a

CWARN= -Wall -Wextra -Werror
CDEBUG=
CDEBUG= -g # Comment this out for release builds.

CFLAGS= -fno-strict-aliasing -std=c99 -pedantic $(CWARN) $(CDEBUG)

INC= -I$(INCDIR)

SOURCES= src/fba.c
OBJECTS= $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.c=.o))

all: $(TARGET)

remake: clean all

clean:
	@$(RM) -rf $(OBJDIR)
	@$(RM) $(TARGET)

$(TARGET): $(OBJECTS)
	$(AR) -rc -o $@ $^


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
