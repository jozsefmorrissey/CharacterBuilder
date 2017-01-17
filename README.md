# CharacterBuilder

Non Standard Library Dependencies
  libjsoncpp-dev
  
Executables 
  DATA_BASE.exe - Builds Database program.
  TEST.exe - Builds all objects and their corresponding test functions.
  CPP_EDITOR.exe - Builds a command line program that can read a .h file and generate or correct source and test files.
  Each exicutable can be made with make [name.exe] or make ALL will make everything.
  
Helper make commands
  findDependencies - make findDependencies FILE=[location/filename.ext] - prints dependencies for makefile rules.
  clean - make clean - erases all exicutables from project home dir, all objects from ./obj/ and all files ending in ~.
  backup - make backup - creates a tar file of existing project and places it in ./backup/ with current date and time in the 
                         name. It deletes oldest files if more than 10 exist, by that time changes should be stable and on github.
                        
                        
TODO:
  Finish Data Base
  Create Server
  Create Simple Client
  implement Bitcoin transactions
  implement Biological Recognition
