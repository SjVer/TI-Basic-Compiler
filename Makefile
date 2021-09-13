# product options
COMPILER_NAME = comp
INTERPRETER_NAME = int

# compiler options
CC = gcc
CXXFLAGS = -std=c11 -Wall -lm -MMD
LDFLAGS = 

# command options
RM = rm
MKDIR = mkdir
TC = touch

# dir stuff
MAINDIR = $(PWD)
SRCDIR = $(MAINDIR)/src
INCDIR = $(MAINDIR)/include
BINDIR = $(MAINDIR)/bin
OBJDIR = $(BINDIR)/obj
COMPILER_OBJDIR = $(OBJDIR)/$(COMPILER_NAME)-obj
INTERPRETER_OBJDIR = $(OBJDIR)/$(INTERPRETER_NAME)-obj

# file stuff
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(patsubst %.c, %.o, $(SRCS))))
COMPILER_BIN = $(BINDIR)/$(COMPILER_NAME)
INTERPRETER_BIN = $(BINDIR)/$(INTERPRETER_NAME)


# make stuff
export COMPILER_NAME INTERPRETER_NAME CC CXXFLAGS LDFLAGS RM MKDIR 
export MAKEDIR SRCDIR INCDIR BINDIR COMPILER_OBJDIR COMPILER_BIN 
export INTERPRETER_OBJDIR INTERPRETER_BIN SRCS OBJS DEPS
.MAIN: all
all: compiler interpreter

YELLOW = \033[0;33m$$(tput bold)
NC= \033[0m$$(tput sgr0)

# targets

# $(OBJS): $(SRCS) | makedirs
$(OBJDIR)/%.o: $(SRCDIR)/%.c | makedirs
	@printf "$(YELLOW)[general    ]$(NC) compiling $(YELLOW)$(notdir $<)$(NC) into $(YELLOW)$(notdir $@)$(NC)..."
	@$(CC) $(CXXFLAGS) -I $(INCDIR) -o $@ -c $<
	@printf "\b\b done!\n"

compiler: $(OBJS) | makedirs
	@$(MAKE) --no-print-directory -f $(MAINDIR)/make/compiler.mk $(COMPILER_BIN)

interpreter: $(OBJS) | makedirs
	@$(MAKE) --no-print-directory -f $(MAINDIR)/make/interpreter.mk $(INTERPRETER_BIN)


makedirs:
	@$(MKDIR) -p $(BINDIR)
	@$(MKDIR) -p $(COMPILER_OBJDIR)
	@$(MKDIR) -p $(INTERPRETER_OBJDIR)

clean:
	@$(RM) -rf $(BINDIR)
	@printf "$(YELLOW)Cleaned!\n$(NC)"



# new file creator
newfile: guard-name | guard-type
	$(TC) $(SRCDIR)/$(type)/$(name).c
	$(TC) $(INCDIR)/$(type)/$(name).h


guard-%: # make sure variable exists
	@ if [ "${${*}}" = "" ]; then \
		echo "Environment variable $* not set (name=\"name\" and type=\"<empty>|interpreter|compiler\" required)"; \
		exit 1; \
	fi


gentokenstrings:
	@python3 $(MAINDIR)/make/gentokenstrings.py