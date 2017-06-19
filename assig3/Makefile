NAME = histogram
CC = g++
CFLAGS = -std=c++14 -fstrict-overflow -Werror -Wall -Wshadow -Wstrict-overflow=5 -pedantic
CFLAGS_1 = -std=c++14 -fstrict-overflow -Werror -Wall -Wshadow -Wstrict-overflow=5 -pedantic
LDFLAGS = -pthread -I$(CURDIR)
LDFLAGS_1 = -I$(CURDIR)

#error if student directory is not set
ifndef SDIR
SDIR = student
endif

#Compiler flags
#if mode variable is empty, setting release build mode
ifeq ($(mode),debug)
	CFLAGS += -O0 -g
else
	mode = release
	CFLAGS += -O2
endif

VPATH = $(SDIR)
SRC = $(wildcard *.cpp) $(wildcard */*.cpp)

OBJ_SEQ = $(SDIR)/main.o $(SDIR)/names.o $(SDIR)/$(NAME).o $(SDIR)/$(NAME)_seq.o
OBJ_PAR = $(SDIR)/main.o $(SDIR)/names.o $(SDIR)/$(NAME).o $(SDIR)/$(NAME)_par.o
OBJ_UNIT = $(SDIR)/unit_test.o $(SDIR)/$(NAME).o $(SDIR)/names.o $(SDIR)/$(NAME)_par.o $(SDIR)/$(NAME)_ref.o

# The dependency file names.
DEPS := $(OBJ_SEQ:.o=.d)

all: sequential parallel unit_test

sequential: $(SDIR)/$(NAME)_seq

parallel: $(SDIR)/$(NAME)_par

unit_test: $(SDIR)/unit_test

$(SDIR)/$(NAME)_seq : $(OBJ_SEQ)
	$(CC) -o $@ $(OBJ_SEQ) $(CFLAGS) $(LDFLAGS_1)

$(SDIR)/$(NAME)_par : $(OBJ_PAR)
	$(CC) -o $@ $(OBJ_PAR) $(CFLAGS) $(LDFLAGS_1)
	
$(SDIR)/unit_test: $(OBJ_UNIT)
	$(CC) -o $@ $(OBJ_UNIT) $(CFLAGS) $(LDFLAGS_1) 
 
$(SDIR)/%.o: %.cpp
	$(CC) -c -MMD -MP $< -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(SDIR)/$(NAME)_seq $(SDIR)/$(NAME)_par $(SDIR)/unit_test $(SDIR)/*.o $(SDIR)/*.d $(SDIR)/runtime
	
-include $(DEPS)

.PHONY : all sequential parallel unit_test clean
