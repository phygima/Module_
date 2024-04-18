#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

void list_files(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_info;

    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    printf("Содержимое каталога %s:\n", path);
    while ((entry = readdir(dir)) != NULL) {
        char full_path[1024];
        sprintf(full_path, "%s/%s", path, entry->d_name);

        if (stat(full_path, &file_info) == -1) {
            perror("stat");
            continue;
        }

        printf("%s\t", entry->d_name);

        if (S_ISREG(file_info.st_mode)) {
            printf(" (Обычный файл)\n");
        } else if (S_ISDIR(file_info.st_mode)) {
            printf(" (Каталог)\n");
        } else if (S_ISLNK(file_info.st_mode)) {
            printf(" (Символическая ссылка)\n");
        } else {
            printf(" (Неизвестный тип)\n");
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Использование: %s <путь к каталогу>\n", argv[0]);
        return 1;
    }

    list_files(argv[1]);

    return 0;
}
