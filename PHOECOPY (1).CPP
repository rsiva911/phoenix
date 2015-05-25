#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<graphics.h>
#include<stdlib.h>
#include<dos.h>
#include<time.h>
class detail{char emailid[20],movienm[30],location[30],shtime[6];             //for func book
	      int crdno,cost,price;
	      char address[50],phno[15],shdate[11];
	      int n, r[48],seats[6];

	      public:
	      detail() {strcpy(location,"Phoenix Cinemas, Chennai");}
	      void home();
	      void first();
	      void list();
	      void timing();
	      void box();
	      void details();
	      void numbers();
	      int check();
	      void book();
	      void screen();
	      void shdetail();
	      void last();
	      }d;

struct showtime{char mov[30], time[10][6];
	       }t[12];
struct setb{char mov[30], ran[48];
	   }s[12];

int numofr=0;

fstream f("details.dat",ios::in|ios::out|ios::binary);

char movies[][30]={"1. SKYFALL","2. UP","3. BARFI!","4. LIFE OF PI","5. MAID IN MANHATTAN","6. AUGUST RUSH","7. 27 DRESSES","8. NEW YEAR'S EVE","9. MR. AND MRS. SMITH","10. SALT","11. JERRY MCGUIRE","12. THE VISITOR"};

void detail::screen()
{for(int x=0,y=0;x<=640;x+=10)
 {line(x,y,x,y+30);
  line(x,y+30,x+5,y+35);
  line(x+5,y+35,x+10,y+30);
 }
 for(x=5,y=35;x<35;x+=10)
  line(x,y,x,y+445);
 for(x=615,y=35;x<640;x+=10)
  line(x,y,x,y+445);
}

void detail::first()
{setcolor(9);
for(int x=0,y=0;x<=640;x+=10)
  {line(x,y,x,y+30);
   line(x,y+30,x+5,y+35);
   line(x+5,y+35,x+10,y+30);
  }
for(x=5,y=35;x<45;x+=10)
 line(x,y,x,y+445);
for(x=605,y=35;x<640;x+=10)
 line(x,y,x,y+445);

x=305;int x1=315;
for(;x1<640;x-=10,x1+=10)
  {line(x,0,x,480);
   line(x1,0,x1,480);
  }
 delay(1000);
 for(x=305,x1=315;x1<640;x-=10,x1+=10)
  {setfillstyle(1,0);
   bar(x,35,x,480);
   bar(x1,35,x1,480);
   delay(75);
   if(x<=55)
    {setcolor(9);
     line(x,y,x,y+445);
     line(x1,y,x1,y+445);
    }
   if(x<=100)
    {settextstyle(4,HORIZ_DIR,5);
     setcolor(12);
     line(120,174,500,174);
     line(130,164,490,164);
     outtextxy(100,175,"PHOENIX CINEMAS");
     line(120,230,500,230);
     line(130,240,490,240);
    }
  }
 delay(3500);
}

void detail::list()
{cleardevice();
 cout<<"\n\n";

 int x,y;
 setcolor(12);
 setbkcolor(0);
 screen();
 settextstyle(7,HORIZ_DIR,3);
 outtextxy(80,50,"LIST OF MOVIES");
 settextstyle(7,HORIZ_DIR,2);
 x=100;
 for(int i=0;i<12;i++)
  {outtextxy(60,x,movies[i]);
   x+=30;
  }
 int ch,flag=1;
 settextstyle(7,HORIZ_DIR,1);
 setfillstyle(11,12);
 bar(340,120,585,240);
 setcolor(15);
 outtextxy(350,130,"ENTER THE CODE");
 outtextxy(350,160,"OF THE MOVIE");
 outtextxy(350,190,"TO BOOK THE TICKETS!");
 setcolor(15);
 while(flag==1)
  {rectangle(340,260,585,290);
   gotoxy(45,18);
   cin>>ch;
   if(ch>=1 && ch<=12)
    {flag=0;
     for(int i=1;i<=12;i++)
     if(i==ch)
      {strcpy(movienm,movies[i-1]);
       movienm[strlen(movienm)]='\0';
      }
     timing();
    }
   else
    {outtextxy(340,290,"Enter valid code number!");
     delay(1000);
     setfillstyle(1,0);
     bar(340,260,600,400);
    }
  }
 getch();
}

