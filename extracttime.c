#define _POSIX_C_SOURCE 200809L

#include <linux/linkage.h>
#include <linux/export.h> //FOR EXPORTING OUR SYSTEM CALL AS A SYMBOL
#include <linux/time.h>  //FOR FUNCTION current_kernel_time
#include <asm/uaccess.h> //FOR FUNCTIONS LIKE access_ok and copy_to_user
#include <linux/printk.h>  //FOR FUNCTION printk
#include <linux/slab.h> 

asmlinkage int sys_my_xtime(struct timespec* current_time)
{
    int nbytes;

    // USING access_ok FUNCTION CHECK THE LOCATION current_time IS IN USER SPACE AND WEATHER IT IS READABLE & WRITABLE 
    if(access_ok(VERIFY_WRITE,current_time,sizeof(current_time))){

             // GET THE SYSTEM TIME FROM KERNEL FUNCTION AND STORE IN STRUCTURE X
             struct timespec x=current_kernel_time();
             
             //COPY TIME FROM LOCATION OF X INTO POINTER CURRENT TIME
              nbytes=copy_to_user(current_time, &x, sizeof(x));
             
             //CHECK HOW MANY BITES COULD NOT COPY
             if(nbytes==0){                  
		printk(KERN_ALERT "\nTIME in nano second %ld",current_time->tv_nsec); 
   	     }
             else{
		printk(KERN_ALERT "\nCOPY TO USER FAIL");
             }	 
   }
    else{

       printk(KERN_ALERT "\nINVALID USER SPACE ACCESS");
    }

   return 0;

    
}
EXPORT_SYMBOL(sys_my_xtime);
