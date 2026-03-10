#ifndef VALUEFIELD_HPP
# define VALUEFIELD_HPP

# include "Text.hpp"
# include "Shape.hpp"
# include "Element.hpp"

class ValueField : public Element
{
    private:
        size_t                  _maxChar = 256;

        string                  _fontPath;
        Color                   _textColor;
        optional<Text>          _mainText;

        size_t                  _cursorPos = 0;
        optional<Shape>         _cursor;

        optional<Shape>         _textFocus;
        optional<Shape>         _background;

        int                     _originalWidth = 0;
        int                     _originalHeight = 0;

        string                  _lastError;

        void                    joinValue(const string& text, SDL_Renderer* renderer);
        void                    createValue(const string& text, SDL_Renderer* renderer);

        bool                    validateValue(const string& text);

    protected:
		virtual void	        onPropertiesChanged(SDL_Renderer* renderer) override;
        virtual void	        onPositionChanged(SDL_Renderer* renderer) override;

		virtual void	        onStyleChanged(void) override;

		virtual void	        onSettingsChanged(void) override;
		virtual void	        onStateChanged(void) override;

    public:
        ValueField(void) = delete;

        ValueField(const int x, const int y, const int width, const int height, \
            const Color& backColor, const Color& frameColor, const string& fontPath, \
            const Color& textColor, const int maxChar = 256);

        ~ValueField(void) = default;

        string                  getLastError(void);

        void                    clear(SDL_Renderer* renderer);

        void                    removeBefore(SDL_Renderer* renderer);
        void                    removeAfter(SDL_Renderer* renderer);

        void                    add(const string& text, SDL_Renderer* renderer);

        void                    increase(void);
        void                    decrease(void);

        int                     getValue(void) const;

        void                    updateCursor(SDL_Renderer* renderer);
        void                    updateCursor(const int x, const int y, SDL_Renderer* renderer);

        void                    moveCursorForward(SDL_Renderer* renderer);
        void                    moveCursorBackward(SDL_Renderer* renderer);

        void                    render(SDL_Renderer* renderer);

		virtual void	        onMouseDown(const int x = 0, const int y = 0, SDL_Renderer* renderer = nullptr) override;
        virtual void	        onMouseDownDouble(const int x = 0, const int y = 0, SDL_Renderer* renderer = nullptr) override;
		virtual void	        onMouseDownOutside(SDL_Renderer* renderer) override;

        virtual void            onMouseUp(const int x, const int y, SDL_Renderer* renderer) override;

		virtual void	        onMouseHover(const int x = 0, const int y = 0, SDL_Renderer* renderer = nullptr) override;
		virtual void	        onMouseHoverOutside(SDL_Renderer* renderer = nullptr) override;

        virtual void	        onButtonDown(const int key, SDL_Renderer* renderer = nullptr) override;
};

#endif