void assigntime()
{randomize();
 for(int k=0;k<12;k++)
  for(int i=0;i<10;i++)
   {for(int j=0;j<5;j++)
     {if(j==0)
       t[k].time[i][j]=random(2)+48;
      else
       if(j==1)
	{if(t[k].time[i][j-1]=='2')
	  t[k].time[i][j]=random(4)+48;
	 else
	  t[k].time[i][j]=random(10)+48;
	}
       else
	if(j==2)
	 t[k].time[i][j]=':';
	else
	 if(j==3)
	  t[k].time[i][j]=random(6)+48;
	 else
	  t[k].time[i][j]=random(10)+48;
    t[k].time[i][5]='\0';}
    strcpy(t[k].mov,movies[k]);
    t[k].mov[strlen(t[k].mov)]='\0';
   }
ofstream f;
f.open("times.dat",ios::binary|ios::out);
 for(k=0;k<12;k++)
   f.write((char*)&t[k],(sizeof(t[k])));
f.close();
getch();
}

void detail::timing()
{showtime t1;
 cleardevice();
 setcolor(12);
 screen();
 settextstyle(6,HORIZ_DIR,1);

 char l[2];
 int y=140,i;
 for(i=1;i<=10;i++,y+=25)
  {itoa(i,l,10);
   outtextxy(75,y,l); outtextxy(98,y,".");
  }

 ifstream F;
 F.open("times.dat",ios::binary|ios::in);
 int k=0,j=140,sh;
 while(k<12)
  {F.read((char*)&t1,sizeof(t1));
   k++;
   if(strcmp(t1.mov,movienm)==0)
    {outtextxy(60,100,"TIMINGS FOR: ");
     outtextxy(175,100,t1.mov);
     for(i=0;i<10;i++,j+=25)
       outtextxy(110,j,t1.time[i]);
     break;
    }
  }
 F.close();
 do
  {settextstyle(6,HORIZ_DIR,1);
   setcolor(12);
   outtextxy(300,200,"Enter code of the desired show time:");
   rectangle(300,230,475,260);
   gotoxy(45,16);
   cin>>sh;
   if(sh<1 || sh>10)
    {outtextxy(300,290,"Enter valid code!");
     delay(2000);
     setfillstyle(1,0);
     bar(300,230,500,290);
    }
   else
    for(k=1;k<11;k++)
   if(sh==k)
    {strcpy(shtime,t1.time[k-1]);
     shtime[strlen(shtime)]='\0';
    }
  }while(sh<1 || sh>10);

 y=300;
 for(i=1;i<=3;i++,y+=25)
  {itoa(i,l,10);
   outtextxy(310,y,l);
   outtextxy(325,y,".");
  }
 char tim[3][26];
 time_t t;
 t = time(NULL);
 y=300;
 for(i=1;i<=3;i++,y+=25)
  {strcpy(tim[i],ctime(&t));
   tim[i][10]='\0';
   outtextxy(338,y,tim[i]);
   t += 24L*60L*60L;
  }
 do
  {outtextxy(300,265,"Enter code of desrired date:");
   gotoxy(66,18);
   cin>>sh;
   if(sh>=1 && sh<=3)
    {strcpy(shdate,tim[sh]);
     shdate[strlen(shdate)]='\0';
    }
   if(sh>3 || sh<1)
    {setfillstyle(1,0);
     bar(300,265,550,295);
     outtextxy(300,265,"Enter valid code!");
     delay(2000);
     bar(300,265,550,295);
    }
  }while(sh<1 || sh>3);
 box();
 getch();

}

void setbox()
{randomize();
 int rm,i,k;
 for(k=0;k<12;k++)
  {for(i=0;i<48;i++)
   {rm=random(50);
    if(rm%2==0)
     s[k].ran[i]=2;
    else s[k].ran[i]=4;
   }
   strcpy(s[k].mov,movies[k]);
   s[k].mov[strlen(s[k].mov)]='\0';
  }
}

