#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	int loop = 0;
	int i = 0;
	chrt(3);
	while(loop <3){
		loop ++;
		if(!fork()){
			if(loop == 1){
			    chrt(20);
		    }
		    else if(loop == 2){
			    chrt(15);
		    }
		    while(1){
			    sleep(1);
			    printf("P %d heart beat %d \n", loop, i++);
			    if(loop == 1 && i == 5){
				    chrt(5);
			    }
			    if(loop == 3 && i == 10){
				    chrt(3);
		        }
            }
		}
	}
	return 0;
}