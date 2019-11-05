
#define CLK_PIN (7)
#define DIO_PIN (8)

#define bit_delay_250ns_4clk_of_16Mhz() asm("nop\n nop\n nop\n nop\n")
#define TM1637_CMD1_write_auto_inc_addr (0x40)
#define TM1637_CMD2_1st_mem_addr_7seg_1xxx (0xC0)   
#define TM1637_CMD3_ctrl_screen_head (0x80)         
int k=0;



     const uint8_t SEVEN_SEG_DIGITS[] = {
           // gfedcba
           0b00111111, // 0
           0b00000110, // 1
           0b01011011, // 2
           0b01001111, // 3
           0b01100110, // 4
           0b01101101, // 5
           0b01111101, // 6
           0b00000111, // 7
           0b01111111, // 8
           0b01101111, // 9

          
           0b00000000, // 10
           0b00000001, // 11
           0b00000011, // 12
           0b00000101, // 13
           0b00001001, // 14
           0b00010001, // 15
           0b00100001, // 16
           0b01000001, // 17
            
         
            
       };

    void tm1637_init_pin_for_sent_I2C() {
       pinMode( CLK_PIN, OUTPUT );
       pinMode( DIO_PIN, OUTPUT );
       digitalWrite( CLK_PIN, HIGH );
       digitalWrite( DIO_PIN, HIGH );
     }

    void tm1637_start_bit_I2C() {
         digitalWrite( DIO_PIN, LOW );
         bit_delay_250ns_4clk_of_16Mhz();
         digitalWrite( CLK_PIN, LOW );
         bit_delay_250ns_4clk_of_16Mhz();
     }

     void tm1637_stop_bit_I2C() {
          digitalWrite( CLK_PIN, HIGH );
          bit_delay_250ns_4clk_of_16Mhz();
          digitalWrite( DIO_PIN, HIGH );
          bit_delay_250ns_4clk_of_16Mhz();
      }

    int tm1637_send_1byte_I2C_ack( uint8_t data ) {
         uint8_t ack;
         for( uint8_t i = 0; i < 8; i++ ) {           // Send 8-bit data, LSB first
            digitalWrite( CLK_PIN, LOW );
            digitalWrite( DIO_PIN, ( data & 0x01 ) ? HIGH : 0 ); // ????????????????
            digitalWrite( CLK_PIN, HIGH );
            data >>= 1;                                    // shift bit to the right
           }
         digitalWrite( CLK_PIN, LOW );
             // I2C acknowledgement process , read ack in clolck9
         pinMode( DIO_PIN, INPUT );      // make DIO pin floating (input)
         digitalWrite( DIO_PIN, HIGH );   // enable pull-up
         digitalWrite( CLK_PIN, HIGH );   // start clock9
         ack = digitalRead( DIO_PIN );    // read ACK bit 
            // make DIO pin to output again
         digitalWrite( DIO_PIN, LOW );
         pinMode( DIO_PIN, OUTPUT );
         digitalWrite( CLK_PIN, LOW );
         return (ack==0);                                    
      }

   boolean showDigits( uint8_t digits[], boolean colon=false, uint8_t brightness=7) {
       // send the first command-----------------------
         tm1637_start_bit_I2C();
         tm1637_send_1byte_I2C_ack( TM1637_CMD1_write_auto_inc_addr );
         tm1637_stop_bit_I2C();
       // send the second command-------------------
         tm1637_start_bit_I2C();
         tm1637_send_1byte_I2C_ack( TM1637_CMD2_1st_mem_addr_7seg_1xxx );
         for ( uint8_t i=0, value; i < 6; i++ ) {
           value = SEVEN_SEG_DIGITS[ digits[i] ];
           if ( (i == 1) && colon ) {
              value |= 0x80; // turn on the colon on the display ,x1xx digit ,hundreds digit
             }
           tm1637_send_1byte_I2C_ack( value );
         }
        tm1637_stop_bit_I2C();
      // send the third command---------------------- option send only 1 time is OK---- 
        tm1637_start_bit_I2C();
        tm1637_send_1byte_I2C_ack( TM1637_CMD3_ctrl_screen_head | (brightness & 7) | 0x08 );
             // brightness [0-7] , &0x07 filter to correct brightness value (before OR with CMD3)
            // 0x08 (0b00001000) , 1 is bit cmd for open 7seg screen ,0= close screen
        tm1637_stop_bit_I2C();
     }

////////////////////////////////////////////////////////////////////////

    uint32_t ts;
    void setup() {

Serial.begin(9600);
      
       tm1637_init_pin_for_sent_I2C();
       ts = millis();   // millis() is arduino function
                            // return: Number of milliseconds since the program started (unsigned long)
                            // ts=mills() 
  pinMode(9, OUTPUT);  //pwmA
  pinMode(10, OUTPUT); //pwmB
      }
     
      // show time (hour and minute)
    void showTime( uint8_t hh, uint8_t mm, uint8_t ss, boolean colon=0 ) {
         static uint8_t data[6];
         int c = 0;int d = 0;
         c=(ss%10)+10;
         if(c>15){c=c-(ss%10);}
         Serial.println(c);
         
         d=(ss/10)+10;
         if(d>15){d=d-(ss/10);}
         Serial.println(d);
         
         data[0] = mm/10;   //
         data[1] = mm%10;   // display
         data[2] = ss/10;   //
         
         data[3] = ss%10;   //
         data[4] = c;   // LED
         data[5] = d;   //
         
         showDigits( data, colon );
   
     }

    void testDigitalWatch() {                       
         static boolean colon=0;
         static uint8_t hh=12, mm=0, ss=0;   // Start at 12:00:00(hours, minutes and seconds)
         if ( millis() - ts >= 500 ) {                // check every 500 msec
            showTime( hh, mm, ss, colon );
           k=k+1;
           
     if (k==8){k=0;}
            colon = !colon;                             
            if (colon) {                                 
                ss = (ss+1)%60;                     
                if (ss == 0) {
                    mm = (mm+1)%60;
                    if (mm == 0) {
                        hh = (hh+1)%24;
                     }
                }
             }
             ts += 500;
           }
     }


    void loop() {
//         testTimer();
         testDigitalWatch();
         

    
     
//       Serial.println(k);
       
      }
/////////////////////////////////////////////////////////////////////
