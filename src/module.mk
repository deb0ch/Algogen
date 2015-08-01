##
## module.mk for hello_geno in src
##
## Made by deb0ch
## Login   <chauvo_t@epitech.net>
##
## Started on  Tue Jul 28 18:46:20 2015 deb0ch
## Last update Tue Jul 28 18:48:53 2015 deb0ch
##

SRCS		:=	Individual.cpp  	\
			main.cpp	  	\
			Population.cpp

SUBDIRS		+=	utils

include $(SRCDIR)/utils/module.mk
