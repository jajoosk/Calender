//This program works only on TURBOCC++ IDE as union in getkey function is not available in other compilers
#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<conio.h>
int getkey()
{
	union REGS in,out;
	in.h.ah=0x8;
	int86(0x21,&in,&out);
	return out.h.al;
}

  char month[][10]={"january","february","march","april","may","june","july","august","september","october","november","december"};
  char days[][10]={"mon","tue","wed","thu","fri","sat","sun"};
  int noofdays[]={31,28,31,30,31,30,31,31,30,31,30,31};

//Gives the start of year
int day(int current_year)
{
    int d1,d2,d3, res=0;
    d1=((current_year-1)/4);
    d2=((current_year-1)/100);
    d3=((current_year-1)/400);
    res=(current_year + d1 - d2 + d3) %7;
    return (res);
}
//create the calender
void calendar(int year, int daycode,char currentmonth[10])
{
	int mo, day;
	for ( mo = 0; mo < 12; mo++ )
	{
	    if(strcmp(currentmonth,month[mo])==0)
	    {

		printf("\n        %d %s",year,currentmonth);


		printf("\n\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n" );

		// Correct the position for the first date
		for ( day = 1; day <= 1 + daycode * 5; day++ )
		{
			printf(" ");
		}

		// Print all the dates for one month
		for ( day = 1; day <= noofdays[mo]; day++ )
		{
			printf("%2d", day );

			// Is day before Sat? Else start next line Sun.
			if ( ( day + daycode ) % 7 > 0 )
				printf("   " );
			else
				printf("\n " );
		}
	    }
			// Set position for next month
	    else
		daycode = ( daycode + noofdays[mo] ) % 7;

	}

}
//check that it is leap year or not so that change the days of month of february.
void leapyear(int year)
{
    if(((year%4==0) && (year%100!=0)) || (year%400==0))
	noofdays[1]=29;
    else
	noofdays[1]=28;


}
 int main()
 {


    int i,start,key=0,currentyear=0;
    char in[12],currentmonth [20];
    clrscr();
    puts("Enter year 1990 onwards");
    scanf("%d",&currentyear);
    puts("Enter the month");
    scanf("%s",in);

    strcpy(currentmonth,in);

    start=day(currentyear);

    leapyear(currentyear);
    calendar(currentyear,start,currentmonth);
    printf("\n Up arrow-Next year,same month");
    printf("\n Down arrow-Previous year,same month");
    printf("\n Left arrow-Same year,previous month");
    printf("\n Right arrow-Same year,next month");
    while(key!=27)
    {
	key=getkey();
	clrscr();
	if(key==72)
	{
	    currentyear++;
	    start=day(currentyear);

	    leapyear(currentyear);
	    calendar(currentyear,start,currentmonth);


	}
	if(key==80)
	{
	    currentyear--;
            start=day(currentyear);

            leapyear(currentyear);
            calendar(currentyear,start,currentmonth);


        }
        if(key==75)
        {


            for(i=0;strcmp(currentmonth,month[i])!=0;i++);
            if(i==0)
            {
                i=11;
                currentyear--;
            }
            else
                i--;

           strcpy(currentmonth,month[i]);
           start=day(currentyear);

           leapyear(currentyear);
           calendar(currentyear,start,currentmonth);


        }

        if(key==77)
        {
            for(i=0;strcmp(currentmonth,month[i])!=0;i++);
            if(i==11)
            {
                i=0;
                currentyear++;
            }
            else
                i++;

           strcpy(currentmonth,month[i]);
           start=day(currentyear);

           leapyear(currentyear);
           calendar(currentyear,start,currentmonth);



	}


    }

    return 0;
}
