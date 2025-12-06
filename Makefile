# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAME = sdl-cpp

SRCS = srcs/main.cpp \
	srcs/base/Element.cpp \
	srcs/base/Text.cpp \
	srcs/base/Button.cpp \
	srcs/base/Texture.cpp \
	srcs/base/Window.cpp \
	srcs/models/YesNo.cpp \

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -I includes/ -I includes/base -I includes/models

SDLFLAGS = -lSDL2 -lSDL2_ttf

OBJS = $(SRCS:.cpp=.o)

## === RULES === ##

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(SDLFLAGS)

re: fclean all

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)
