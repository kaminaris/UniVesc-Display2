SET(SOURCES screens/ui_mainScreen.c
    screens/ui_setClockScreen.c
    ui.c
    ui_helpers.c)

add_library(ui ${SOURCES})
