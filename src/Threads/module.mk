##
## module.mk for  in src/Threads
##
## Made by deb0ch
## Login   <chauvo_t@epitech.net>
##
## Started on  Tue Jul 28 18:46:53 2015 deb0ch
## Last update Mon Aug  3 17:44:04 2015 deb0ch
##

THIS_DIR_L0	:= Threads

MOD_SRC		:=	MutexException.cpp		\
			SafeFifoException.cpp		\
			ScopedMutex.cpp			\
			ThreadException.cpp		\
			ThreadPool.cpp			\
			UCondVar.cpp			\
			UMutex.cpp			\

SRCS		+= $(addprefix $(THIS_DIR_L0)/, $(MOD_SRC))

LDFLAGS		+= -lpthread
