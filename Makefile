CC = g++
DEBUG = -g
FLAGS = -Wall -Wextra -Werror -pthread #-ljsoncpp
CFLAGS = $(FLAGS) -c $(DEBUG)
LFLAGS = $(FLAGS) $(DEBUG)

NOSPACE :=
COLON := :
SPACE := $(NOSPACE) $(NOSPACE)
MODULES :=FileCreator Utils Server Server/DataBase Client
OBJS = Error.o Declaration.o Source.o
OBJST = mainTest.o ErrorTest.o StringManipulation.o DeclarationTEST.o SourceTEST.o
OBJ_ALL = $(OBJS) $(OBJST)
FILE_CREATE = cppEditor.o StringManipulation.o ReadCpp.o Declaration.o Error.o Source.o ReadH.o

SRC_DIR := $(addprefix src/,$(MODULES)) src
OBJ_DIR := obj
TEST_DIR := $(addprefix test/,$(MODULES)) test


TEST_EXE = TEST_ALL.exe
ALL_EXE = $(ALL%)
FUNC_GEN_EXE = FUNC_GEN.exe
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


$(TEST_EXE): $(OBJS) $(OBJST);
	$(EXE_RULE)

$(FUNC_GEN_EXE):functionGenorator.o
	$(CC) $) $(addprefix $(OBJ_DIR)/, $(notdir $^)) -o  $@

$(CPP_EDITOR): $(FILE_CREATE)
	$(EXE_RULE)

include DependencyRules
include EditFileRules


