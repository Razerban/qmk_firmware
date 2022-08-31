# Build Options
#   change yes to no to disable
BOOTMAGIC_ENABLE  = no                                # Virtual DIP switch configuration
MOUSEKEY_ENABLE   = no                                # Mouse keys
EXTRAKEY_ENABLE   = yes                               # Audio control and System control
CONSOLE_ENABLE    = no                                # Console for debug
COMMAND_ENABLE    = no                                # Commands for debug and configuration

TAP_DANCE_ENABLE  = yes

SRC += custom_keycodes.c tap_dance.c

ifeq (,$(findstring xwhatsit/, $(strip $(KEYBOARD)))) # Add the EnterBootloader communication protocol only if the firmware isn't XWhatsit's
    RAW_ENABLE    = yes                               # Enable RAW_HID capabilities
    SRC          += comm_protocol.c
endif
