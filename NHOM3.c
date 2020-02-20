#include <16f887.h>
#FUSES HS
#USE delay(clock=20M)

#include <DS1307.h>
#include <LCD.h>
#include <DHT11.h>

#DEFINE TIME   PIN_A0
#DEFINE CHANGE PIN_A1
#DEFINE UP     PIN_A2
#DEFINE DOWN   PIN_A3
#DEFINE ALARM  PIN_A4
#DEFINE BUZZER PIN_B2

int8 thu, ngay, thang, nam, gio, phut, giay, gio_alarm=0, phut_alarm=0, giay_alarm=0, tt_alarm=0; 
int8 t1, t2, rh1, rh2, n=0;
int  reng=0;
void set_time();
void set_alarm();
void display_dht11();

void display_set_time(int8 m)
{
   lcd_nhanlenh(0x80);
   lcd_xuatdata("Time ");
   if(m==1)
   {
      
      lcd_xuatdata("__");
   }
   else
   {
      lcd_xuatdata((gio/10)+0x30);
      lcd_xuatdata((gio%10)+0x30);
   }
   lcd_xuatdata(":");
   if(m==2)
   {
      lcd_xuatdata("__");
   }
   else
   {
      lcd_xuatdata((phut/10)+0x30);
      lcd_xuatdata((phut%10)+0x30);
   }
   lcd_xuatdata(":");
   if(m==3)
   {
      lcd_xuatdata("__");
   }
   else
   {
      lcd_xuatdata((giay/10)+0x30);
      lcd_xuatdata((giay%10)+0x30);
   }
   lcd_nhanlenh(0xC0);
   lcd_xuatdata("Date ");
   if(m==4)
   {
      lcd_xuatdata("___");
   }
   else
   {
      switch(thu)
      {
         case 1: lcd_xuatdata("Sun");
                 break; 
         case 2: lcd_xuatdata("Mon");
                 break;
         case 3: lcd_xuatdata("Tue");
                 break;
         case 4: lcd_xuatdata("Wed");
                 break;
         case 5: lcd_xuatdata("Thu");
                 break;
         case 6: lcd_xuatdata("Fri");
                 break;
         case 7: lcd_xuatdata("Sat");
                 break;
      }
   }
   lcd_xuatdata(" ");
   if(m==5)
   {
      lcd_xuatdata("__");
   }
   else
   {
      lcd_xuatdata((ngay/10)+0x30);
      lcd_xuatdata((ngay%10)+0x30);
   }
   lcd_xuatdata("-");
   if(m==6)
   {
      lcd_xuatdata("__");
   }
   else
   {
      lcd_xuatdata((thang/10)+0x30);
      lcd_xuatdata((thang%10)+0x30);
   }
   lcd_xuatdata("-");
   if(m==7)
   {
      lcd_xuatdata("__");
   }
   else
   {
      lcd_xuatdata((nam/10)+0x30);
      lcd_xuatdata((nam%10)+0x30);
   }
}

void display_set_alarm(int8 m)
{
   lcd_nhanlenh(0x80);
   lcd_xuatdata("                 ");
   if(m==1)
   {
      lcd_xuatdata("___");
   }
   else
   {
      if(tt_alarm==1)
      {
         lcd_xuatdata("On ");
      }
      else
         lcd_xuatdata("Off");
   }
   lcd_nhanlenh(0xC0);
   lcd_xuatdata("       ");
   if(m==2)
   {
      lcd_xuatdata("__");
   }
   else
   {
      lcd_xuatdata((gio_alarm/10)+0x30);
      lcd_xuatdata((gio_alarm%10)+0x30);
   }
   lcd_xuatdata(":");
   if(m==3)
   {
      lcd_xuatdata("__");
   }
   else
   {
      lcd_xuatdata((phut_alarm/10)+0x30);
      lcd_xuatdata((phut_alarm%10)+0x30);
   }
   lcd_xuatdata(":");
   if(m==4)
   {
      lcd_xuatdata("__");
   }
   else
   {
      lcd_xuatdata((giay_alarm/10)+0x30);
      lcd_xuatdata((giay_alarm%10)+0x30);
   }
   lcd_xuatdata("  ");
}  

