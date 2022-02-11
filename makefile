# ----------------------------
# Makefile Options
# ----------------------------

NAME = SHADE
ICON = icon.png
DESCRIPTION = "Move the car into the shade!"
COMPRESSED = YES
ARCHIVED = YES

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)

