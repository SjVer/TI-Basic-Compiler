INT_SRCS = $(wildcard $(SRCDIR)/interpreter/*.c)
INT_OBJS = $(addprefix $(INTERPRETER_OBJDIR)/, $(notdir $(patsubst %.c, %.o, $(INT_SRCS))))
INT_INCDIR = $(INCDIR)/compiler

YELLOW = \033[0;33m$$(tput bold)
PURPLE = \033[1;35m$$(tput bold)
NC= \033[0m$$(tput sgr0)

# $(INT_OBJS): $(INT_SRCS)
$(INTERPRETER_OBJDIR)/%.o: $(SRCDIR)/interpreter/%.c
	@printf "$(YELLOW)[interpreter]$(NC) compiling $(YELLOW)$(notdir $<)$(NC) into $(YELLOW)$(notdir $@)$(NC)..."
	@$(CC) $(CXXFLAGS) -I $(INCDIR) -I $(INT_INCDIR) -o $@ -c $<
	@printf "\b\b done!\n"

$(INTERPRETER_BIN): $(INT_OBJS)
	@printf "$(YELLOW)[interpreter]$(NC) compiling $(YELLOW)$(notdir $<)$(NC) into product $(PURPLE)$(notdir $@)$(NC)..."
	@$(CC) $(CXXFLAGS) -o $@ $^ $(OBJS) $(LDFLAGS)
	@printf "\b\b done!\n"