#include<sys/types.h>
#include<stdio.h>
#include<math.h>
#include<curses.h>
#include<unistd.h>
#include<termios.h>
#include<term.h>
#include<stdlib.h>
static struct termios initial_settings, new_settings;
static int peek_character = -1;
float cannon(float x, int dir, float v);
void init_keyboard();
void close_keyboard();
int kbhit();
void print_blast(float x);
int readch();
void print(float v, int dir, float *x, char in,float *time, int *flag, int *status, int level);
void move_truck(float *v, int *dir, float *x, char *key, float *time, int *flag, int *status, int level){
	if(*status!=1){
	float u = *v;
	if(*key=='a' && *dir == 1){
		//printf("Entering key:a and dir: 1 with v=%f and x= %f\n",*v,*x);
		for(;*v>0;*v=*v-1){
			u=*v+1;
			*x=*x+((u*0.1)-(0.5*2*0.1*0.1));
			system("clear");
			print(*v,*dir,x,*key,time,flag,status,level);
			usleep(100000);
		}
		*dir=-1;
		for(;*v<2;*v=*v+1){
			*x=*x-(0.5*2*0.1*0.1);
			system("clear");
			print(*v,*dir,x,*key,time,flag,status,level);
			usleep(100000);
		}
	}
	else if(*key == 'a' && *dir == -1){
		//printf("Entering key:a and dir: -1\n");
		for(;*v<2;*v=*v+1){
			u=*v+1;
			*x=*x-(2*0.1);
			system("clear");
			print(*v,*dir,x,*key,time,flag,status,level);
			usleep(100000);
		}
		*dir=-1;
	}
	else if(*key=='d' && *dir == -1){
		//printf("Entering key:d and dir: -1 with v=%f and x= %f\n",*v,*x);
		for(;*v>0;*v=*v-1){
			u=*v+1;
			*x=*x-((u*0.1)-(0.5*2*0.1*0.1));
			system("clear");
			print(*v,*dir,x,*key,time,flag,status,level);
			usleep(100000);
		}
		*dir=1;
		for(;*v<2;*v=*v+1){
			*x=*x+(0.5*2*0.1*0.1);
			system("clear");
			print(*v,*dir,x,*key,time,flag,status,level);
			usleep(100000);
		}
	}
	else if(*key == 'd' && *dir == 1){
		//printf("Entering key:d and dir: 1\n");
		for(;*v<2;*v=*v+1){
			u=*v+1;
			*x=*x+(2*0.1);
			system("clear");
			print(*v,*dir,x,*key,time,flag,status,level);
			usleep(100000);
		}
		*dir=1;
		
	}
	else if(*key == 'a' && *dir == 0){
		*dir=-1;
		//printf("Entering key:a and dir: 0 \n");
		for(;*v<2;*v=*v+1){
			u=*v+1;
			//printf("v is :%f and x is :%f\n",*v,*x);
			*x=*x-(0.5*2*0.1*0.1);
			system("clear");
			print(*v,*dir,x,*key,time,flag,status,level);
			usleep(100000);
		}
	}
	else if(*key == 'd' && *dir == 0){
		*dir=1;
		//printf("Entering key:d and dir: 0\n");
	 	for(;*v<2;*v=*v+1){
			*x=*x+(0.5*2*0.1*0.1);
			system("clear");
			print(*v,*dir,x,*key,time,flag,status,level);
			usleep(100000);
		}
	}
	}
	else{
		print_blast(*x);
	}
}
void print_blast(float x){
	system("clear");
	int counter=10;
	float pos=0;
	while(counter!=0){
		printf("\n");
		counter=counter-0.5;
	}		
	while(pos<=40){
		if(pos==0){
			printf("\\*/");
		}
		if( pos-x <= 0.25 && pos-x >= -0.25 ){	
			printf("BOOM\n");
 			break;
		}
		else{
			printf(" ");
		}
		pos=pos+0.5;
	}
	printf("The Game is Over: You were hit by the cannon\n");		
}
void print(float v, int dir, float *x, char in, float *time, int *flag, int *status, int level ){
	printf("YOUR CURRENT POSITION: %f\n",*x);
	*time=*time+0.1;
	if((int)(*time*10)%20==0){
		*flag=1;
		*time=0;
	}
	if (*x >=40){
			*x=40;
			printf("Congratulations, You have successfully completed this level\n");
			*status=1;
		}
	if((int)(*time*10) % 20!=0 && *flag == 0 && *status != 1){
	//printf("Entering print with v: %f",v);
		
		if(*x < 1){
			*x=1;
		}
		int counter=12;
		float pos=0;
		while(counter!=0){
			printf("\n");
			counter=counter-0.5;
		}
		while(pos<=40){
			if(pos==0){
				printf("\\*/");
			}
			if(pos == 40){
				printf("!");
			}
				if( pos-*x <= 0.25 && pos-*x >= -0.25 ){	
					printf("oO");
	 				break;
				}
			
			else{
				printf(" ");
			}
			pos=pos+0.5;
		}
		printf("\n");
	}
	else if(*status != 1){
		float i,j;
		
		float angle;
		if(level == 4){
			angle=cannon(*x,dir,v);
		}
		else if(level == 3){
			angle=cannon(*x+0.3,dir,v);
		}
		else if(level == 2){
			angle=cannon(*x+0.5,dir,v);
		}
		else{
			angle=cannon(*x+0.7,dir,v);
		}
		float xPos = 20*cos(angle)*(*time);
		float yPos = (xPos*tan(angle))-((10*xPos*xPos)/(2*400*cos(angle)*cos(angle)));
		
		if (*x >40){
			*x=40;
		}
		if(*x < 1){
			*x=1;
		}
		float pos=0;
		 for(i=6;i>0;i=i-0.5){
			 for(j=0;j<=40;j=j+0.5){
				//float y=(j*tan(angle))-((10*j*j)/(2*10*1.414*10*1.414*cos(angle)*cos(angle)));
				//printf("Y: %f, i:%f and j:%f\n",y,i,j);
				if(i == 0 ){
					if(*x - xPos <= 0.2 && *x-xPos >= -0.2){
						*status = 1;
						print_blast(*x);
						
					}
				}
 				else if(j-xPos <= 0.25 &&   j-xPos >= -0.25 ){
					 if(i-yPos <= 0.25 &&   i-yPos >= -0.25){
						 printf("*");
						 break;
						 /*for(;check<(int)(*x-j);check++){
							printf(" ");
						}*/
						//printf(".");	
					 }
				 }
				//else if(i-y <= 0.05 &&   i-y >= -0.05 ){
					//
					// printf(".");
					/*for(;check<(int)(*x-j);check++){
						printf(" ");
					}*/
					//printf(".");
				//}
				 
				 else{
					 printf(" ");
				 }
			 }
			 printf("\n");
		 }
		while(pos<=40 && *status != 1){
				
				//printf("\nxPos: %f and yPos: %f and pos:%f \n",xPos,yPos,pos);
				if(pos==0){
					printf("\\*/");
				}
				if(pos == 40){
					printf("!");
				}
				else if( pos-*x <= 0.25 && pos-*x >= -0.25 ){	
					printf("oO");
				}
				
				//if(yPos <= 0.2){
					//if(xPos-pos <= 0.25 && xPos-pos >= -0.25){
						//printf("BOOM");
						//printf("\nxPos: %f and yPos: %f and time:%f \n",xPos,yPos,*time);
						
					//}
				//}
						
						
			else{
				printf(" ");
			}
			if(yPos >= 0 && yPos <=0.23){
				if(xPos - *x <= 0.35 && xPos-*x >= -0.35){ 
					*status=1;
					
				}
			}
			pos=pos+0.5;
		}
		if(*status == 1){
			print_blast(*x);
		}
		else{
			printf("\n");
			if(yPos < 0){
				//printf("....\n");
				*flag=0;
			}
		}
	}
	
}	
float cannon(float x, int dir, float v){  //time is the current time of the program
	//int status=0; //status is initially set to zero assuming that the target is not hit
	//float td=time-t1; //td is the time difference b/w the time obtained from the table and the actual situaton time
	//if(td<1){ //because maximum time difference can be 2 sec, hence we are checking whether it is at right half of the time difference or to the left
		//if(r==0){ //if time difference is to right half and the truck isn't retarding
			//x=x-(2*td); //2 is the max speed of the truck
		//}`
		//else{
			//x=x-(0.5*2*td*td);// if truck is retarding with -2 m per sec square, the we have calculated the distance
		//}
	//}
	//else if(td>=1){  //if the time difference is to the right half
		//if(a==0){ //if truck is not accelerated
			//x=x-(2*td); 
		//}
		//else{ //if truck is accelerating
			//x=(x-1)-(0.5*2*(t1-time+2)*(t1-time+2)); 
		//}
	//}	
	float y=(asin(10*x/400))/2;  //arcsin of range
	float t=(2*20*sin(y))/10; //time fo flight of the calculated angle 'y'
	float u;
	if(v==0){
		u=v;
	}
	else{
		u=2;
	}
	float sl,ss;
	if(dir==1 || dir==0){
		sl=x+((u*0.163)+(0.5*2*pow(t,2))); //largest distance to which truck can go in the given time of flight
		ss=x+((u*0.163)-(0.5*2*pow(t,2)));//smallest distance to which the truck can go
	}
	else{
		sl=x-((u*0.163)+(0.5*2*pow(t,2))); //largest distance to which truck can go in the given time of flight
		ss=x-((u*0.163)-(0.5*2*pow(t,2)));//smallest distance to which the truck can go
	}
	float ql=(asin(10*sl/400))/2;//Largest angle of elevation
	float qs=(asin(10*ss/400))/2;//Smallest angle af elevation
	float qa=(ql+qs)/2;//Qaverage at which we have to shoot
	//float tn=2*10*1.414*sin(qa)/10;//new time of flight of the cannon ball
	//float range=400*sin(2*qa)/10; //range of the cannonball at the new angle
 	
 	//printf("Range: %f\n",range);//t1=t1+tn; // new current runing time of the program
 	return qa;
}
//void next(){ //function is implemented at the end after al the calculations have been made
	//if((x-range)<=0.2&&(x-range)>=-0.2){ //because diameter of the bomb explosion is 0.7 meters
		//status=1; //Bomb has hit the target
	//}
		//if(status==1){
			//cout<<"The target is hit at t="<<t1<<"and at position "<<x<<"\n";
		//}
