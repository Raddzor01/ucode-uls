CC = clang
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -D_GNU_SOURCE -gdwarf-4

NAME = uls

OBJ_DIR = obj
INC_DIR = inc
SRC_DIR = src

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:%.c=%.o)))
INC_FILES = $(wildcard $(INC_DIR)/*.h)

LIB_DIR = libmx
LIB_INC = $(LIB_DIR)/inc
LIB_A = $(LIB_DIR)/libmx.a

RM = rm -rf
AR = ar rcs
MKDIR = mkdir -p
MAKE_LIB = make -sC

all: $(LIB_A) $(NAME) clean

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -L$(LIB_DIR) -lmx -o $@

$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR) -I$(LIB_INC)

$(OBJ_DIR):
	@$(MKDIR) $@

$(LIB_A):
	@$(MAKE_LIB) $(LIB_DIR)

clean:
	@$(RM) $(OBJ_DIR)

uninstall: clean
	@$(MAKE_LIB) $(LIB_DIR) $@
	@$(RM) $(NAME)

reinstall: uninstall all
