#include<reg51.h>

sbit C1=P1^0;
sbit C2=P1^1;
sbit C3=P1^2;
sbit C4=P1^3;
sbit R1=P2^0;
sbit R2=P2^1;
sbit R3=P2^2;
sbit R4=P2^3;
sbit busy_flag=P3^7;
sbit rs=P0^0;
sbit rw=P0^1;
sbit en=P0^2;
unsigned char flag;
unsigned char key;
unsigned char count[10]={0};
unsigned char cursor_position=0x80;

unsigned char columnfinder_1();
unsigned char columnfinder_2();
unsigned char columnfinder_3();
unsigned char columnfinder_4();
unsigned char one_sec_timer();
void cmdwrt(unsigned char cmd);
void display(unsigned char counter,unsigned char digit);
void datawrt(unsigned char lcd_data);
void ready();

void intro()
{
	unsigned char a[]={0x38,0x0E,0x01,0x80};
	unsigned char i;
	for(i=0;i<4;i++)
	{
		cmdwrt(a[i]);
	}
}

void main()
{
	P0=0x00;
	P1=0xFF;
	P3=0x00;
	TMOD=0x01;
	intro();
	P1= P1 & 0x0F;
	while (1)
	{
		P2=0x00;
		flag=0;		
		while(P1==0x0F);
		TH0=0xDB;
		TL0=0xFF;
		TR0=1;
		while(TF0==0);
		TR0=0;
		TF0=0;
		while (P1!=0x0F)
		{
			if (columnfinder_1());
			else if (columnfinder_2());
			else if (columnfinder_3());
			else
				columnfinder_4();
		}
	}
}

unsigned char columnfinder_1()
{
label_1:R1=0,R2=R3=R4=1;
	if (C1==0)
	{
		datawrt('1');
		while(C1==0);
		cmdwrt(++cursor_position);
		return 1;
	}
	else if (C2==0)
	{
		key=2;
		count[key]++;
		display(count[key],key);
		while(C2==0);
	}
	else if (C3==0)
	{
		key=3;
		count[key]++;
		display(count[key],key);
		while(C3==0);
	}
	else if (C4==0)
	{
		cmdwrt(++cursor_position);
		while(C4==0);
		return 1;
	}
	else
		return 0;
	if (one_sec_timer()==0)
		goto label_1;
	return 1;
}
unsigned char columnfinder_2()
{
label_2:R2=0,R1=R3=R4=1;
	if (C1==0)
	{
		key=4;
		count[key]++;
		display(count[key],key);
		while(C1==0);
	}
	else if (C2==0)
	{
		key=5;
		count[key]++;
		display(count[key],key);
		while(C2==0);
	}
	else if (C3==0)
	{
		key=6;
		count[key]++;
		display(count[key],key);
		while(C3==0);
	}
	else if (C4==0)
	{
		cmdwrt(++cursor_position);
		while(C4==0);
		return 1;
	}
	else
		return 0;
	if (one_sec_timer()==0)
		goto label_2;
	return 1;
}
unsigned char columnfinder_3()
{
label_3:R3=0,R1=R2=R4=1;
	if (C1==0)
	{
		key=7;
		count[key]++;
		display(count[key],key);
		while(C1==0);
	}
	else if (C2==0)
	{
		key=8;
		count[key]++;
		display(count[key],key);
		while(C2==0);
	}
	else if (C3==0)
	{
		key=9;
		count[key]++;
		display(count[key],key);
		while(C3==0);
	}
	else if (C4==0)
	{
		cmdwrt(--cursor_position);
		while(C4==0);
		return 1;
	}
	else
		return 0;
	if (one_sec_timer()==0)
		goto label_3;
	return 1;
}
unsigned char columnfinder_4()
{
	R4=0,R1=R2=R3=1;
	if (C1==0)
	{
		datawrt('*');
		while(C1==0);
	}
	else if (C2==0)
	{
		datawrt('0');
		while(C2==0);
	}
	else if (C3==0)
	{
		datawrt('#');
		while(C3==0);
	}
	else if (C4==0)
	{
		cmdwrt(0x01);
		cursor_position=0x80;
		cmdwrt(cursor_position);
		while(C4==0);
		return 1;
	}
	else
		return 0;
	cmdwrt(++cursor_position);
	return 1;
}

