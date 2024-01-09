/*
 * Calculator.c
 *
 * Created: 12/13/2022 11:26:38 AM
 * Author : M.Sayed
 */ 
#include "DIO_Interface.h"
#include "LCD.h"
#include "KeyPad.h"

int main(void)
{
	DIO_init();
	LCD_init();
	
	LCD_WriteString("Welcome To My Calculator ");
	_delay_ms(1000);
	
	LCD_Clear();
	
	u8 k,process,flag=0,mins=0,again=0,count=0;
    s32 num,result,a,b;
	
    while (1) 
    {
		k=KEYPAD_GetKey();
		
		if (k!=NO_KEY)
		{
			if (count==1)
			{
				LCD_Clear();
				LCD_GoTo(0,0);
				LCD_WriteNumber(result);
				u32 s= result;
				u8 c=0;
				while (s!=0)
				{
					s=s/10;
					c++;
				}
				
				LCD_GoTo(0,c);
				LCD_WriteChar(k);
				again=1;
				count=0;
				c=0;
				s=0;
			}
			else
			{
				LCD_WriteChar(k);
			}
			if (k>='0'&& k<='9')
			{
				num=num*10+(k-'0');
				if (mins==1)
				{
					num=(-1)*num;
					mins=0;
				}
				
				flag=1;
			}
			else if (k=='-'&&flag==0) 
			{
				mins=1;
			}
			else if ((k=='+'||k=='-'||k=='/'||k=='*'))
			{
					process=k;
					flag=0;
					if (again==1)
					{
						a=result;
						again=0;
					}
					else 
					{
						a=num;
						num=0;
					}	
			}
			
			else if (k=='=')
			{
				b=num;
				num=0;
				flag=1;
				switch(process)
				{
					case '+':
					result=a+b;
					LCD_GoTo(1,0);
				    LCD_WriteNumber(result);
					break;
					case '-':
					result=a-b;
					LCD_GoTo(1,0);
					LCD_WriteNumber(result);
					break;
					case '/':
					if (b!=0)
					{
					result=a/b;
					u32 result2;
					result2=(a*10)/b;
					LCD_GoTo(1,0);
					LCD_WriteNumber(result2/10);
					LCD_WriteChar('.');
					LCD_WriteNumber(result2%10);
					}
					else 
					{
						LCD_Clear();
						LCD_GoTo(0,10);
						LCD_WriteString("ERROR");
						_delay_ms(1000);
						k='c';
					}
					break;
					case '*':
					result=a*b;
					LCD_GoTo(1,0);
					LCD_WriteNumber(result);
					break;
				}
				a=0;
				b=0;
				count=1;
			}
			
			if (k=='c')
			{
				LCD_Clear();
				num=0;
				a=0;
				b=0;
				flag=0;
				again=0;
				count=0;
			}
			
		}
    }
}