void detail::box()
{cleardevice();
 setcolor(12);
 int x,y;
 setbkcolor(0);
 setfillstyle(10,12);
 screen();
 settextstyle(4,HORIZ_DIR,4);
 outtextxy(150,50,"PHOENIX CINEMAS");
 settextstyle(6,HORIZ_DIR,1);
 outtextxy(40,100,"Seats available for ");
 outtextxy(200,100,movienm);
 for(int i=0;i<12;i++)
  if(strcmp(s[i].mov,movienm)==0)
   {for(int j=0;j<48;j++)
     r[j]=s[i].ran[j];
     break;
   }
 char l[3];
 setcolor(12);
 for(y=150;y<=450;y+=50)
  line(40,y,440,y);
 for(x=40;x<=440;x+=50)
  line(x,150,x,450);
 y=150;
 int o=1;
 settextstyle(4,HORIZ_DIR,2);
 for(int j=1;j<=6;j++,y+=50)
  {x=65;
   for(int k=1;k<=8;k++,x+=50)
    {setcolor(r[o-1]);
     itoa(o,l,10);
     o++;
     outtextxy(x,y,l);
    }
  }
 setcolor(4);
 fillellipse(457,140,3,3);
 setcolor(2);
 fillellipse(457,160,3,3);
 setcolor(12);
 settextstyle(6,HORIZ_DIR,1);
 outtextxy(465,125,"Booked seat.");
 outtextxy(465,145,"Unbooked seat.");
 setcolor(12);
 rectangle(456,207,605,426);
 settextstyle(3,HORIZ_DIR,1);
 int flag=1;
 while(flag==1)
  {setfillstyle(1,0);
   bar(461,216,603,235);
   delay(2000);
   gotoxy(74,15);
   outtextxy(461,216,"No.of tickets: ");
   cin>>n;
   if(n>0 && n<7)
    flag=0;
   else
    {outtextxy(461,380,"Only 6 tickets");
     outtextxy(461,395,"allowed!");
     delay(2000);
     setfillstyle(1,0);
     bar(461,380,603,425);
     flag=1;
    }
  }
 while(flag==0)
  {outtextxy(461,240,"Enter seats");
   outtextxy(461,255,"to be booked:");
   gotoxy(59,19);
   i=0;	 //
   while(i<n)
     {cin>>seats[i];
      i++;
     }
   if(check()==-1)
     {outtextxy(461,310,"Specified seats");
      outtextxy(461,325,"have been");
      outtextxy(461,340,"booked!");
      delay(2000);
      setfillstyle(1,0);
      bar(461,239,603,425);  flag=0;}
   else
     if(check()==3)
       {outtextxy(461,310,"Only 6 tickets");
	outtextxy(461,325,"allowed!");
	delay(2000);
	setfillstyle(1,0);
	bar(461,239,603,425);  flag=0;
       }
     else
       if(check()==2)
	 {outtextxy(461,310,"Enter valid");
	  outtextxy(461,325,"seat numbers!");
	  delay(2000);
	  setfillstyle(1,0);
	  bar(461,239,603,425);  flag=0;
	 }
       else
	 {details();
	  flag=-1;
	 }
  }
 getch();
}

int detail::check()
{int f=0,k=0,tempr[6];
 for(int i=0;i<n;i++)
   {if(seats[i]<0 || seats[i]>48)
      {f=2;

       break;
      }
    for(int j=1;j<49;j++)
      if(seats[i]==j)
      if(r[j-1]==4)
	{f=1;
	 break;
	}
      else
	{tempr[k++]=r[j-1];
	 r[j-1]=4;
	}
   }
 if(f==1)
   {i=0;
    while(i<n) r[seats[i]-1]=tempr[i++];
    return -1;
   }
 else
   if(f==0)
     return 1;
   else
     return 2;
}

void detail::details()
{int count=0,flag=1,k;
 char ok='n',press;
 while(ok=='n' || ok=='N')
  {cleardevice();
   flag=1;
   setcolor(12);
   setbkcolor(0);
   screen();
   settextstyle(6,HORIZ_DIR,1);
   outtextxy(60,60,"Movie: ");
   outtextxy(120,60,movienm); movienm[strlen(movienm)]='\0';
   outtextxy(60,100,"CUSTOMER DETAILS:");
   outtextxy(60,135,"Email ID: ");
   while(flag==1 || count!=2)
    {count=0; flag=0;
     rectangle(180,136,380,161);
     gotoxy(24,10);
     gets(emailid);
     for(int i=0;i<strlen(emailid);i++)
      if(emailid[i]=='@' || (emailid[i]=='.' && emailid[i+1]=='c' && emailid[i+2]=='o' && emailid[i+3]=='m'))
	count++;
      else
	if(emailid[i]==' ')
	  {flag=1;
	   break;
	  }
     if(count!=2 || flag==1)
      {gotoxy(48,10);
       cout<<"Enter valid emailid!";
       delay(2000);
       setfillstyle(1,0);
       bar(180,135,550,161);
      }
    }
  emailid[strlen(emailid)]='\0';
  flag=1;
  outtextxy(60,170,"Phone number:");
  while(flag==1)
   {rectangle(180,171,380,196);
    gotoxy(24,12);
    cin>>phno;
    flag=0;
    for(int i=0;i<strlen(phno);i++)
     if(phno[i]<48 || phno[i]>57 || strlen(phno)<8)
       {flag=1;
	break;
       }
     if(flag==1)
       {gotoxy(48,12);
	cout<<"Enter valid phone number!";
	delay(2000);
	bar(180,171,580,196);
       }
   }
  outtextxy(60,205,"Address:");
  rectangle(180,206,500,231);
  gotoxy(24,14);
  gets(address); address[strlen(address)]='\0';
  outtextxy(60,245,"Number of seats: ");
  gotoxy(26,17); cout<<n;
  outtextxy(60,280,"Seat numbers: ");
  gotoxy(24,19);
  for(int i=0;i<n;i++)
  cout<<seats[i]<<" ";
  outtextxy(60,315,"Confirm details: ok?(y/n): ");
  gotoxy(33,21); cin>>ok;
  if(ok=='n'|| ok=='N')
    {outtextxy(70,350,"Change details: press 1.");
     outtextxy(70,380,"Book for another movie: press 2");
     outtextxy(70,410,"Change seats: press 3");
     press=getch();
     switch(press)
       {case '1':break;
	case '2':{list();
		 break;
		 }
	case '3':{box();
		 break;
		 }
       }
    }
  }
 book();
 getch();
}

