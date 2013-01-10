#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h>

int main()
{
	union 
	{
		short number;
		char c[sizeof(short)];
	}un;

	struct utsname uts;

	un.number = 0x0102;
	if(uname(&uts)<0)
	{
		printf("Could no get host information\n");
		return 1;
	}

	printf("%s:-%s:-%s:\n",uts.machine,uts.sysname,uts.release);

	if(sizeof(short) !=2)
	{
		printf("sizeof short = %d\n",sizeof(short));
	}

	if(un.c[0]==1 && un.c[1]==2)
	{
		printf("big_endian\n");
	}
	else if(un.c[0]== 2 && un.c[1] ==1)
	{
		printf("little_endia\n");
	}
	else
	{
		printf("unknow\n");
	}
}
