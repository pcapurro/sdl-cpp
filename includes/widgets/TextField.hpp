#ifndef TEXTFIELD_HPP
# define TEXTFIELD_HPP

# include "Text.hpp"
# include "Shape.hpp"
# include "Element.hpp"

class TextField : public Element
{
    private:
        int                     _maxChar;

        string                  _fontPath;
        Color                   _textColor;
        optional<Text>          _mainText;

        int                     _cursorPos;
        optional<Shape>         _cursor;

        optional<Shape>         _background;

        int                     _originalHeight;
        bool                    _wrapping;
        int                     _maxLines;


    protected:
		virtual void	        onPropertiesChanged(SDL_Renderer* renderer) override;
		virtual void	        onStyleChanged(void) override;

		virtual void	        onSettingsChanged(void) override;
		virtual void	        onStateChanged(void) override;

    public:
        TextField(void) = delete;

        TextField(const Properties& properties, const Color& backColor, \
            const Color& frameColor, const string& fontPath, const Color& textColor, \
            const int maxChar = 256, const int maxWidth = 0, const bool wrapping = false);

        TextField(const int x, const int y, const int width, const int height, \
            const Color& backColor, const Color& frameColor, const string& fontPath, \
            const Color& textColor, const int maxChar = 256, const int maxWidth = 0, \
            const bool wrapping = false);

        ~TextField(void) = default;

        void                    clear(SDL_Renderer* renderer);

        void                    removeBefore(SDL_Renderer* renderer);
        void                    removeAfter(SDL_Renderer* renderer);

        void                    add(const string& text, SDL_Renderer* renderer);

        string                  getText(void) const;

        void                    updateCursor(SDL_Renderer* renderer);
        void                    updateCursor(const int x, const int y, SDL_Renderer* renderer);

        void                    setMaxWidth(const int maxWidth) noexcept;
        void                    setWrapping(const bool wrapping) noexcept;

        void                    moveCursorForward(SDL_Renderer* renderer);
        void                    moveCursorBackward(SDL_Renderer* renderer);

        void                    render(SDL_Renderer* renderer);

		virtual void	        onMouseDown(const int x = 0, const int y = 0) override;
        virtual void	        onMouseDownDouble(const int x = 0, const int y = 0) override;
		virtual void	        onMouseDownOutside(void) override;

		virtual void	        onMouseUp(const int x = 0, const int y = 0) override;
		virtual void	        onMouseUpOutside(void) override;

		virtual void	        onMouseHover(const int x = 0, const int y = 0) override;
		virtual void	        onMouseHoverOutside(void) override;

        virtual void	        onButtonDown(const int key) override;

};

#endif