//}		
int main(){
	float v=0; //dir=+ve for D and -ve for A
	int dir=0;
	float x=10;
	char in;
	float time=0;
	int flag = 0;
	int status=0;
	printf("Lets start the game: To move the truck, Press A to move left and D to move it Right, and Q to exit\n");
	printf("SELECT THE LEVEL YOU WANT TO BEGIN WITH\n");
	printf("LEVEL 1: AMATEUR\nLEVEL 2: SEMI PRO\nLEVEL 3: PROFESSIONAL\nLEVEL 4: LEGENDARY\n");
	int ch;
	scanf("%d",&ch);
	switch (ch){
		case 4:
		while(in != 'q' && status != 1){
			//x=x+0.1;
			init_keyboard();
			usleep(100000);
			if(kbhit()){
				//printf("=>");
				in=readch();
				//printf("Flag:%d\n",flag);
				move_truck(&v,&dir,&x,&in,&time,&flag,&status,ch);
			}
			else{
				if(dir==1){
					x=x+(2*0.1);
				}
				else if(dir==-1){
					x=x-(2*0.1);
				}
				system("clear");
				//printf("Flag:%d\n",flag);	
				print(v,dir,&x,in,&time,&flag,&status,ch);
				usleep(100000);	
			}
		}
	close_keyboard();
	break;
	case 3:
		while(in != 'q' && status != 1){
			//x=x+0.2;
			init_keyboard();
			usleep(100000);
			if(kbhit()){
				//printf("=>");
				in=readch();
				//printf("Flag:%d\n",flag);
				move_truck(&v,&dir,&x,&in,&time,&flag,&status,ch);
			}
			else{
				if(dir==1){
					x=x+(2*0.1);
				}
				else if(dir==-1){
					x=x-(2*0.1);
				}
				system("clear");
				//printf("Flag:%d\n",flag);	
				print(v,dir,&x,in,&time,&flag,&status,ch);
				usleep(100000);	
			}
		}
	close_keyboard();
	break;
	case 2:
		while(in != 'q' && status != 1){
			//x=x+0.3;
			init_keyboard();
			usleep(100000);
			if(kbhit()){
				//printf("=>");
				in=readch();
				//printf("Flag:%d\n",flag);
				move_truck(&v,&dir,&x,&in,&time,&flag,&status,ch);
			}
			else{
				if(dir==1){
					x=x+(2*0.1);
				}
				else if(dir==-1){
					x=x-(2*0.1);
				}
				system("clear");
				//printf("Flag:%d\n",flag);	
				print(v,dir,&x,in,&time,&flag,&status,ch);
				usleep(100000);	
			}
		}
	close_keyboard();
	break;
	case 1:
		while(in != 'q' && status != 1){
			//x=x+0.5;
			init_keyboard();
			usleep(100000);
			if(kbhit()){
				//printf("=>");
				in=readch();
				//printf("Flag:%d\n",flag);
				move_truck(&v,&dir,&x,&in,&time,&flag,&status,ch);
			}
			else{
				if(dir==1){
					x=x+(2*0.1);
				}
				else if(dir==-1){
					x=x-(2*0.1);
				}
				system("clear");
				//printf("Flag:%d\n",flag);	
				print(v,dir,&x,in,&time,&flag,&status,ch);
				usleep(100000);	
			}
		}
	close_keyboard();
	break;
	default:
	printf("Wrong CHOICE\n");
}
	return 0;
}
void init_keyboard()
{
    tcgetattr(0,&initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_lflag &= ~ISIG;
    new_settings.c_cc[VMIN] = 0;
    new_settings.c_cc[VTIME] = 1;
    tcsetattr(0, TCSANOW, &new_settings);
}

void close_keyboard()
{
    tcsetattr(0, TCSANOW, &initial_settings);
}

int kbhit()
{
    char ch;
    int nread;

    if(peek_character != -1)
        return 1;
    new_settings.c_cc[VMIN]=0;
    tcsetattr(0, TCSANOW, &new_settings);
    nread = read(0,&ch,1);
    new_settings.c_cc[VMIN]=1;
    tcsetattr(0, TCSANOW, &new_settings);

    if(nread == 1) {
        peek_character = ch;
        return 1;
    }
    return 0;
}

int readch()
{
    char ch;

    if(peek_character != -1) {
        ch = peek_character;
        peek_character = -1;
        return ch;
    }
    read(0,&ch,1);
    return ch;
}
	




