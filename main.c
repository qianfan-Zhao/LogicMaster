#include <stdio.h>
#include <stdlib.h>
#include <platform.h>

char buf[256];

int main(void)
{
	for(;;)
	{
		__io_puts("$ ");
		__io_puts(__io_gets(buf,256));
		__io_putchar('\n');
	}
}