void set_time()
{
   int8 i=1,j=0;
   ds1307_gettime2(gio, phut, giay);
   ds1307_gettime1(thu, ngay, thang, nam);
   while(true)
   {
      if(j<25)
         display_set_time(0);
      else
         display_set_time(i);
         j++;
         if(j>=50)
         j=0;
      if(input(UP)==0)
      {
         while(input(UP)==0);
         j=0;
         switch(i)
         {
            case 1: if(gio<23) 
                       gio++;
                    else
                       gio=0;
                    break;   
            case 2: if(phut<59) 
                       phut++;
                    else
                       phut=0;
                    break;
            case 3: if(giay<59) 
                       giay++;
                    else
                       giay=0;
                    break;
            case 4: if(thu<7) 
                       thu++;
                    else
                       thu=1;
                    break;
            case 5: if(ngay<31) 
                       ngay++;
                    else
                       ngay=1;
                    break;        
            case 6: if(thang<12) 
                       thang++;
                    else
                       thang=1;
                    break;
            case 7: if(nam<99) 
                       nam++;
                    else
                       nam=0;
                    break;        
         }
      }
      if(input(DOWN)==0)
      {
         while(input(DOWN)==0);
         j=0;
         switch(i)
            {
               case 1: if(gio>0) 
                          gio--;
                       else
                          gio=23;
                       break;   
               case 2: if(phut>0) 
                          phut--;
                       else
                          phut=59;
                       break;
               case 3: if(giay>0) 
                          giay--;
                       else
                          giay=59;
                       break;
               case 4: if(thu>1) 
                          thu--;
                       else
                          thu=7;
                       break;        
               case 5: if(ngay>1) 
                          ngay--;
                       else
                          ngay=31;
                       break;
               case 6: if(thang>0) 
                          thang--;
                       else
                          thang=12;
                       break;
               case 7: if(nam>0) 
                          nam--;
                       else
                          nam=99;
                       break;        
            }
      }
      if(input(CHANGE)==0)
      {
         while(input(CHANGE)==0);
         j=25;
         i++;
         if(i>7)
         i=1;
      }
      if(input(TIME)==0)
      {
         while(input(TIME)==0);
         break;
      }
   }
   ds1307_settime(thu, ngay, thang, nam, gio, phut, giay);
}

void set_alarm()
{
   int8 i=1,j=0;
   while(true)
   {
      if(j<25)
         display_set_alarm(0);
      else
         display_set_alarm(i);
         j++;
         if(j>=50)
         j=0;
      if(input(UP)==0)
      {
         while(input(UP)==0);
         j=0;
         switch(i)
            {
               case 1: if(tt_alarm<1) 
                          tt_alarm++;
                       else
                          tt_alarm=0;
                       break;  
               case 2: if(gio_alarm<23)
                          gio_alarm++;
                       else
                          gio_alarm=0;
                       break;   
               case 3: if(phut_alarm<59) 
                          phut_alarm++;
                       else
                          phut_alarm=0;
                       break;
               case 4: if(giay_alarm<59) 
                          giay_alarm++;
                       else
                          giay_alarm=0;
                       break;      
            }
      }
      if(input(DOWN)==0)
      {
         while(input(DOWN)==0);
         j=0;
         switch(i)
            {
               case 1: if(tt_alarm>0) 
                          tt_alarm--;
                       else
                          tt_alarm=1;
                       break;  
               case 2: if(gio_alarm>0) 
                          gio_alarm--;
                       else
                          gio_alarm=23;
                       break;   
               case 3: if(phut_alarm>0) 
                          phut_alarm--;
                       else
                          phut_alarm=59;
                       break;
               case 4: if(giay_alarm>0) 
                          giay_alarm--;
                       else
                          giay_alarm=59;
                       break;     
            }
      }
      if(input(CHANGE)==0)
      {
         while(input(CHANGE)==0);
         j=25;
         i++;
         if(i>4)
         i=1;
      }
      if(input(ALARM)==0)
      {
         while(input(ALARM)==0);
         break;
      }
   }
} 

void display_dht11()
{
   start_1wire();
   check_response();
   if(k==1)
   {
      read_dht11(t1,t2,rh1,rh2);    
      lcd_nhanlenh(0x94);
      lcd_xuatdata("   Temp ");
      lcd_xuatdata((t1/10)+0x30);
      lcd_xuatdata((t1%10)+0x30);   
      lcd_xuatdata(223);     
      lcd_xuatdata("C");    
      lcd_nhanlenh(0xD4);
      lcd_xuatdata("   Humi ");     
      lcd_xuatdata((rh1/10)+0x30);    
      lcd_xuatdata((rh1%10)+0x30);   
      lcd_xuatdata("%");
   }
   else
   {
      lcd_nhanlenh(0x94);
      lcd_xuatdata("  DHT11");
      lcd_nhanlenh(0xD4);
      lcd_xuatdata("  KHONG PHAN HOI");
   }
}

#int_timer1
void count1s()
{
   set_timer1(3036);
   n++;
}


void main()
{
   set_tris_A(0xFF);
   set_tris_D(0x00);
   set_tris_E(0x00); 
   ds1307_init();
   lcd_setup();
   //lcd_nhanlenh(0x91);  
   //lcd_xuatdata("OFF");
   setup_timer_1(T1_internal | t1_div_by_8);
   set_timer1(3036);
   enable_interrupts(global);
   enable_interrupts(int_timer1);
   while(true)
   {
      ds1307_gettime2(gio, phut, giay);
      ds1307_gettime1(thu, ngay, thang, nam);
      display_set_time(0);
      lcd_nhanlenh(0x91);
      if(tt_alarm==0)
      {
         lcd_xuatdata("Off");
      }
      else
      {
      lcd_xuatdata("On");
      }
      if(n>=50)
      {
         n=0;
         display_dht11();
      }
      if(gio==gio_alarm && phut==phut_alarm && giay==giay_alarm && tt_alarm==1)
      {
         output_high(BUZZER);
         reng=1;
      }
      if(input(TIME)==0)
      {
         while(input(TIME)==0);
         set_time();
      }
      if(input(ALARM)==0)
      {
         while(input(ALARM)==0);
         if(reng==1)
         {
            output_low(BUZZER);
            reng=0;           
         }
         else
         set_alarm();
         }
   }
}


