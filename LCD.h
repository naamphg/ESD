//#include <16F887.h>

#IFNDEF lcd_rs
#DEFINE lcd_rs PIN_E0
#ENDIF

#IFNDEF lcd_rw
#DEFINE lcd_rw PIN_E1
#ENDIF

#IFNDEF lcd_e
#DEFINE lcd_e PIN_E2
#ENDIF

#IFNDEF output_lcd
#DEFINE output_lcd output_D
#ENDIF

#DEFINE clear_lcd 0x01
#DEFINE entry_set 0x06
#DEFINE display_control 0x0C
#DEFINE function_set 0x38
#DEFINE shift_left 0x18
#DEFINE shift_right 0x1C
#DEFINE first_line1 0x80
#DEFINE first_line2 0xC0
#DEFINE first_line3 0x94
#DEFINE first_line4 0xD4

void lcd_nhanlenh(unsigned char ln)
{
output_low(lcd_rs);
output_lcd(ln);
output_low(lcd_e);
delay_us(50);
output_high(lcd_e);
delay_us(50);
}

void lcd_xuatdata(unsigned char dx)
{
output_high(lcd_rs);
output_lcd(dx);
output_low(lcd_e);
delay_us(50);
output_high(lcd_e);
delay_us(50);
}

void lcd_setup()
{
output_low(lcd_rs);
output_low(lcd_rw);
output_low(lcd_e);
lcd_nhanlenh(clear_lcd);
delay_ms(1);
lcd_nhanlenh(entry_set);
delay_ms(1);
lcd_nhanlenh(display_control);
delay_ms(1);
lcd_nhanlenh(function_set);
delay_ms(1);
}

