#include<stdio.h>
#include<windows.h>
#include<conio.h>
int checkLeapYear(int year);
void printDate(int mm, int yy);
void getDay(int date,int month,int year);
void gotoxy (int x, int y);
int getNumberOfDays(int mm,int yy);
int getDayNumber(int dd,int mm,int yy);
void printMonth(int mon,int year,int x,int y);
void increase(int *mm,  int *yy);
void decrease(int *mm,  int *yy);
void AddNote();
void showNote(int mmm);
void showHolidays(int ye);
COORD xy = {0, 0};
struct notes{
    int dd;
    int mm;
    char note[50];
};
struct notes n[50];
int i=0;
struct holidays{
    int d;
    int m;
    char h[50];
};
struct holidays hh[50];
int main()
{
    int ch;
    int d,m,y;
    char choice='1';
    hh[0].d=26;
   hh[0].m=1;
   strcpy(hh[0].h,"Republic Day");
   hh[1].d=15;
   hh[1].m=8;
     strcpy(hh[1].h,"Independence Day");
   hh[2].d=2;
   hh[2].m=10;
     strcpy(hh[2].h,"Gandhi Jayanti");
     hh[3].d=25;
   hh[3].m=12;
     strcpy(hh[3].h,"Christmas");
   while(1)
    {
        system("cls");
        printf("\t\t\t\t\t\tWHAT DO YOU WANT ME TO DO?\n\n\t\t\t\t\t\t\tPRESS\n\n\t\t\t\t1:TELL ME THE DAY\n\t\t\t\t2:PRINT ALL DAYS OF A MONTH\n\t\t\t\t3:ADD A NOTE\n\t\t\t\t4:SHOW ME THE HOLIDAYS OF A YEAR\n\t\t\t\t5:Exit\n\n");
        printf("\t\tENTER YOUR CHOICE : ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: system("cls");
                    printf("Enter the Date,Month and Year in DD MM YYYY format\n");
                    scanf("%d %d %d",&d,&m,&y);
                    getDay(d,m,y);
                    printf("\nPress any key to continue......");
                    getch();
                    break;
            case 2: system("cls");
                    printf("Enter month and year (MM YYYY) : ");
                    scanf("%d %d",&m,&y);
                    system("cls");
                    choice='a';
                    while(choice!='q')
                    {
                        system("cls");
                        printMonth(m,y,20,5);
                        choice = getch();
                        if(choice == 'n')
                        {
                            increase(&m,&y);
                            system("cls");
                            printMonth(m,y,20,5);
                        }
                        else if(choice == 'p')
                        {
                            decrease(&m,&y);
                            system("cls");
                            printMonth(m,y,20,5);
                        }
                        else if(choice == 's')
                        {
                            showNote(m);
                            system("cls");
                        }
                    }
                    break;
            case 3: system("cls");
                    AddNote();//AddNote();
                    break;
            case 4: system("cls");
                    printf("ENTER YEAR\n");
                    scanf("%d",&y);
                    showHolidays(y);//shows important holidays();
                    printf("\n\nPress any key to continue......");
                    getch();
                    break;
            case 5: exit(0);
            default : printf("INCORRECT CHOICE");
        }
    }
    return 0;
}
void gotoxy (int x, int y)
{
        xy.X = x; xy.Y = y; // X and Y coordinates
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}
int checkLeapYear(int year)//to check if a year is leap year
{
    if(year % 400 == 0 || (year % 100!=0 && year % 4 ==0))
        return 1;
    return 0;
}
//to get the day name **pointer in front of getday
void getDay(int date,int month,int year)
{
    char getName[7][10]={"sunday","monday","tuesday","wednesday","thursday","friday","saturday"};
    int day;
    if((month<1)||(month>12) )
        printf("Invalid month value");
   else if(date<1 || date>getNumberOfDays(month,year))
        printf("Invalid date");
    else if(year>=1700 && year<2400)
    {
        day = getDayNumber(date,month,year);
        printf("%s",getName[day]);
    }
    else
        printf("Please give year more than 1600");

}
int getNumberOfDays(int mm,int yy)
{
      switch(mm)
      {                          //returns no.of days in a given month
        case 1 : return(31);
        case 2 : if(checkLeapYear(yy))
                    return(29);
                 else
                    return(28);
        case 3 : return(31);
        case 4 : return(30);
        case 5 : return(31);
        case 6 : return(30);
        case 7 : return(31);
        case 8 : return(31);
        case 9 : return(30);
        case 10: return(31);
        case 11: return(30);
        case 12: return(31);
        default: return(-1);
   }
}
int getDayNumber(int dd,int mm,int yy)//returns day number
{
    int monthno[12]={0,3,3,6,1,4,6,2,5,0,3,5};
    int cent[7]={4,2,0,6,4,2,0};
    int yyy=yy%100;
    int k=((yyy+(yyy/4))%7)+monthno[mm-1]+cent[yy/100 -17]+dd;
    if((checkLeapYear(yy))&&((mm==1)||(mm==2)))
        k-=1;
    k=k%7;
    return k;
}



