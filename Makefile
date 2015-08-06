##
## Makefile for yolok in tests_algogen
##
## Made by chauvo_t
## Login   <chauvo_t@epitech.net>
##
## Started on  Tue Jul 28 18:40:39 2015 deb0ch
## Last update Thu Aug  6 15:23:42 2015 deb0ch
##

CXX			:= clang++

SRCDIR			:= src
OBJDIR			:= obj

# These lines are needed to set immediate evaluation for
# these variables, instead of deferred evaluation which is unsuitable.
SRCS			:=
SUBDIRS			:=
CXXFLAGS		:=
LDFLAGS			:=

include $(SRCDIR)/module.mk

OBJS			:= $(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))

SRCS			:= $(addprefix $(SRCDIR)/, $(SRCS))

OBJS			:= $(OBJS:.S=.o)

DEPS			:= $(OBJS:.o=.d)

TMPS			:= $(OBJS) $(OBJS:.o=.d)

CXXFLAGS		+= -W -Wall -Wextra -Werror
CXXFLAGS		+= -std=c++11
CXXFLAGS		+= -O3
CXXFLAGS		+= -MD
debug: CXXFLAGS		+= -g -g3 -ggdb
CXXFLAGS		+= -I./$(SRCDIR)
CXXFLAGS		+= $(addprefix -I./$(SRCDIR)/, $(SUBDIRS))

debug: LDFLAGS		+= -g -g3 -ggdb

NAME			:= hello_geno

all: $(NAME)

debug:	re

showflags:
	@printf "[\033[0;33mCompiler flags\033[0m] %s\n"
	@echo $(CXXFLAGS)
	@printf "[\033[0;33mLinker flags\033[0m] %s\n"
	@echo $(LDFLAGS)

-include $(DEPS)

$(OBJDIR)/%.o: $(SRCDIR)/%.S
	@printf "[\033[0;32mCompiling\033[0m] %s\n" $<
	@$(COMPILE.c) $(OUTPUT_OPTION) $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@printf "[\033[0;32mCompiling\033[0m] %s\n" $<
	@$(COMPILE.c) $(OUTPUT_OPTION) $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@printf "[\033[0;32mCompiling\033[0m] %s\n" $<
	@$(COMPILE.cpp) $(OUTPUT_OPTION) $<

$(NAME): $(OBJS)
	@printf "[\033[0;33mLinker flags\033[0m] %s\n"
	@echo $(LDFLAGS)
	@printf "[\033[0;34mLinking\033[0m] %s\n" $(NAME)
	@$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)
	@printf "[\033[0;35mDONE\033[0m]\n" $(NAME)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	@printf "[\033[0;33mCompiler flags\033[0m] %s\n"
	@echo $(CXXFLAGS)
	@mkdir -p $(OBJDIR)
	@for dir in $(SUBDIRS);			\
	do					\
		mkdir -p $(OBJDIR)/$$dir;	\
	done

clean:
	@rm -rf $(TMPS)
	@printf "[\033[0;31mDeleted\033[0m] %s\n" $(OBJS)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(OBJDIR)
	@printf "[\033[0;35mRemoved\033[0m] %s\n" $(NAME)
	@printf "[\033[0;35mRemoved\033[0m] %s\n" $(OBJDIR)

re:	fclean all

.PHONY:	all clean fclean re
