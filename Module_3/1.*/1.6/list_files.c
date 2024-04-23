#include "list_files.h"


void list_files(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_info;

    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    printf("Directory contents %s:\n", path);
    while ((entry = readdir(dir)) != NULL)
    {
        char full_path[1024];
        sprintf(full_path, "%s/%s", path, entry->d_name);

     if (stat(full_path, &file_info) == -1) {
            perror("stat");
            continue;
        }
        printf("%s\t", entry->d_name);

       if (S_ISREG(file_info.st_mode)) {
            printf(" (Simple file)\n");
        } else if (S_ISDIR(file_info.st_mode)) {
            printf(" (Catalog)\n");
        } else if (S_ISLNK(file_info.st_mode)) {
            printf(" (Symbolic link)\n");
        } else {
            printf(" (Unknown type)\n");
        }

    }
    
    closedir(dir);
}