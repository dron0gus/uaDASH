#
# Makefile
#
CC 				?= gcc
AS				?= as
PROJ_DIR 		?= $(abspath .)
LVGL_DIR	 	?= $(PROJ_DIR)/lvgl
UI_DIR			?= $(PROJ_DIR)/export
APP_DIR			?= $(PROJ_DIR)

DDEFS			:= -DLINUX_BUILD=1
DDEFS			+= -DLV_USE_LINUX_DRM=1

WARNINGS		:= -Wall -Wshadow -Wundef -Wmissing-prototypes -Wno-discarded-qualifiers -Wall -Wextra -Wno-unused-function -Wno-error=strict-prototypes -Wpointer-arith \
					-fno-strict-aliasing -Wno-error=cpp -Wuninitialized -Wmaybe-uninitialized -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess \
					-Wno-format-nonliteral -Wno-cast-qual -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wformat-security -Wno-ignored-qualifiers -Wno-error=pedantic \
					-Wno-sign-compare -Wno-error=missing-prototypes -Wdouble-promotion -Wclobbered -Wdeprecated -Wempty-body -Wtype-limits -Wshift-negative-value -Wstack-usage=2048 \
					-Wno-unused-value -Wno-unused-parameter -Wno-missing-field-initializers -Wuninitialized -Wmaybe-uninitialized -Wall -Wextra -Wno-unused-parameter \
					-Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wpointer-arith -Wno-cast-qual -Wmissing-prototypes \
					-Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wno-discarded-qualifiers -Wformat-security -Wno-ignored-qualifiers -Wno-sign-compare -std=c99

CFLAGS 			?= -O3 -g0 $(WARNINGS)
CFLAGS			+= -I$(LVGL_DIR)/
CFLAGS  		+= -I$(UI_DIR)/
CFLAGS  		+= -I$(APP_DIR)/
CFLAGS			+= -I/usr/include/drm/
CFLAGS          += $(DDEFS)
LDFLAGS 		?= -lm

LDFLAGS         += -ldrm

BIN 			= dash
BUILD_DIR 		= ./build
BUILD_OBJ_DIR 	= $(BUILD_DIR)/obj
BUILD_BIN_DIR 	= $(BUILD_DIR)/bin

prefix 			?= /usr
bindir 			?= $(prefix)/bin

#Collect the files to compile
MAINSRC = 		./main.c

APPSRC = \
	$(UI_DIR)/ui.c \
	$(UI_DIR)/ui_helpers.c \
	$(UI_DIR)/fonts/ui_font_FontIndicator.c \
	$(UI_DIR)/fonts/ui_font_FontIndicatorLabel.c \
	$(UI_DIR)/fonts/ui_font_FontLabel.c \
	$(UI_DIR)/fonts/ui_font_FontRPM.c \
	$(UI_DIR)/fonts/ui_font_FontSpeed.c \
	$(UI_DIR)/screens/ui_mainScreen.c \
	$(UI_DIR)/screens/ui_settingsScreen.c \
	$(UI_DIR)/screens/ui_benchScreen.c \
	$(UI_DIR)/components/ui_comp_hook.c \

CPPSRCS = \
	$(APP_DIR)/events.cpp \
	$(APP_DIR)/updaters.cpp \
	$(APP_DIR)/display_driver.cpp

#	$(APP_DIR)/screens/ui_benchScreen.c \
#	$(APP_DIR)/screens/ui_engineConfigScreen.c \

CSRCS			+=$(APPSRC)

include $(LVGL_DIR)/lvgl.mk

CSRCS 			+= mouse_cursor_icon.c 

OBJEXT 			?= .o

AOBJS 			= $(ASRCS:.S=$(OBJEXT))
COBJS 			= $(CSRCS:.c=$(OBJEXT))
CPPOBJS 		= $(CPPSRCS:.cpp=$(OBJEXT))

MAINOBJ 		= $(MAINSRC:.c=$(OBJEXT))

SRCS 			= $(MAINSRC) $(ASRCS) $(CSRCS) $(CPPSRCS)
OBJS 			= $(MAINOBJ) $(AOBJS) $(COBJS) $(CPPOBJS)
TARGET 			= $(addprefix $(BUILD_OBJ_DIR)/, $(patsubst ./%, %, $(OBJS)))

## MAINOBJ -> OBJFILES

all: default

$(BUILD_OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC)  $(CFLAGS) -c $< -o $@
	@echo "CC $<"

$(BUILD_OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CXX)  $(CFLAGS) -c $< -o $@
	@echo "CXX $<"

$(BUILD_OBJ_DIR)/%.o: %.S
	@mkdir -p $(dir $@)
	@$(AS) -c $< -o $@
	@echo "AS $<"

default: $(TARGET)
	@mkdir -p $(dir $(BUILD_BIN_DIR)/)
	$(CC) -o $(BUILD_BIN_DIR)/$(BIN) $(TARGET) $(LDFLAGS)

clean: 
	rm -rf $(BUILD_DIR)

install:
	install -d $(DESTDIR)$(bindir)
	install $(BUILD_BIN_DIR)/$(BIN) $(DESTDIR)$(bindir)

uninstall:
	$(RM) -r $(addprefix $(DESTDIR)$(bindir)/,$(BIN))
