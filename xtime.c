#include<stdio.h>
#include<unistd.h>
#include<linux/unistd.h>
#include <inttypes.h>
#include <math.h>
#include<time.h>
int main(){
	
        int y;
        time_t s;
        long ns;
        
        struct timespec ct;//user level structure element(variable) for storing                            //time in sec and time in nano seconds
	
        y = syscall(327,&ct);// we have made a entry of our implemented system                               //call with number 327
        if(y==0){
 		printf("\nSuccess! Syscall return value :%d\n",y);              
                
                s = ct.tv_sec;
                ns=(long)ct.tv_nsec;
                
                printf("\nTime in seconds: %"PRIdMAX"",(intmax_t)s);
                printf("\nTime in nano seconds: %ld",ns);
                printf("\n\n");               
                
        }
        else{
               printf("\nSorry! System Call Failed. Return value: %d",y);
               printf("\n\n");
        }
	
        return 0;
}