void detail::book()
{cleardevice();
 setcolor(12);
 setbkcolor(0);
 screen();
 settextstyle(6,HORIZ_DIR,1);
 int amt,flag=0,i=0;
 price=120;
 outtextxy(60,60,movienm);
 outtextxy(60,135,"Seat numbers: ");
 gotoxy(24,10);
 while(i<n)
 cout<<seats[i++]<<" ";
 cost=n*price;
 outtextxy(60,170,"Cost of one ticket: ");
 gotoxy(29,12); cout<<"Rs. "<<price;
 outtextxy(60,205,"Total cost: ");
 gotoxy(24,14); cout<<"Rs. "<<cost;
 outtextxy(60,240,"-Pay now. Press 1.");
 outtextxy(60,275,"-Pay on arrival. Press 2.");
 outtextxy(60,310,"-Cancel booking. Press 3.");
 char pay=getch();
 switch(pay)
  {case '2':{setfillstyle(1,0);
	     bar(60,239,300,400);
	     outtextxy(70,250,"Please wait....");
	     delay(2000);
	     bar(60,239,350,400);
	     outtextxy(70,250,"Your seats have been reserved! ");
	     outtextxy(70,270,"Please collect the tickets at our counter.");
	     getch();
	     break;
	    }
   case '1':{setfillstyle(1,0);
	     bar(60,239,550,400);
	     outtextxy(60,245,"Credit card number: ");
	     rectangle(225,245,315,272);
	     gotoxy(30,17);
	     cin>>crdno;
	     do
	      {outtextxy(60,280,"Amount: ");
	       rectangle(225,280,265,305);
	       gotoxy(30,19);
	       cin>>amt;
	       if(amt!=cost)
		 {gotoxy(35,19); cout<<"Wrong amount! Check again.";
		  delay(1500);
		  setfillstyle(1,0);
		  bar(60,274,550,400);
		 }
	       }while(amt!=cost);
	     outtextxy(60,315,"Ok, book? (y/n):");        //dont know what it will do if no
	     char ok=getch(),nxt;
	     if(ok=='y' || ok=='Y')
	       {outtextxy(70,355,"Transaction processing....");
		delay(3000);
		bar(70,355,300,400);
		outtextxy(70,355,"Your tickets have been booked! ");
		getch();
	       }break;
	    }
   case '3':{flag=1;
	     numofr--;
	     break;
	    }
   default :{outtextxy(70,345,"Please enter one of given options.");
	     delay(2000); bar(70,345,500,380);
	    }
  }
 if(flag!=1)
   {for(int k=0;k<n;k++)
    if(strcmp(s[k].mov,movienm)==0)
      {i=0;
       while(i<n)
	 {s[k].ran[seats[i]-1]=4;
	  i++;
	 }
       break;
      }
   }
 if(flag!=1)
 f.write((char*)&d,sizeof(d));
 shdetail();
 getch();
}

