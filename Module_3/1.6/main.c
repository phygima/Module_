#include "list_files.h"

//Написать простой файловый менеджер, позволяющий
//просматривать содержимое каталогов и отображающий типы файлов.

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Использование: %s <путь к каталогу>\n", argv[0]);
        return 1;
    }

    list_files(argv[1]);

    return 0;
}