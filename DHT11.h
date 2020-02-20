
#BIT dht11_data = 0x07.7
#BIT dht11_direction = 0x87.7

int k=0;
void read_dht11(unsigned int8 &t_byte1, &t_byte2, &rh_byte1, &rh_byte2);
void start_1wire()
{
dht11_direction = 0;
dht11_data = 1;
delay_ms(30);
dht11_data = 0;
delay_ms(18);
dht11_data = 1;
delay_us(50);
dht11_direction = 1;
}

void check_response()
{
if(dht11_data) 
k=0;
else 
while(!(dht11_data));
delay_us(60);
if(!dht11_data)
k=0;
else 
k=1;
while((dht11_data));
}

void read_dht11(unsigned int8 &t_byte1, &t_byte2, &rh_byte1, &rh_byte2)
{
unsigned int8 i, j, checksum;
unsigned int8 bytes_dht11[5]={0,0,0,0,0};
for(i=0;i<5;i++)
{
   for(j=0;j<8;j++)
   {
      while(!(dht11_data));
      {
          delay_us(50);
          if(dht11_data)
          {
             bytes_dht11[i]|=(1<<(7-j));
             while((dht11_data));
          }
      }
   }
}
checksum=bytes_dht11[0]+bytes_dht11[1]+bytes_dht11[2]+bytes_dht11[3];
if(checksum!=bytes_dht11[4])
k=0;
t_byte1=bytes_dht11[2];
t_byte2=bytes_dht11[3];
rh_byte1=bytes_dht11[0];
rh_byte2=bytes_dht11[1];
}
