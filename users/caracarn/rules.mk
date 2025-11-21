SRC += caracarn.c
SRC += definitions/keycodes.c
INTROSPECTION_KEYMAP_C = caracarn.c
INTROSPECTION_KEYMAP_C = $(USER_PATH)/definitions/keycodes.c
INTROSPECTION_KEYMAP_C = $(USER_PATH)/features/tapdance.c

ifneq ($(PLATFORM),CHIBIOS)
    ifneq ($(strip $(LTO_SUPPORTED)), no)
        LTO_ENABLE        = yes
    endif
endif

SECRETS_ENABLE ?= no
ifeq ($(strip $(SECRETS_ENABLE)), yes)
    SRC += $(USER_PATH)/features/secrets.c
    OPT_DEFS += -DSECRETS_ENABLE
endif

COMBO_ENABLE ?= no
ifeq ($(strip $(COMBO_ENABLE)), yes)
    SRC += $(USER_PATH)/features/combos.c
    OPT_DEFS += -DCOMBO_ENABLE
endif

GQT_ENABLE ?= no
ifeq ($(strip $(GQT_ENABLE)), yes)
    SRC += $(USER_PATH)/features/global_quick_tap.c
    OPT_DEFS += -DGQT_ENABLE
endif

TAP_FLOW_ENABLE ?= no
ifeq ($(strip $(TAP_FLOW_ENABLE)), yes)
    OPT_DEFS += -DTAP_FLOW_ENABLE
endif

ACHORDION_ENABLE ?= no
ifeq ($(strip $(ACHORDION_ENABLE)), yes)
    SRC += $(USER_PATH)/features/achordion.c
    OPT_DEFS += -DACHORDION_ENABLE
endif

SMART_CASE_ENABLE ?= no
ifeq ($(strip $(SMART_CASE_ENABLE)), yes)
    SRC += $(USER_PATH)/features/smart_case.c
    OPT_DEFS += -DSMART_CASE_ENABLE
endif

CASEMODE_ENABLE ?= no
ifeq ($(strip $(CASEMODE_ENABLE)), yes)
    SRC += $(USER_PATH)/features/casemodes.c
    OPT_DEFS += -DCASEMODE_ENABLE
endif

CUSTOM_ONESHOT_MODS_ENABLE ?= no
ifeq ($(strip $(CUSTOM_ONESHOT_MODS_ENABLE)), yes)
    SRC += $(USER_PATH)/features/custom_oneshot_mods.c
    OPT_DEFS += -DCUSTOM_ONESHOT_MODS_ENABLE
endif

SMART_THUMB_KEYS_ENABLE ?= no
ifeq ($(strip $(SMART_THUMB_KEYS_ENABLE)), yes)
    SRC += $(USER_PATH)/features/smart_thumb_keys.c
    OPT_DEFS += -DSMART_THUMB_KEYS_ENABLE
endif

CAPSWORD_ENABLE ?= no
ifeq ($(strip $(CAPSWORD_ENABLE)), yes)
    SRC += $(USER_PATH)/features/caps_word.c
    OPT_DEFS += -DCAPSWORD_ENABLE
endif

TAPHOLD_ENABLE ?= no
ifeq ($(strip $(TAPHOLD_ENABLE)), yes)
    SRC += $(USER_PATH)/features/taphold.c
    OPT_DEFS += -DTAPHOLD_ENABLE
endif

DEFAULT_MOD_KEY_ENABLE ?= no
ifeq ($(strip $(DEFAULT_MOD_KEY_ENABLE)), yes)
    SRC += $(USER_PATH)/features/default_mod_key.c
    OPT_DEFS += -DDEFAULT_MOD_KEY_ENABLE
endif

CAPITALIZE_KEY_ENABLE ?= no
ifeq ($(strip $(CAPITALIZE_KEY_ENABLE)), yes)
    SRC += $(USER_PATH)/features/capitalize_key.c
    OPT_DEFS += -DCAPITALIZE_KEY_ENABLE
endif

CAPSLOCK_TIMER_ENABLE ?= no
ifeq ($(strip $(CAPSLOCK_TIMER_ENABLE)), yes)
    SRC += $(USER_PATH)/features/capslock_timer.c
    OPT_DEFS += -DCAPSLOCK_TIMER_ENABLE
endif

OS_TOGGLE_ENABLE ?= no
ifeq ($(strip $(OS_TOGGLE_ENABLE)), yes)
    SRC += $(USER_PATH)/features/os_toggle.c
    OPT_DEFS += -DOS_TOGGLE_ENABLE
endif

