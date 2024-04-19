#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#define CHANNEL_NAME "/tmp/my_channel"


int main() {
    
    mkfifo(CHANNEL_NAME, 0666);

    int fd = open(CHANNEL_NAME, O_WRONLY);
    if (fd < 0){
        perror("Erorr of opening pipe for writing");
        exit(1);
    }

    srand(time(NULL));
    for(int i = 0; i < 10; i++){
        int num = rand() % 100;
        write(fd, &num, sizeof(num));
        printf("Numder is writed: %d\n", num);
        sleep(1);
    }
    
    close(fd);

    return 0;
}


