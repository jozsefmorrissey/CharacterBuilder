CC = g++
DEBUG = -g
FLAGS = -Wall -Wextra -Werror -pthread #-ljsoncpp
CFLAGS = $(FLAGS) -c $(DEBUG)
LFLAGS = $(FLAGS) $(DEBUG)

NOSPACE :=
COLON := :
SPACE := $(NOSPACE) $(NOSPACE)
MODULES :=FileCreator Utils Server Server/DataBase Client DataObjects
OBJS = Error.o Declaration.o Source.o StringManipulation.o
OBJST = ErrorTest.o DeclarationTEST.o SourceTEST.o
OBJ_ALL = $(OBJS) $(OBJST)
FILE_CREATE = cppEditor.o StringManipulation.o ReadCpp.o Declaration.o Error.o Source.o ReadH.o

SRC_DIR := $(addprefix src/,$(MODULES)) src
OBJ_DIR := obj
TEST_DIR := $(addprefix test/,$(MODULES)) test


DATA_BASE = DATA_BASE.exe
TEST = TEST.exe
ALL = $(ALL%)
CPP_EDITOR = CPP_EDITOR.exe


comma:= :
empty:=
space:= $(empty) $(empty)
foo:= a b c
bar:= $(subst $(space),$(comma),$(SRC_DIR))


SIMPLERULE = $(CC) -c $< -o $(OBJ_DIR)/$@ -ljsoncpp
OBJECTRULE = $(CC) $(CFLAGS) $< -o $(OBJ_DIR)/$@
EXE_RULE = $(CC) $(LFLAGS) $(addprefix $(OBJ_DIR)/, $(notdir $^)) -o  $@


vpath %.cpp $(subst $(SPACE),$(COLON),$(SRC_DIR))
vpath %.h $(subst $(SPACE),$(COLON),$(SRC_DIR))
vpath %.o $(OBJ_DIR)
vpath %Test.cpp $(TEST_DIR)
vpath %Test.h $(TEST_DIR)
vpath %TEST.cpp $(TEST_DIR)
vpath %TEST.h $(TEST_DIR)

ALL: $(DATA_BASE) $(TEST) $(CPP_EDITOR);

$(DATA_BASE): main.o $(OBJS);
	$(EXE_RULE)

$(TEST): mainTest.o $(OBJS) $(OBJST);
	$(EXE_RULE)

$(CPP_EDITOR): $(FILE_CREATE)
	$(EXE_RULE)

include DependencyRules
include EditFileRules


