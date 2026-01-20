SET(SOURCES screens/ui_mainScreen.c
    screens/ui_settingsScreen.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    fonts/ui_font_FontIndicator.c
    fonts/ui_font_FontIndicatorLabel.c
    fonts/ui_font_FontLabel.c
    fonts/ui_font_FontRPM.c
    fonts/ui_font_FontSpeed.c)

add_library(ui ${SOURCES})
