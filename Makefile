# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAME = sdl-cpp.a

SRCS = srcs/base/Color.cpp \
	srcs/base/Cursor.cpp \
	srcs/base/Engine.cpp \
	srcs/base/Font.cpp \
	srcs/base/Properties.cpp \
	srcs/base/ImageTexture.cpp \
	srcs/base/TextTexture.cpp \
	srcs/base/TTF.cpp \
	srcs/element/Element.cpp \
	srcs/element/Image.cpp \
	srcs/element/Render.cpp \
	srcs/element/Shape.cpp \
	srcs/element/Text.cpp \
	srcs/widgets/textfield/Cursor.cpp \
	srcs/widgets/textfield/Edit.cpp \
	srcs/widgets/textfield/Get.cpp \
	srcs/widgets/textfield/Init.cpp \
	srcs/widgets/textfield/On.cpp \
	srcs/widgets/textfield/Set.cpp \
	srcs/widgets/textfield/Render.cpp \
	srcs/widgets/textbutton/Get.cpp \
	srcs/widgets/textbutton/Init.cpp \
	srcs/widgets/textbutton/On.cpp \
	srcs/widgets/textbutton/Render.cpp \
	srcs/window/dialogbox/Add.cpp \
	srcs/window/dialogbox/Event.cpp \
	srcs/window/dialogbox/Init.cpp \
	srcs/window/dialogbox/React.cpp \
	srcs/window/dialogbox/Render.cpp \
	srcs/window/dialogbox/Routine.cpp \
	srcs/window/dialogtextbox/Add.cpp \
	srcs/window/dialogtextbox/Event.cpp \
	srcs/window/dialogtextbox/Get.cpp \
	srcs/window/dialogtextbox/Init.cpp \
	srcs/window/dialogtextbox/React.cpp \
	srcs/window/dialogtextbox/Render.cpp \
	srcs/window/dialogtextbox/Routine.cpp \
	srcs/window/window/Core.cpp \
	srcs/window/window/Delete.cpp \
	srcs/window/window/Get.cpp \
	srcs/window/window/Init.cpp \
	srcs/window/window/Set.cpp \

CXX = c++

CXXFLAGS = -std=c++17 -Wall -Wextra -Werror \
	-I includes/ \
	-I includes/base \
	-I includes/element \
	-I includes/widgets \
	-I includes/window

AR = ar

ARFLAGS = rcs

OBJS = $(SRCS:.cpp=.o)

## === RULES === ##

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

re: fclean all

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)
