#ifndef MACROS_HPP
# define MACROS_HPP

/* UI config */

# define MIN_WINDOW_W 300
# define MIN_WINDOW_H 150

# define MAX_BUTTONS 4

# define HIGHLIGHT_OPACITY 100
# define FOCUS_OPACITY 200

# define CURSOR_WIDTH 1
# define DEF_SELECT_COLOR BLUE

/* DialogBox paramaters */

# define DARK_MODE 1
# define LIGHT_MODE 0

/* State */

# define NONE 0
# define DEFAULT 21
# define OK 42
# define END 84
# define RETURN 168

/* Render values */

# define BORDER_SELECT 21
# define CORNER_SELECT 22
# define CENTER_SELECT_X 23
# define HIGHLIGHT_SELECT 24

/* UI Ratios */

# define TITLE_RATIO 0.10f
# define TEXT_RATIO 0.08f

# define LIMIT_RATIO 0.05f
# define LIMIT_HEIGHT 1

/* UI Colors */

# define WHITE {255, 255, 255, 255}
# define BLACK {0, 0, 0, 255}

# define RED {255, 0, 0, 255}
# define GREEN {0, 255, 0, 255}
# define BLUE {0, 0, 255, 255}
# define YELLOW {255, 255, 0, 255}

/* Text colors */

# define RED_TXT "\033[31m"
# define GREEN_TXT "\033[32m"
# define GREY_TXT "\033[90m"

# define END_COLOR "\033[0m"

#endif
