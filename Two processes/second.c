#include <stdio.h>
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
  
int main() 
{ 
    int fd1; 
  
    char * myfifo = "/tmp/myfifo"; 
    mkfifo(myfifo, 0666); 
    
    char * myfifo_1 = "/tmp/myfifo_1"; 
    mkfifo(myfifo_1, 0666);
  
    char str1[80];
    char format_string[80]="%d,%d";
 
    int n1, n2;
    double mean;

    while (1) 
    { 
    	/* opens a file to read*/
    	fd1 = open(myfifo,O_RDONLY); 
        read(fd1, str1, 80); 
 
    	/* send an info message to the first one */
    	fd1 = open(myfifo_1, O_WRONLY);
    	char *send_string = "Data is received from second\n";
    	/* writes the message to the file for informing first */
    	write(fd1, send_string, strlen(send_string)+1); 
        close(fd1);
                    
        /* if the first input char is q, exit  */
        if (str1[0] == 'q') exit(EXIT_SUCCESS) ;
        /* read numbers from input line */
        sscanf(str1, format_string, &n1, &n2);
        /* calculation of mean and sum*/
        mean = (n1 + n2) / 2.0; 
        printf("mean value is: %.2f, sum is: %d\n", mean, n1 + n2); 
        close(fd1); 
    } 
    return 0; 
} 

