##
## module.mk for hello_geno in src
##
## Made by deb0ch
## Login   <chauvo_t@epitech.net>
##
## Started on  Tue Jul 28 18:46:20 2015 deb0ch
## Last update Sat Oct 24 14:46:32 2015 chauvo_t
##

SRCS		:=	Individual.cpp  	\
			main.cpp	  	\
			Population.cpp

SUBDIRS		+=	utils		\
			Threads

include $(SRCDIR)/utils/module.mk
include $(SRCDIR)/Threads/module.mk
