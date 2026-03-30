CXX		    =	clang++

BUILD_DIR	=	build

CXXFLAGS	=	-std=c++20\
				-Wall\
				-Wextra\
				-Werror

CPPFLAGS	=	-Isrc/Network/include\
				-Isrc/Utils/include\
				-Isrc/DesignPattern/include\

LDFLAGS		=

RM		=	rm -f
