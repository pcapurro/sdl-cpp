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
		virtual void	        onPropertiesChanged([[maybe_unused]] SDL_Renderer* renderer) override;
        virtual void	        onPositionChanged([[maybe_unused]] SDL_Renderer* renderer) override;

		virtual void	        onStyleChanged(void) override;

		virtual void	        onSettingsChanged(void) override;
		virtual void	        onStateChanged(void) override;

    public:
        TextButton(const int x, const int y, const int width, const int height, \
            const Color& backColor, const string& text, const int size, \
            const Color& textColor, const string& fontPath, SDL_Renderer* renderer);

        ~TextButton(void) = default;

        string                  getText(void) const;

        void                    render(SDL_Renderer* renderer);

		virtual void	        onMouseDown([[maybe_unused]] const bool held = false, \
            [[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
		virtual void	        onMouseDownOutside([[maybe_unused]] SDL_Renderer* renderer = nullptr) override;

        virtual void	        onMouseUp([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;

		virtual void	        onMouseHover([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
		virtual void	        onMouseHoverOutside([[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
};

#endif
