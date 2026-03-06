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
		virtual void	        onStyleChanged(void) override;

		virtual void	        onSettingsChanged(void) override;
		virtual void	        onStateChanged(void) override;

    public:
        TextButton(void) = delete;

        TextButton(const Properties& properties, const Color& backColor, \
            const string& text, const int size, const Color& textColor, \
            const string& fontPath, SDL_Renderer* renderer);

        TextButton(const int x, const int y, const int width, const int height, \
            const Color& backColor, const string& text, const int size, \
            const Color& textColor, const string& fontPath, SDL_Renderer* renderer);

        ~TextButton(void) = default;

        void                    setSettings(const bool select, const int selectType, \
            const bool hover, const int hoverCursor, const bool highlight, const bool focus) noexcept;

        string                  getText(void) const;

        void                    render(SDL_Renderer* renderer);

		virtual void	        onMouseDown(void) override;
		virtual void	        onMouseDownOutside(void) override;

		virtual void	        onMouseUp(void) override;
		virtual void	        onMouseUpOutside(void) override;

		virtual void	        onMouseHover(void) override;
		virtual void	        onMouseHoverOutside(void) override;
};

#endif
