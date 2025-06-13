# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a QMK (Quantum Mechanical Keyboard) firmware project for the Inland MK47, a 40% (47-key) hot-swappable RGB mechanical keyboard. The keyboard uses the Planck MIT layout with WB32FQ95 processor and SNLED27351 RGB driver.

## Build Commands

### Building firmware:
```bash
make inland/mk47:default
```

### Flashing firmware to keyboard:
```bash
make inland/mk47:default:flash
```

## Architecture

### Key Files Structure:
- `keyboard.json` - Main keyboard configuration (matrix, features, RGB layout)
- `mk47.c` - Hardware-specific code including RGB LED mapping
- `config.h` - Hardware configuration (SPI, I2C settings)
- `keymaps/default/keymap.c` - Default keymap with 4 layers and RGB effects
- `mk47.layout.json` - VIA configuration file for visual keymap editing

### Hardware Configuration:
- **Processor**: WB32FQ95 with wb32-dfu bootloader
- **Matrix**: 4x12 (ROW2COL) with position [3,6] unused (MIT layout)
- **RGB**: 47 LEDs using SNLED27351 driver at I2C address GND
- **Features**: RGB matrix, NKRO, bootmagic, extrakey support
- **Storage**: SPI flash with wear leveling for EEPROM

### Keymap Structure:
- **Layer 0**: Base QWERTY with rainbow RGB effect
- **Layer 1**: Numpad/symbols with solid yellow RGB 
- **Layer 2**: Navigation arrows with solid green RGB
- **Layer 3**: Spare layer with solid red RGB

### RGB Matrix Implementation:
The keyboard implements per-layer RGB lighting in `keymaps/default/keymap.c:95-121` using `layer_state_set_user()` function. RGB LED positions are defined in `mk47.c:19-76` following the SNLED27351 manual's CB/CA addressing scheme.

## Bootloader Access

Enter bootloader mode:
- **Bootmagic**: Hold top-left key (Escape) while plugging in
- **Keycode**: Press mapped QK_BOOT key if available