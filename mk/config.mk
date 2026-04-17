CXX			=	clang++

BUILD_DIR	=	build

CXXFLAGS	=	-std=c++20 \
				-Wall \
				-Wextra \
				-Werror

CPPFLAGS	=	-Isrc/Network/include \
				-Isrc/Utils/include \
				-Isrc/DesignPattern/include \
				-Isrc/Server/include \
				-Isrc/Client/include \
				-Isrc/Types			\
				-Ilibs/myteams \
				-Isrc/LiteORM/include

LDFLAGS		=	-L$(BUILD_DIR)/libs\
 				-lnetwork\
 				-ldesign-pattern\
 				-lutils \
 				-llite-orm \
				-Llibs/myteams \
				-lmyteams \
				-luuid

RM			=	rm -f
