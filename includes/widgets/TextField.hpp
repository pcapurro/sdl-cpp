#ifndef TEXTFIELD_HPP
# define TEXTFIELD_HPP

# include "Text.hpp"
# include "Shape.hpp"
# include "Element.hpp"

class TextField : public Element
{
    private:
        string                  _fontPath;
        Color                   _textColor;
        optional<Text>          _mainText;

        size_t                  _cursorPos = 0;
        optional<Shape>         _cursor;

        optional<Shape>         _textFocus;
        optional<Shape>         _background;

        int                     _originalWidth = 0;
        int                     _originalHeight = 0;

        size_t                  _maxChar = 256;
        bool                    _wrapping = false;

        string                  _lastError;

        static constexpr int    CursorWidth = 1;

        void                    joinText(const string& text, SDL_Renderer* renderer);
        void                    createText(const string& text, SDL_Renderer* renderer);

    protected:
		virtual void	        onPropertiesChanged([[maybe_unused]] SDL_Renderer* renderer) override;
        virtual void	        onPositionChanged([[maybe_unused]] SDL_Renderer* renderer) override;

		virtual void	        onStyleChanged(void) override;

		virtual void	        onSettingsChanged(void) override;
		virtual void	        onStateChanged(void) override;

    public:
        TextField(const int x, const int y, const int width, const int height, \
            const Color& backColor, const Color& frameColor, const string& fontPath, \
            const Color& textColor, const int maxChar = 256, const bool wrapping = false);

        ~TextField(void) = default;

        bool                    empty(void) const;
        string                  getText(void) const;
        string                  getLastError(void);

        void                    clear(SDL_Renderer* renderer);

        void                    removeBefore(SDL_Renderer* renderer);
        void                    removeAfter(SDL_Renderer* renderer);

        void                    add(const string& text, SDL_Renderer* renderer);

        void                    updateCursor(SDL_Renderer* renderer);
        void                    updateCursor(const int x, const int y, SDL_Renderer* renderer);

        void                    setWrapping(const bool wrapping) noexcept;

        void                    moveCursorForward(SDL_Renderer* renderer);
        void                    moveCursorBackward(SDL_Renderer* renderer);

        void                    render(SDL_Renderer* renderer);

		virtual void	        onMouseDown([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
        virtual void	        onMouseDownDouble([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
		virtual void	        onMouseDownOutside([[maybe_unused]] SDL_Renderer* renderer = nullptr) override;

        virtual void	        onMouseUp([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;

		virtual void	        onMouseHover([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
		virtual void	        onMouseHoverOutside([[maybe_unused]] SDL_Renderer* renderer = nullptr) override;

        virtual void	        onButtonDown([[maybe_unused]] const int key = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
};

#endif
