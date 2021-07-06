
//Stop Watch Without Button Control

#define F_CPU 12000000ul
#include <avr/io.h>
#include <util/delay.h>

#define SSDPORT PORTD
#define SLPORT PORTC
#define SL1 PC1
#define SL2 PC2
#define SL3 PC3
#define SL4 PC4

//Function Declaration (with 4 arguments but no return type)
void display(unsigned int d1,unsigned int d2,unsigned int d3,unsigned int d4);

//Array holding patterns 0	  1		2	3	4	  5		6	7	8	 9	
unsigned int digit[10]={0XFC,0X60,0XDA,0XF2,0X66,0XB6,0XBE,0XE0,0XFE,0XF6};

unsigned int data1,data2,data3,data4;	//4 global variables to hold data 
	
int main(void)
{
	DDRD=0XFF;			//Define PORTD as output
	DDRC=0b0011110;		//Define PC1, PC2, PC3, PC4 as Output
	
    while (1) 
    {
			display(data1,data2,data3,data4); //Function to display data on SSD
			
			data4++;		//increment data4
			if (data4>9)	
			{
				data4=0;	//if data4=10, reset data4 to 0
				data3++;	//increment data3
				
				if (data3>9)
				{
					data3=0;	//if data3=10, reset data3 to 0
					data2++;	//increment data2
				
					if (data2>9)
					{
						data2=0;	//if data2=10, reset data2 to 0
						data1++;	//increment data1
						
						if (data1>9)	//if data1=10
						{
							data1=data2=data3=data4=0;	//reset all to 0
						}
					}
				}
			}
	}
}

//display Function definition 

void display(unsigned int d1,unsigned int d2,unsigned int d3,unsigned int d4)
{
	unsigned int i=0;	//local variable for looping
	
	for(i=0;i<250;i++)  //one loop takes 4ms | to get 1000ms delay, run loop 250 times
	{
		SLPORT=1<<SL2|1<<SL3|1<<SL4;	//SSD1 active	
		SSDPORT=digit[d1];				//Data transmitted to SSD1
		_delay_ms(1);

		SLPORT=1<<SL1|1<<SL3|1<<SL4;	//SSD2 active
		SSDPORT=digit[d2];				//Data transmitted to SSD2
		_delay_ms(1);

		SLPORT=1<<SL1|1<<SL2|1<<SL4;	//SSD3 active
		SSDPORT=digit[d3];				//Data transmitted to SSD3
		_delay_ms(1);

		SLPORT=1<<SL1|1<<SL2|1<<SL3;	//SSD4 active	
		SSDPORT=digit[d4];				//Data transmitted to SSD4
		_delay_ms(1);
	}
}








/*


 //With Button Control (Start,Pause,Reset via button)
 
#define F_CPU 12000000ul
#include <avr/io.h>
#include <util/delay.h>

#define SSDPORT PORTD
#define SLPORT PORTC
#define SL1 PC1
#define SL2 PC2
#define SL3 PC3
#define SL4 PC4

//Function Declaration
void display(unsigned int d1,unsigned int d2,unsigned int d3,unsigned int d4);

//Array holding patterns 0	  1		2	3	4	  5		6	7	8	 9		-
unsigned int digit[11]={0XFC,0X60,0XDA,0XF2,0X66,0XB6,0XBE,0XE0,0XFE,0XF6,0X02};

unsigned int data1,data2,data3,data4;	//global variables to hold data 
	
int main(void)
{

	unsigned int button_status=0;	//local variable holding button status	
	unsigned int press_count=0;		//local variable holding button press count

	DDRD=0XFF;			//Define PORTD as output
	DDRC=0b0011110;		//Define PB1, PB2, PB3, PB4 as Output 

    while (1) 
    {
		//Routine To Check Button Status 
		button_status= PINB & 0X01; //Store status of button connected at PB0
		 
		if (button_status==0x01)	//If button is pressed
		{
			_delay_ms(200);			//debounce time
			press_count++;			//increment press count
			
			if (press_count==3)		//if press count==3
			{
				press_count=0;		//press count=0
			}
		}
		
		
		//Routine To Do Task According To Button Pressed
			
		if (press_count==0)		//If press count ==0, Reset Counter
			{
			data1=data2=data3=data4=10;			//10th element of array holds - pattern			
			display(data1,data2,data3,data4);	//Function to display data on SSD
			}
		

		else if (press_count==1)	//If press count ==1, Start Counter
			{
				data4++;		//increment data4
				if (data4>9)	
				{
					data4=0;	//if data4=10, reset data4 to 0
					data3++;	//increment data3
				
					if (data3>9) 
					{
						data3=0;	//if data3=10, reset data3 to 0
						data2++;	//increment data2
						
						if (data2>9)
						{
							data2=0;	//if data2=10, reset data2 to 0
							data1++;	//increment data1
						
							if (data1>9)	//if data1=10, reset data1 to 0
							{
								data1=data2=data3=data4=0;	//Reset all to 0
							}
						}
					}
				}
				display(data1,data2,data3,data4);
			}
			
		 else if (press_count==2)	//if press count ==2, pause stopwatch
		{
			display(data1,data2,data3,data4);
		}
	
	}
}


void display(unsigned int d1,unsigned int d2,unsigned int d3,unsigned int d4)
{
	unsigned int i=0;	//local variable for looping
	
	for(i=0;i<250;i++)  //one loop takes 4ms | to get 1000ms delay, run loop 250 times
	{
		SLPORT=1<<SL2|1<<SL3|1<<SL4;	//SSD1 active
		SSDPORT=digit[d1];				//Data transmitted to SSD1
		_delay_ms(1);

		SLPORT=1<<SL1|1<<SL3|1<<SL4;	//SSD2 active
		SSDPORT=digit[d2];				//Data transmitted to SSD2
		_delay_ms(1);

		SLPORT=1<<SL1|1<<SL2|1<<SL4;	//SSD3 active
		SSDPORT=digit[d3];				//Data transmitted to SSD3
		_delay_ms(1);

		SLPORT=1<<SL1|1<<SL2|1<<SL3;	//SSD4 active
		SSDPORT=digit[d4];				//Data transmitted to SSD4
		_delay_ms(1);
	}
}











*/





















