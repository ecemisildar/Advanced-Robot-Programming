#include <stdio.h>
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <sys/wait.h>


void body(){
    
    int fd1; 
  
    char * myfifo = "/tmp/myfifo"; 
    mkfifo(myfifo, 0666); 
    
  
    char str1[80];
    char format_string[80]="%d,%d";
 
    int n1, n2;
    double mean;

    while (1) 
    { 
    	/* opens a file to read*/
    	fd1 = open(myfifo,O_RDONLY); 
        read(fd1, str1, 80);                    
        /* if the first input char is q, exit  */
        if (str1[0] == 'q') exit(EXIT_SUCCESS) ;
        /* read numbers from input line */
        sscanf(str1, format_string, &n1, &n2);
        /* calculation of mean and sum*/
        mean = (n1 + n2) / 2.0; 
        printf("mean value is: %.2f, sum is: %d\n", mean, n1 + n2); 
        close(fd1); 
    } 	
}

void parent(){

    int fd; 
   
    char * myfifo = "/tmp/myfifo"; 
    mkfifo(myfifo, 0666); 
  
    char input_string[80];

    while (1) 
    { 
      	/* opens a file to write*/
        fd = open(myfifo, O_WRONLY); 

        printf("Please, write two integer numbers, separated by commas (,), or q to quit\n");
        /* to be sure that the previous is executed immediately */
	fflush(stdout);
        /* read a full input line */
        fgets(input_string, 80 , stdin); 
        /* writes it in to the file */
        write(fd, input_string, strlen(input_string)+1); 
        close(fd); 
        /* delay to prevent working before child */
        usleep(100000);  
        /* if the first input char is q, exit  */
        if (input_string[0] == 'q') exit(EXIT_SUCCESS) ;
  
    } 
}

int main(int argc, char *argv[])
{
    pid_t child;
   int res;

    child = fork();
    if (child < 0) {
        perror("Fork");

        return -1;
    }

    if (child == 0) {
        body();

	return 0;
    }
    parent();

    wait(&res);

    return 0;
}

