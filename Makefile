# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAME = sdl-cpp.a

SRCS = srcs/bases/Color.cpp \
	srcs/bases/Cursor.cpp \
	srcs/bases/Engine.cpp \
	srcs/bases/Font.cpp \
	srcs/bases/Properties.cpp \
	srcs/bases/Surface.cpp \
	srcs/bases/Texture.cpp \
	srcs/bases/ImageTexture.cpp \
	srcs/bases/TextTexture.cpp \
	srcs/bases/TTF.cpp \
	srcs/elements/Element.cpp \
	srcs/elements/Image.cpp \
	srcs/elements/Render.cpp \
	srcs/elements/Shape.cpp \
	srcs/elements/Text.cpp \
	srcs/widgets/textfield/Cursor.cpp \
	srcs/widgets/textfield/Edit.cpp \
	srcs/widgets/textfield/Get.cpp \
	srcs/widgets/textfield/Init.cpp \
	srcs/widgets/textfield/On.cpp \
	srcs/widgets/textfield/Set.cpp \
	srcs/widgets/textfield/Render.cpp \
	srcs/widgets/imagebutton/Init.cpp \
	srcs/widgets/imagebutton/On.cpp \
	srcs/widgets/imagebutton/Render.cpp \
	srcs/widgets/textbutton/Get.cpp \
	srcs/widgets/textbutton/Init.cpp \
	srcs/widgets/textbutton/On.cpp \
	srcs/widgets/textbutton/Render.cpp \
	srcs/widgets/valuefield/Cursor.cpp \
	srcs/widgets/valuefield/Edit.cpp \
	srcs/widgets/valuefield/Get.cpp \
	srcs/widgets/valuefield/Init.cpp \
	srcs/widgets/valuefield/On.cpp \
	srcs/widgets/valuefield/Check.cpp \
	srcs/widgets/valuefield/Render.cpp \
	srcs/windows/dialogbox/Add.cpp \
	srcs/windows/dialogbox/Init.cpp \
	srcs/windows/dialogbox/React.cpp \
	srcs/windows/dialogbox/Render.cpp \
	srcs/windows/dialogtextbox/Add.cpp \
	srcs/windows/dialogtextbox/Get.cpp \
	srcs/windows/dialogtextbox/Init.cpp \
	srcs/windows/dialogtextbox/React.cpp \
	srcs/windows/dialogtextbox/Render.cpp \
	srcs/windows/dialogvaluesbox/Add.cpp \
	srcs/windows/dialogvaluesbox/Get.cpp \
	srcs/windows/dialogvaluesbox/Init.cpp \
	srcs/windows/dialogvaluesbox/React.cpp \
	srcs/windows/dialogvaluesbox/Render.cpp \
	srcs/windows/window/Core.cpp \
	srcs/windows/window/Delete.cpp \
	srcs/windows/window/Get.cpp \
	srcs/windows/window/Init.cpp \
	srcs/windows/window/Set.cpp \
	srcs/softwares/DialogBoxPreview.cpp \
	srcs/softwares/DialogTextBoxPreview.cpp \
	srcs/softwares/DialogValuesBoxPreview.cpp \

CXX = c++ -std=c++17

CXXFLAGS = -Wall -Wextra -Werror \
	-I includes/ \
	-I includes/bases \
	-I includes/elements \
	-I includes/widgets \
	-I includes/windows \
	-I includes/softwares

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
