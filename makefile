# ----------------------------
# Makefile Options
# ----------------------------

NAME = SHADE
ICON = icon.png
DESCRIPTION = "Move the Car into the Shade"
COMPRESSED = YES
ARCHIVED = YES

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)

