#José "Emily" Sá   fc58200
#Yichen Cao "Mimi" fc58165
#Gonçalo Fernandes fc58194
# #directories# #
#.c files:
SRC_DIR := ./src
# SRC_DIR := /Users/yichencao/Desktop/College/Ano2_Sem2/SO/AdmPor/so-project-1/ADMPOR/src
#.h files:
INC_DIR := ./include
# INC_DIR := /Users/yichencao/Desktop/College/Ano2_Sem2/SO/AdmPor/so-project-1/ADMPOR/include
#.o files:
OBJ_DIR := ./obj
# OBJ_DIR := /Users/yichencao/Desktop/College/Ano2_Sem2/SO/AdmPor/so-project-1/ADMPOR/obj
#executable output:
BIN_DIR := ./bin
# BIN_DIR := /Users/yichencao/Desktop/College/Ano2_Sem2/SO/AdmPor/so-project-1/ADMPOR/bin
#change before submission: BIN_DIR := ./bin

# #implicit rules# #
CC = gcc
CFLAGS = -Wall -Wextra -I $(INC_DIR)
#		-Wall: includes all compile warning signs
#		-Wextra: all the extra warning files.
# 		-I $(INC_DIR): includes the directory to find the .h files

OBJ = client.o enterprise.o intermediary.o process.o main.o memory.o
#DEP = main.h memory.h

# #linking all objects# #
AdmPor: $(addprefix $(OBJ_DIR)/, $(OBJ))
		$(CC) $(addprefix $(OBJ_DIR)/, $(OBJ)) -o $(BIN_DIR)/$@

# #general cmd for obj creation# #
# this command creates a .o file for every corresponding .c file in ./src/ and put it in./obj/.
# it finds its respective .h files automatically.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 
#	$< the first prerequisite -- in this case, all .c files in ./src/
#	$@ the target -- in this case, the output name. 

# #make clean# #
# removes all .o files and executable
clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/AdmPor
#	   -f: force. never prompt. as opposed to -i which goes through every file.