void cmdwrt(unsigned char cmd)
{
	ready();
	P3=cmd;
	rs=0;
	rw=0;
	en=1;
	TH0=0xF8;
	TL0=0xCD;
	TR0=1;
	while(TF0==0);
	TR0=0;
	TF0=0;
	en=0;
}
void datawrt(unsigned char lcd_data)
{
	ready();
	P3=lcd_data;
	rs=1;
	rw=0;
	en=1;
	TH0=0xFC;
	TL0=0x66;
	TR0=1;
	while(TF0==0);
	TR0=0;
	TF0=0;
	en=0;
	cmdwrt(cursor_position);
}
void ready()
{
	busy_flag=1;
	rs=0;
	rw=1;
	do {
		en=0;
		TH0=0xFC;
		TL0=0x66;
		TR0=1;
		while(TF0==0);
		TR0=0;
		TF0=0;
		en=1;
	}while(busy_flag==1);	
}

unsigned char one_sec_timer()
{
	unsigned char i;
	for(i=0;i<15;i++)
	{
		TH0=0x4B;
		TL0=0xFD;
		TR0=1;
		while(TF0==0);
		TR0=0;
		TF0=0;
		if ( C1==0 || C2==0 || C3==0 || C4==0 )
		{
			flag=1;
			return 0;
		}
	}
	cursor_position++;
	cmdwrt(cursor_position);
	return 1;
}

void display(unsigned char counter,unsigned char digit)
{
	unsigned char i;
	if(counter>5)
		counter=count[key]=1;
  if (counter==1)
	{
		if (flag==1)
		{
			cursor_position++;
			cmdwrt(cursor_position);
		}
		for(i=2;i<10;i++)
		{
			if (i != key)
				count[i]=0;
		}
back:switch(digit)
		{
			case 2:
				datawrt('A');
				break;
			case 3:
				datawrt('D');
				break;
			case 4:
				datawrt('G');
				break;
			case 5:
				datawrt('J');
				break;
			case 6:
				datawrt('M');
				break;
			case 7:
				datawrt('P');
				break;
			case 8:
				datawrt('T');
				break;
			case 9:
				datawrt('W');
				break;
		}
	}
	else if (counter==2)	
	{
		switch(digit)
		{
			case 2:
				datawrt('B');
				break;
			case 3:
				datawrt('E');
				break;
			case 4:
				datawrt('H');
				break;
			case 5:
				datawrt('K');
				break;
			case 6:
				datawrt('N');
				break;
			case 7:
				datawrt('Q');
				break;
			case 8:
				datawrt('U');
				break;
			case 9:
				datawrt('X');
				break;
		}
	}
	else if(counter==3)
	{
		switch(digit)
		{
			case 2:
				datawrt('C');
				break;
			case 3:
				datawrt('F');
				break;
			case 4:
				datawrt('I');
				break;
			case 5:
				datawrt('L');
				break;
			case 6:
				datawrt('O');
				break;
			case 7:
				datawrt('R');
				break;
			case 8:
				datawrt('V');
				break;
			case 9:
				datawrt('Y');
				break;
		}
	}
	else if(counter==4)
	{
		switch(digit)
		{
			case 2:
				datawrt('2');
				break;
			case 3:
				datawrt('3');
				break;
			case 4:
				datawrt('4');
				break;
			case 5:
				datawrt('5');
				break;
			case 6:
				datawrt('6');
				break;
			case 7:
				datawrt('S');
				break;
			case 8:
				datawrt('8');
				break;
			case 9:
				datawrt('Z');
				break;
		}
	}
	else
	{
		switch(digit)
		{
			case 7:
				datawrt('7');
				break;
			case 9:
				datawrt('9');
				break;
			default:
				counter=count[key]=1;
				goto back;
		}
	}
}