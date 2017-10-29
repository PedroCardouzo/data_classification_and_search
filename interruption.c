#include <stdio.h>
#include <signal.h>
#include <unistd.h>


#define MAX_TIME 10

typedef unsigned char bool;
#define true 1
#define false 0

bool overtime = false;

void callback(){
	overtime = true;
	return;
}

void printmsg(){
	printf("You went overtime!!\n");
}

int loop(){
	double ans = 0;
	int var =0;
	overtime = 0;
	alarm(5);
	for (int i=0;i<100000;i++){
    	for (int j=0;j<100000;j++){
    		for(int k=0;k<100000;k++){
				ans = (ans*2-4)/5*4;
				if(overtime){
					printmsg();
					return 1;
				}
    		}
    	}
    	printf("test\n");
    }

	printf("ans = %lf", ans);
}

int main(){
	signal(SIGALRM, callback);
	loop();
	loop();
	return 0;
}