MACRO_ENABLE ?= no
ifeq ($(strip $(MACRO_ENABLE)), yes)
    SRC += $(USER_PATH)/features/macros.c
    OPT_DEFS += -DMACRO_ENABLE
endif

DYNAMIC_MACRO_ENABLE ?= no
ifeq ($(strip $(DYNAMIC_MACRO_ENABLE)), yes)
    SRC += $(USER_PATH)/features/dynamic_macro.c
    OPT_DEFS += -DDYNAMIC_MACRO_ENABLE
endif

SELECT_WORD_ENABLE ?= no
ifeq ($(strip $(SELECT_WORD_ENABLE)), yes)
    SRC += $(USER_PATH)/features/select_word.c
    OPT_DEFS += -DSELECT_WORD_ENABLE
endif

WINDOW_SWAPPER_ENABLE ?= no
ifeq ($(strip $(WINDOW_SWAPPER_ENABLE)), yes)
    SRC += $(USER_PATH)/features/window_swapper.c
    OPT_DEFS += -DWINDOW_SWAPPER_ENABLE
endif

CUSTOM_LEADER_ENABLE ?= no
ifeq ($(strip $(CUSTOM_LEADER_ENABLE)), yes)
    SRC += $(USER_PATH)/features/leader.c
    OPT_DEFS += -DCUSTOM_LEADER_ENABLE
endif

SHORTCUTS_ENABLE ?= no
ifeq ($(strip $(SHORTCUTS_ENABLE)), yes)
    SRC += $(USER_PATH)/features/custom_shortcuts.c
    OPT_DEFS += -DSHORTCUTS_ENABLE
endif

CUSTOM_SHIFT_ENABLE ?= no
ifeq ($(strip $(CUSTOM_SHIFT_ENABLE)), yes)
    SRC += $(USER_PATH)/features/custom_shift.c
    OPT_DEFS += -DCUSTOM_SHIFT_ENABLE
endif

RGB_MATRIX_CUSTOM ?= no
ifeq ($(strip $(RGB_MATRIX_CUSTOM)), yes)
	SRC += $(USER_PATH)/features/rgb_matrix_custom.c
	OPT_DEFS += -DRGB_MATRIX_CUSTOM_ENABLED
endif

EOS_ENABLE?= no
ifeq ($(strip $(EOS_ENABLE)), yes)
	SRC += $(USER_PATH)/features/eos_util.c
	OPT_DEFS += -DEOS_ENABLE
endif

OLED_MENU_ENABLE?= no
ifeq ($(strip $(OLED_MENU_ENABLE)), yes)
	SRC += $(USER_PATH)/features/oled_menu.c
	SRC += $(USER_PATH)/features/rgb_matrix_keys.c
	OPT_DEFS += -DOLED_MENU_ENABLE
endif

QMENU_ENABLE?= no
ifeq ($(strip $(QMENU_ENABLE)), yes)
	SRC += $(USER_PATH)/features/qmenu.c
	SRC += $(USER_PATH)/features/qkeys.c
	SRC += $(USER_PATH)/features/qhelper.c
	OPT_DEFS += -DQMENU_ENABLE
endif

ifdef HLC_TFT_DISPLAY
	SRC += $(USER_PATH)/features/qpainter.c
	SRC += $(USER_PATH)/features/mononoki.qff.c
	SRC += $(USER_PATH)/features/kyria_logo-mono.qgf.c
	SRC += $(USER_PATH)/fonts/bigbluetermmono.qff.c
	SRC += $(USER_PATH)/images/glyphs.qgf.c
	include $(USER_PATH)/splitkb/rules.mk
	POST_CONFIG_H += $(USER_PATH)/splitkb/config.h
endif

CUSTOM_SPLIT_TRANSPORT_SYNC ?= yes
ifeq ($(strip $(CUSTOM_SPLIT_TRANSPORT_SYNC)), yes)
    ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
        QUANTUM_LIB_SRC += $(USER_PATH)/features/transport_sync.c
        OPT_DEFS += -DCUSTOM_SPLIT_TRANSPORT_SYNC
    endif

endif

ifeq ($(strip $(RAW_ENABLE)), yes)
	ifeq ($(strip $(CONVERT_TO)), bonsai_c4)
		override RAW_ENABLE = no
	endif
endif

ifeq ($(strip $(ENCODER_ENABLE)), yes)
	ifeq ($(strip $(CONVERT_TO)), bonsai_c4)
		override ENCODER_ENABLE = no
	endif
endif

ifeq ($(strip $(ENCODER_MAP_ENABLE)), yes)
	ifeq ($(strip $(CONVERT_TO)), bonsai_c4)
		override ENCODER_MAP_ENABLE = no
	endif
endif

