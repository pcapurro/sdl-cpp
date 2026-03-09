#ifndef TEXTBUTTON_HPP
# define TEXTBUTTON_HPP

# include "Text.hpp"
# include "Shape.hpp"
# include "Element.hpp"

class TextButton : public Element
{
    private:
        optional<Text>          _mainText;
        optional<Shape>         _background;

    protected:
		virtual void	        onPropertiesChanged(SDL_Renderer* renderer) override;
        virtual void	        onPositionChanged(SDL_Renderer* renderer) override;

		virtual void	        onStyleChanged(void) override;

		virtual void	        onSettingsChanged(void) override;
		virtual void	        onStateChanged(void) override;

    public:
        TextButton(void) = delete;

        TextButton(const int x, const int y, const int width, const int height, \
            const Color& backColor, const string& text, const int size, \
            const Color& textColor, const string& fontPath, SDL_Renderer* renderer);

        ~TextButton(void) = default;

        string                  getText(void) const;

        void                    render(SDL_Renderer* renderer);

		virtual void	        onMouseDown(const int x = 0, const int y = 0) override;
		virtual void	        onMouseDownOutside(void) override;

		virtual void	        onMouseUp(const int x = 0, const int y = 0) override;
		virtual void	        onMouseUpOutside(void) override;

		virtual void	        onMouseHover(const int x = 0, const int y = 0) override;
		virtual void	        onMouseHoverOutside(void) override;
};

#endif
