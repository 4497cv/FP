
#include <terminal.h>

void terminal_menu_start(void)
{
	/*VT100 command for clearing the screen*/
	UART_put_string(UART_0,"\033[2J");
	/** VT100 command for text in black and background in black*/
	UART_put_string(UART_0,"\033[0;30;40m");
	/*VT100 command for clearing the screen*/
	UART_put_string(UART_0,"\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_put_string(UART_0, "\033[0;47;40m");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_put_string(UART_0, "\033[12;34H");
	/** Set the text in a string*/
	UART_put_string(UART_0, "Welcome back\r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_put_string(UART_0, "\033[12;47H");
}

void terminal_menu_select(void)
{
	/*VT100 command for clearing the screen*/
	UART_put_string(UART_0,"\033[2J");
	/** VT100 command for text in black and background in black*/
	UART_put_string(UART_0,"\033[0;30;40m");
	/*VT100 command for clearing the screen*/
	UART_put_string(UART_0,"\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_put_string(UART_0, "\033[0;47;40m");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_put_string(UART_0, "\033[10;10H");
	/** Set the text in a string*/
	UART_put_string(UART_0, "1) Play classic mode\r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_put_string(UART_0, "\033[11;10H");
	/** Set the text in a string*/
	UART_put_string(UART_0, "2) Guitar tuner \r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_put_string(UART_0, "\033[14;10H");
}

void terminal_menu_op1(void)
{
	/*VT100 command for clearing the screen*/
	UART_put_string(UART_0,"\033[2J");
	/** VT100 command for text in black and background in black*/
	UART_put_string(UART_0,"\033[0;30;40m");
	/*VT100 command for clearing the screen*/
	UART_put_string(UART_0,"\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_put_string(UART_0, "\033[0;47;40m");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_put_string(UART_0, "\033[12;34H");
	/** Set the text in a string*/
	UART_put_string(UART_0, "Classic Mode\r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_put_string(UART_0, "\033[12;47H");
}

void terminal_menu_op2(void)
{
	/*VT100 command for clearing the screen*/
	UART_put_string(UART_0,"\033[2J");
	/** VT100 command for text in black and background in black*/
	UART_put_string(UART_0,"\033[0;30;40m");
	/*VT100 command for clearing the screen*/
	UART_put_string(UART_0,"\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_put_string(UART_0, "\033[0;47;40m");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_put_string(UART_0, "\033[12;34H");
	/** Set the text in a string*/
	UART_put_string(UART_0, "Guitar Tuner\r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_put_string(UART_0, "\033[12;47H");
}
