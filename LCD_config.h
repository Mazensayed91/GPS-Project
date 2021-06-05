#ifndef LCD_DRIVER_LCD_CONFIG_H
#define LCD_DRIVER_LCD_CONFIG_H

#define CLEAR_DISPLAY        0x01
#define RETURN_HOME          0x02
#define MOVE_CURSOR_RIGHT    0x06
#define MOVE_CURSOR_LEFT     0x08
#define SHIFT_DISPLAY_RIGHT  0x1C
#define SHIFT_DISPLAY_LEFT   0x18
#define CURSOR_BLINK         0x0F
#define CURSOR_OFF           0x0C
#define CURSOR_ON            0x0E
#define FUNCTION_SET_4BIT    0x28
#define FUNCTION_SET_8BIT    0x38
#define ENTRY_MODE           0x06
#define FUNCTION_8_BIT       0x32
#define SET_5X7_FONT_SIZE    0x20
#define FIRST_ROW            0x80
#define SECOND_ROW           0xC0

#endif //LCD_DRIVER_LCD_CONFIG_H
