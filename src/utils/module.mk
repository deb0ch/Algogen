##
## module.mk for  in src/utils
##
## Made by deb0ch
## Login   <chauvo_t@epitech.net>
##
## Started on  Tue Jul 28 18:46:53 2015 deb0ch
## Last update Thu Aug 13 13:28:46 2015 deb0ch
##

THIS_DIR_L0	:= utils

MOD_SRC		:=	ConfigReader.cpp	\
			ExecFinder.cpp		\
			ExecFinderException.cpp	\
			Randomizer.cpp		\

SRCS		+= $(addprefix $(THIS_DIR_L0)/, $(MOD_SRC))
