#pragma once

#include QMK_KEYBOARD_H
#include "caracarn.h"
#include "quantum.h"

typedef enum {
    LIGHTING_HEADING,
    MENU_FLAGS,
    MENU_SPEED,
    MENU_HUE,
    MENU_SAT,
    MENU_VAL,
    MENU_RGBMODE,
    LIGHTING_END
} qmenu_lighting_t;

extern qmenu_lighting_t qmenu_lighting;

typedef enum {
    MODTAP_HEADING,
    MENU_STT,
    MENU_TT,
    MENU_MT,
#ifdef ACHORDION_ENABLE
    MENU_AT,
#endif
#if defined(GQT_ENABLE) || defined(TAP_FLOW_ENABLE)
    MENU_GQT,
    MENU_SGQT,
#endif
    MODTAP_END
} qmenu_modtap_t;

extern qmenu_modtap_t qmenu_modtap;

typedef enum {
    KB_HEADING,
    MENU_DEFAULTLAYER,
    MENU_OSFLAG,
    MENU_DEBUG,
    MENU_NKRO,
    MENU_EECLEAR,
    MENU_BOOTLOADER,
    KB_END
} qmenu_kb_t;

extern qmenu_kb_t qmenu_kb;

typedef enum {
    PAINTER_HEADING,
    MENU_PHUE,
    MENU_PSAT,
    MENU_PVAL,
    MENU_SHUE,
    MENU_SSAT,
    MENU_SVAL,
    PAINTER_END
} qmenu_painter_t;

extern qmenu_painter_t qmenu_painter;

typedef enum {
    SUBMENU_OFF,
    SUBMENU_LIGHTING,
    SUBMENU_MODTAP,
    SUBMENU_PAINTER,
    SUBMENU_KB
} qsubmenu_t;

extern qsubmenu_t qsubmenu;

void render_menu(void);
bool dyn_display;
int start_index;
void qmenu_timer(void);
