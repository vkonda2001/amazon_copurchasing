EXE = finalproj
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = graph.o main.o algorithms.o

# Generated files
#CLEAN_RM = images/Out.png

# Use the cs225 makefile template:
include cs225.mk