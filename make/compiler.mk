COMP_SRCS = $(wildcard $(SRCDIR)/compiler/*.c)
COMP_OBJS = $(addprefix $(COMPILER_OBJDIR)/, $(notdir $(patsubst %.c, %.o, $(COMP_SRCS))))
COMP_INCDIR = $(INCDIR)/compiler

YELLOW = \033[0;33m$$(tput bold)
PURPLE = \033[1;35m$$(tput bold)
NC= \033[0m$$(tput sgr0)

# $(COMP_OBJS): $(COMP_SRCS)
$(COMPILER_OBJDIR)/%.o: $(SRCDIR)/compiler/%.c
	@printf "$(YELLOW)[compiler   ]$(NC) compiling $(YELLOW)$(notdir $<)$(NC) into $(YELLOW)$(notdir $@)$(NC)..."
	@$(CC) $(CXXFLAGS) -I $(INCDIR) -I $(COMP_INCDIR) -o $@ -c $<
	@printf "\b\b done!\n"

$(COMPILER_BIN): $(COMP_OBJS)
	@printf "$(YELLOW)[compiler   ]$(NC) compiling $(YELLOW)$(notdir $<)$(NC) into product $(PURPLE)$(notdir $@)$(NC)..."
	@$(CC) $(CXXFLAGS) -o $@ $^ $(OBJS) $(LDFLAGS)
	@printf "\b\b done!\n"