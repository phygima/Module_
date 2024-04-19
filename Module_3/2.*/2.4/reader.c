#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define CHANNEL_NAME "/tmp/my_channel"


int main() {

    int fd = open(CHANNEL_NAME, O_RDONLY);
    if (fd < 0){
        perror("Erorr of opening pipe for writing");
        exit(1);
    }

    int num;
    while(read(fd, &num, sizeof(num)) > 0){
        printf("Accepted number: %d\n", num);
    }

    
    close(fd);

    return 0;
}


