#ifndef IMAGEBUTTON_HPP
# define IMAGEBUTTON_HPP

# include "Image.hpp"
# include "Shape.hpp"
# include "Element.hpp"

class ImageButton : public Element
{
    private:
        optional<Shape>         _background;
        optional<Image>         _mainImage;
        optional<Shape>         _border;

    protected:
		virtual void	        onPropertiesChanged([[maybe_unused]] SDL_Renderer* renderer) override;
        virtual void	        onPositionChanged([[maybe_unused]] SDL_Renderer* renderer) override;

		virtual void	        onStyleChanged(void) override;

		virtual void	        onSettingsChanged(void) override;
		virtual void	        onStateChanged(void) override;

    public:
        ImageButton(void) = delete;

        ImageButton(const int x, const int y, const int width, const int height, \
            const string& path, const Color& backColor, const int borderThickness, \
            const Color& borderColor, SDL_Renderer* renderer);

        ~ImageButton(void) = default;

        void                    render(SDL_Renderer* renderer);

		virtual void	        onMouseDown([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
		virtual void	        onMouseDownOutside([[maybe_unused]] SDL_Renderer* renderer = nullptr) override;

        virtual void	        onMouseUp([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;

		virtual void	        onMouseHover([[maybe_unused]] const int x = 0, [[maybe_unused]] const int y = 0, \
            [[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
		virtual void	        onMouseHoverOutside([[maybe_unused]] SDL_Renderer* renderer = nullptr) override;
};

#endif
