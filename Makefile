TARGET := main
SOURCES := main.cpp OLED_I2C/OLED_I2C.cpp OLED_I2C/DefaultFonts.c
BOARD := uno
CPPFLAGS += '-I./OLED_I2C'
include arduino.mk