/*
//With External Interrupt

#define F_CPU 1000000ul
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define SSDPORT PORTB
#define SLPORT PORTC
#define SL1 PC1
#define SL2 PC2
#define SL3 PC3
#define SL4 PC4

//Function Declaration
void display(unsigned int d1,unsigned int d2,unsigned int d3,unsigned int d4);

//Function To Initialize External Interrupt
void init_ext_interrupt();

//Array holding patterns 0	  1		2	3	4	  5		6	7	8	 9		-
unsigned int digit[11]={0XFC,0X60,0XDA,0XF2,0X66,0XB6,0XBE,0XE0,0XFE,0XF6,0X02};

unsigned int data1,data2,data3,data4;	//global variables to hold data

unsigned int press_count=0;		//global variable holding button press count

int main(void)
{

	//unsigned int button_status=0;	//local variable holding button status
	DDRB=0XFF;			//Define PORTD as output
	DDRC=0b0011110;		//Define PB1, PB2, PB3, PB4 as Output
	init_ext_interrupt();
	while (1)
	{
		//Routine To Do Task According To Button Pressed
		
		if (press_count==0)		//If press count ==0, Reset Counter
		{
			data1=data2=data3=data4=0;			//10th element of array holds - pattern
			display(data1,data2,data3,data4);	//Function to display data on SSD
		}
		
		else if (press_count==1)	//If press count ==1, Start Counter
		{
			data4++;		//increment data4
			if (data4>9)
			{
				data4=0;	//if data4=10, reset data4 to 0
				data3++;	//increment data3
				
				if (data3>9)
				{
					data3=0;	//if data3=10, reset data3 to 0
					data2++;	//increment data2
					
					if (data2>9)
					{
						data2=0;	//if data2=10, reset data2 to 0
						data1++;	//increment data1
						
						if (data1>9)	//if data1=10, reset data1 to 0
						{
							data1=data2=data3=data4=0;	//Reset all to 0
						}
					}
				}
			}
			display(data1,data2,data3,data4);
		}
		
		else// if (press_count==2)	//if press count ==2, pause stopwatch
		{
			display(data1,data2,data3,data4);
		}
		
	}
}


void display(unsigned int d1,unsigned int d2,unsigned int d3,unsigned int d4)
{
	unsigned int i=0;	//local variable for looping
	
	for(i=0;i<250;i++)  //one loop takes 4ms | to get 1000ms delay, run loop 250 times
	{
		SLPORT=1<<SL2|1<<SL3|1<<SL4;	//SSD1 active
		SSDPORT=digit[d1];				//Data transmitted to SSD1
		_delay_ms(1);

		SLPORT=1<<SL1|1<<SL3|1<<SL4;	//SSD2 active
		SSDPORT=digit[d2];				//Data transmitted to SSD2
		_delay_ms(1);

		SLPORT=1<<SL1|1<<SL2|1<<SL4;	//SSD3 active
		SSDPORT=digit[d3];				//Data transmitted to SSD3
		_delay_ms(1);

		SLPORT=1<<SL1|1<<SL2|1<<SL3;	//SSD4 active
		SSDPORT=digit[d4];				//Data transmitted to SSD4
		_delay_ms(1);
	}
}

void init_ext_interrupt()
{
	MCUCR=(1<<ISC11)|(1<<ISC10); //Interrupt On Rising Edge 
	sei();
	GICR=(1<<INT1); //External Interrupt Enable
}

ISR(INT1_vect)
{
	press_count++;
	if(press_count==3)
	{
		press_count=0;
	}
}

*/