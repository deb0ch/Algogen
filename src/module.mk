##
## module.mk for hello_geno in src
##
## Made by deb0ch
## Login   <chauvo_t@epitech.net>
##
## Started on  Tue Jul 28 18:46:20 2015 deb0ch
## Last update Sun Aug  2 15:22:27 2015 deb0ch
##

SRCS		:=	Individual.cpp  	\
			main.cpp	  	\
			Population.cpp

SUBDIRS		+=	utils		\
			Threads

include $(SRCDIR)/utils/module.mk
include $(SRCDIR)/Threads/module.mk
