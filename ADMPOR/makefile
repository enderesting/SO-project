
#.c files:
SRC_DIR := ./src
#.h files:
INC_DIR := ./include
#.O files:
OBJ_DIR := ./obj
#output files:
BIN_DIR := ./bin

# OBJ_dir = obj
# OBJECTOS = main.o par.o positive.o
# main.o = funcoes.h
# par.o =
# positive.o =

# #implicit rules
CC = gcc
CFLAGS = -Wall -Wextra -I $(INC_DIR)
#		-Wall: includes all compile warning signs
# 		-I $(INC_DIR): includes the directory the files are at
# #LIBS = -lm
# #		-math library


# out: $(OBJECTOS)
# 		$(CC) $(addprefix $(OBJ_DIR)/, $(OBJECTOS)) -o bin/out $(LIBS)
# 		# echo ${FIM}

# %.o: src/%.c $($@)
# 		$(CC) -I include -o $(OBJ_dir)/$@ -c $<

OBJ = client.o enterprise.o intermediary.o process.o main.o memory.o
DEP = main.h memory.h


AdmPor: $(addprefix $(OBJ_DIR)/, $(OBJ))
		$(CC) $(addprefix $(OBJ_DIR)/, $(OBJ)) -o $(BIN_DIR)/$@

# client:
# enterprise:
# intermediary:
# process: memory.h main.h
# 	gcc 

# main.o: memory.o
# 	gcc $^ -c main.c
# # 	    $^: prints prerequisites
# memory.o:
# 	gcc -c memory.c 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c #$(INC_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@ 

# $(OBJ_DIR)/%.o: $(addprefix $(INC_DIR)/, $(DEP))


# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/$(DEP)
# 	$(CC) $(CFLAGS) -c $< $(addprefix $(INC_DIR)/, $(DEP)) -o $@ 
# $(OBJ): $(INC_DIR)/*.h $(SRC_DIR)/$(OBJ).c
# 	$(CC) $(CFLAGS) -c $^ -o ./$(OBJ_DIR)/$@
#	$^ all prequisite
#	$@ the target

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/AdmPor
#	   -f: force. never prompt. as opposed to -i which goes through every file.
# in this case i think removes all .o files and out?