void printMonth(int mon,int year,int x,int y)//prints the month with all days
{
    int nod, day, cnt, d = 1, x1 = x, y1 = y, isNote = 0;
    if(mon<1 || mon>12){
        printf("INVALID MONTH\n");
        printf("Press 'q' to go back\n");
        return;
    }
    if(year<1700 || year>2400){
        printf("INVALID YEAR\n");
        printf("Press 'q' to go back\n");
        return;
    }
    gotoxy(20,y);
    printDate(mon,year);
    y += 3;
    gotoxy(x,y);
    printf("S   M   T   W   T   F   S   ");
    y++;
    nod = getNumberOfDays(mon,year);
    day = getDayNumber(d,mon,year);
    cnt=day+1;
    switch(day){ //locates the starting day in calender
        case 0 :x=x;break;
        case 1 :x=x+4;break;
        case 2 :x=x+8;break;
        case 3 :x=x+12;break;
        case 4 :x=x+16;break;
        case 5 :x=x+20;break;
        case 6 :x=x+24;break;
        return;
    }
    gotoxy(x,y);
    printf("%02d",d);
    for(d=2;d<=nod;d++){
        if(cnt%7==0)
            {
                y++;
                cnt=0;
                x=x1-4;
            }
        x = x+4;
        cnt++;
        gotoxy(x,y);
        printf("%02d",d);
    }
    printf("\n\tPress 'n' for Next month\n\tPress 'p' for Previous month \n\tPress 'q' to Quit\n");
    printf("\tPress 's' to see note: \n");

}
void printDate(int mm, int yy){ //prints the name of month and year
    printf("---------------------------\n");
    gotoxy(25,6);
    switch(mm){
        case 1: printf("January"); break;
        case 2: printf("February"); break;
        case 3: printf("March"); break;
        case 4: printf("April"); break;
        case 5: printf("May"); break;
        case 6: printf("June"); break;
        case 7: printf("July"); break;
        case 8: printf("August"); break;
        case 9: printf("September"); break;
        case 10: printf("October"); break;
        case 11: printf("November"); break;
        case 12: printf("December"); break;
    }
    printf(" , %d", yy);
    gotoxy(20,7);
    printf("---------------------------");
}
void increase(int *mm,  int *yy)//increase the month by one
{
    ++*mm;
    if(*mm > 12)
    {
        ++*yy;
        *mm = *mm - 12;
    }
}

void decrease(int *mm,  int *yy)//decrease the month by one
{
        --*mm;
        if(*mm < 1)
        {
            --*yy;
            if(*yy<1700 && *yy>2400)
            {
                printf("No record available");
                return;
            }
            *mm = *mm + 12;
        }
}
void AddNote(){
    int dd,mm;
    char note[50];
    printf("Enter the date(DD/MM): ");
    scanf("%d%d",&n[i].dd, &n[i].mm);
    printf("Enter the Note(50 character max): \n");
    fflush(stdin);
    scanf("%[^\n]",n[i].note);
    i++;
      printf("Press any key............Note is saved successfully");
    getch();
    }

void showNote(int mmm){
    int j,c=0, isFound = 0,l=0;
    system("cls");
     for(j=0;j<=i;j++){
        if(n[j].mm==mmm){
                 gotoxy(10,5+l);
              printf("Note on %d.%d is = %s", n[j].dd,n[j].mm,n[j].note);
           isFound = 1;
        l++;
           }
        }
    if(isFound == 0){
        gotoxy(10,5);
        printf("This Month contains no note");
    }
    gotoxy(10,7+l);
    printf("Press any key to back.......");
    getch();

}

void showHolidays(int ye){
    int k;
    printf("THE GAZETTED HOLIDAYS ARE\n");
for( k=0;k<4;k++)
    printf("%d.%d.%d is %s\n",hh[k].d,hh[k].m,ye,hh[k].h);
}

