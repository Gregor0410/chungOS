#ifndef VGA_TEXT_H
#define VGA_TEXT_H
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
void write_char_at_cursor(char text,uint8_t color);
uint16_t get_cursor();
void set_cursor(uint16_t cursor);
void write_char_at_location(char text,uint8_t color,uint16_t position);
void vga_scroll();
void clear_screen();
#endif