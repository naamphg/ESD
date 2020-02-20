//#include<16F887.h>

#define rtc_scl pin_C3
#define rtc_sda pin_C4
#use delay(clock=20M)
#use i2c(master, sda=rtc_sda, scl=rtc_scl)

BYTE bin2bcd(BYTE binary_value);
BYTE bcd2bin(BYTE bcd_value);

void ds1307_init(void)
{
BYTE giay = 0;
i2c_start();
i2c_write(0xD0);
i2c_write(0x00);
i2c_start();
i2c_write(0xD1);
giay = bcd2bin(i2c_read(0));
i2c_stop();
giay=giay & 0x7F;
delay_us(3);
i2c_start();
i2c_write(0xD0);
i2c_write(0x00);
i2c_write(bin2bcd(giay));
i2c_start();
i2c_write(0xD0);
i2c_write(0x07);
i2c_write(0x80);
i2c_stop();
}

void ds1307_settime(BYTE thu, BYTE ngay, BYTE thang, BYTE nam, BYTE gio, BYTE phut, BYTE giay)
{
giay=giay & 0x7F;
gio=gio & 0x3F;
i2c_start();
i2c_write(0xD0);
i2c_write(0x00);
i2c_write(bin2bcd(giay));
i2c_write(bin2bcd(phut));
i2c_write(bin2bcd(gio));
i2c_write(bin2bcd(thu));
i2c_write(bin2bcd(ngay));
i2c_write(bin2bcd(thang));
i2c_write(bin2bcd(nam));
i2c_write(0x80);
i2c_stop();
}

void ds1307_gettime1(BYTE &thu, BYTE &ngay, BYTE &thang, BYTE &nam)
{
i2c_start();
i2c_write(0xD0);
i2c_write(0x03);
i2c_start();
i2c_write(0xD1);
thu=bcd2bin(i2c_read() & 0x7F);
ngay=bcd2bin(i2c_read() & 0x3F);
thang=bcd2bin(i2c_read() & 0x1F);
nam=bcd2bin(i2c_read(0));
i2c_stop();
}

void ds1307_gettime2(BYTE &gio, BYTE &phut, BYTE &giay)
{
i2c_start();
i2c_write(0xD0);
i2c_write(0x00);
i2c_start();
i2c_write(0xD1);
giay=bcd2bin(i2c_read() & 0x7F);
phut=bcd2bin(i2c_read() & 0x7F);
gio=bcd2bin(i2c_read(0) & 0x3F);
i2c_stop();
}

BYTE bin2bcd(BYTE binary_value)
{
  BYTE temp;
  BYTE retval;

  temp = binary_value;
  retval = 0;

  while(true)
  {
    // Get the tens digit by doing multiple subtraction
    // of 10 from the binary value.
    if(temp >= 10)
    {
      temp -= 10;
      retval += 0x10;
    }
    else // Get the ones digit by adding the remainder.
    {
      retval += temp;
      break;
    }
  }

  return(retval);
}


// Input range - 00 to 99.
BYTE bcd2bin(BYTE bcd_value)
{
  BYTE temp;

  temp = bcd_value;
  // Shifting upper digit right by 1 is same as multiplying by 8.
  temp >>= 1;
  // Isolate the bits for the upper digit.
  temp &= 0x78;

  // Now return: (Tens * 8) + (Tens * 2) + Ones

  return(temp + (temp >> 2) + (bcd_value & 0x0f));
}