void detail::last()
{cleardevice();
 char p[10],s[12],c[5];
 int N=1;
 detail d1;
 settextstyle(1,HORIZ_DIR,2);
 cleardevice();
 f.close();
 ifstream f1("details.dat",ios::in,ios::binary);
 while(f1.read((char*)&d1,sizeof(d1)) && N<=numofr)
   {delay(2000);
    cleardevice();
    settextstyle(1,HORIZ_DIR,2);
    outtextxy(50,70,"Details of booking number ");
    gotoxy(43,6);
    cout<<N;
    N++;
    settextstyle(1,HORIZ_DIR,2);
    outtextxy(100,100,"CUSTOMER DETAILS:");
    settextstyle(6,HORIZ_DIR,1);
    setcolor(12);
    outtextxy(100,130,"Email-id: "); outtextxy(300,130,d1.emailid);
    outtextxy(100,150,"Phone number:");
    outtextxy(300,150,d1.phno);
    outtextxy(100,170,"Address:"); outtextxy(300,170,d1.address);
    settextstyle(1,HORIZ_DIR,2);
    outtextxy(100,200,"MOVIE/ TICKET DETAILS:");
    settextstyle(6,HORIZ_DIR,1);
    setcolor(12);
    outtextxy(100,230,"Movie name:"); outtextxy(300,230,d1.movienm);
    outtextxy(100,250,"Seat numbers:");
    for(int i=0;i<d1.n;i++)
       {itoa(d1.seats[i],s,10);
	if(i!=d1.n-1) s[strlen(s)]=',';
	s[strlen(s)]='\0';
	outtextxy(37*i+300,250,s);
       }
    outtextxy(100,270,"Show time:");
    outtextxy(300,270,d1.shtime);
    outtextxy(100,290,"Date:"); outtextxy(300,290,d1.shdate);
    outtextxy(100,310,"Cost of tickets:");
    itoa(d1.cost,c,10); outtextxy(300,310,c);
    outtextxy(100,330,"Location:"); outtextxy(300,330,d1.location);
    getch();
   }
 cleardevice();
 outtextxy(100,100,"THANK YOU FOR BOOKING WITH US!");
 outtextxy(100,130,"ENJOY YOUR EXPERIENCE WITH PHOENIX!");
 getch();
 exit(0);
}

void detail::shdetail()
{cleardevice();
 char ch,nxt,bk;
 numofr++;
 outtextxy(60,135,"Number of bookings done");
 gotoxy(34,10);
 cout<<numofr;
 outtextxy(60,170,"Continue booking? (y/n):");
 gotoxy(33,12);
 cin>>ch;
 if(ch=='y' || ch=='Y')
   list();
 else if(numofr!=0)
  {outtextxy(60,230,"Display details of previous bookings- press ->");
   nxt=getch();
    if(nxt=='6')
      last();
  }
 else
  {outtextxy(60,230,"Book again or exit? (b/e)");
   bk=getch();
    if(bk=='b' || bk=='B')
     list();
    else
     exit(0);
  }
}

void detail::home()
{int gdriver=DETECT,gmode,errorcode;
 initgraph(&gdriver,&gmode,"c:\\tc\\bgi");
 cleardevice();
 int flag=0;
 setcolor(12);
 setbkcolor(0);
 settextstyle(4,HORIZ_DIR,4);
 settextstyle(4,HORIZ_DIR,4);
 outtextxy(150,50,"PHOENIX CINEMAS");
 int x=50, y=2, z=400;
 for(int i=0;i<4;i++)
    {line(x,2,x,z);
     x+=20; y+=10; z-=50;
    }
 settextstyle(3,HORIZ_DIR,2);
 outtextxy(120,150,"ABOUT US");
 settextstyle(6,HORIZ_DIR,1);
 outtextxy(125,180,"Welcome to phoenix cinemas!");
 outtextxy(120,200,"Phoenix cinemas is dedicated to giving Chennai the");
 outtextxy(120,220,"finest cinema experience.Equipped with state of the ");
 outtextxy(120,240,"art technology including RDX-3D,4 way speakers,pushback");
 outtextxy(120,260,"seats and more features,all designed to give you the" );
 outtextxy(120,280,"best entertainment ever!");
 outtextxy(120,300,"ENJOY!");
 outtextxy(180,400,"SEE MOVIES RUNNING NOW. press -> ");
 while(flag==0)
   {char ch=getch();
    if(ch=='6')
      {list();
       flag=1;
      }
    else
      {setfillstyle(1,0);
       bar(180,400,500,430);
       outtextxy(180,400,"Please enter ->");
      }
   }
}


main()
{int gdriver=DETECT,gmode,errorcode;
 initgraph(&gdriver,&gmode,"c:\\tc\\bgi");
 settextstyle(6,HORIZ_DIR,1);
 setcolor(12);
 assigntime();
 setbox();
 d.first();
 d.home();
 getch();
 closegraph();
 return 0;
}

