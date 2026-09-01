#define RED_LED (1<<17)
#define YELLOW_LED (1<<8)
#define GREEN_LED (1<<19)
#define sw1 ((IOPIN0>>14)&1)
#define sw2 ((IOPIN0>>15)&1)
#define buz (1<<21)

extern void wifi_connect(void);		  //p0.0->tx    //p0.1->rx
extern void esp_read(void);


 typedef unsigned int u32;
 typedef unsigned char u8;
 typedef signed char s8;
 typedef signed int s32; 

extern void delay_ms(unsigned int ms);
extern void delay_us(unsigned int us);
extern void lcd_data(unsigned char data);
extern void lcd_cmd(unsigned int cmd);
extern void lcd_integer(int num);
extern void lcd_float(float f);
extern void lcd_string(char *ptr);
void lcd_init(void);
extern void uart0_init(unsigned int baud);
extern void uart0_tx(unsigned char data);
extern unsigned char uart0_rx(void);
extern void uart0_tx_string(char *ptr);
extern void uart0_binary(int num);
extern void uart0_integer(int num);
extern void uart0_float(float f);
extern void adc_init(void);
extern unsigned int adc_read(unsigned char );

//ultrasonic
extern void ultrasonic_init(void);
extern u32 ultrasonic_read(void);

extern void relay_init(void);
extern void relay_on(void);

extern void relay_off(void);

extern void servo_init(void);
extern void servo_0deg(void);
extern void servo_90deg(void);
extern void servo_180deg(void);
extern void servo_off(void);


extern void wifi_connect(void);
extern void esp_read(void);

extern void i2c_init(void);
extern void i2c_write(u8 , u8 , u8 );
extern u8 i2c_read(u8 ,u8 );

extern void eeprom(u8 );

extern float water_level_sensor(void);
extern void rtc_display(void);
extern void eeprom(u8 );
extern u8 eeprom_read(u32);
extern void eeprom_write(u32 address,u8 data);

//CAN

typedef struct CAN_MSG{

u32 id;
u32 byteA;
u32 byteB;
u8 rtr;
u8 dlc;
u8 ff;
}CAN1;

extern void can1_init(void);
extern void can_init(void);
extern void can_rx(CAN1 *);
extern void can1_parameter(u8 t,u8 w,u8 d);	


 //delay
extern void delay_ms(unsigned int);

extern void rtc_date(void);

//interupts
extern void can1_parameter(u8 t,u8 w,u8 d);


extern void delay_sec(unsigned int);

//intrpt
extern void config_for_eint0(void);


