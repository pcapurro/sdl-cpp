#ifndef TEXTFIELD_HPP
# define TEXTFIELD_HPP

# include "Text.hpp"
# include "Shape.hpp"
# include "Element.hpp"

class TextField : public Element
{
    private:
        optional<Text>          _mainText;

        optional<Shape>         _textBack;
        optional<Shape>         _background;

    protected:
		virtual void	        onPropertiesChanged(SDL_Renderer* renderer) override;
		virtual void	        onStyleChanged(void) override;

		virtual void	        onSettingsChanged(void) override;
		virtual void	        onStateChanged(void) override;

    public:
        TextField(void) = delete;

        TextField(const Properties& properties, const Color& backColor, \
            const Color& frameColor);

        TextField(const int x, const int y, const int width, const int height, \
            const Color& backColor, const Color& frameColor);

        ~TextField(void) = default;

        void                    setSettings(const bool select, const int selectType, \
            const bool hover, const int hoverCursor, const bool highlight, const bool focus) noexcept;

        void                    clear(void);

        void                    update(const string& text, const string& fontPath, \
                                    const Color& textColor, SDL_Renderer* renderer);

        string                  getText(void) const;

        void                    render(SDL_Renderer* renderer);

		virtual void	        onMouseDown(void) override;
        virtual void	        onMouseDownDouble(void) override;
		virtual void	        onMouseDownOutside(void) override;

		virtual void	        onMouseUp(void) override;
		virtual void	        onMouseUpOutside(void) override;

		virtual void	        onMouseHover(void) override;
		virtual void	        onMouseHoverOutside(void) override;

        virtual void	        onButtonDown(const int key) override;

};

#endif
