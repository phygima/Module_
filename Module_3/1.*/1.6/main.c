#include "list_files.h"

//Написать простой файловый менеджер, позволяющий
//просматривать содержимое каталогов и отображающий типы файлов.

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory path>\n", argv[0]);
        return 1;
    }

    list_files(argv[1]);

    return 0;
}