#ifndef COLOR_HPP
# define COLOR_HPP

# include "Global.hpp"

class Color
{
	public:
		uint8_t						r = 0;
		uint8_t						g = 0;
		uint8_t						b = 0;

		uint8_t						a = 255;

		constexpr Color() noexcept = default;
		constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) noexcept : \
			r(r), g(g), b(b), a(a) {};

		bool						operator==(const Color& other) const;
		bool						operator!=(const Color& other) const;

		Uint32						toUint32t(const SDL_PixelFormat* format) const noexcept;
		SDL_Color					toSDLColor(void) const noexcept;
		Color 						toNewOpacity(const uint8_t opacity) const noexcept;
		int							getAverage(void) const noexcept;

		void						setColor(const uint8_t r, const uint8_t g, \
			const uint8_t b, const uint8_t a = 255) noexcept;

		static Uint32				toUint32t(const Color& color, \
										const SDL_PixelFormat* format) noexcept;
		static SDL_Color			toSDLColor(const Color& color) noexcept;
		static int					getAverage(const Color& color) noexcept;

		static void					colorSurface(const Color& color, SDL_Surface* surface);

		static const Color	White;
		static const Color	Black;

		static const Color	Red;
		static const Color	Green;
		static const Color	Blue;
		static const Color	Yellow;

		static const Color	GreyLight;
		static const Color	GreyDark;

		static const Color	Invisible;
};


inline constexpr Color      Color::White{255, 255, 255, 255};
inline constexpr Color      Color::Black{0, 0, 0, 255};

inline constexpr Color      Color::Red{255, 0, 0, 255};
inline constexpr Color      Color::Green{0, 255, 0, 255};
inline constexpr Color      Color::Blue{0, 0, 255, 255};
inline constexpr Color      Color::Yellow{255, 255, 0, 255};

inline constexpr Color      Color::GreyLight{200, 200, 200, 255};
inline constexpr Color      Color::GreyDark{128, 128, 128, 255};

inline constexpr Color      Color::Invisible{0, 0, 0, 0};

#endif
