#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void get_permissions(mode_t mode, char *str) {

    strcpy(str, "----------");

    if (S_ISDIR(mode)) str[0] = 'd';
    if (S_ISCHR(mode)) str[0] = 'c';
    if (S_ISBLK(mode)) str[0] = 'b';

    if (mode & S_IRUSR) str[1] = 'r';
    if (mode & S_IWUSR) str[2] = 'w';
    if (mode & S_IXUSR) str[3] = 'x';

    if (mode & S_IRGRP) str[4] = 'r';
    if (mode & S_IWGRP) str[5] = 'w';
    if (mode & S_IXGRP) str[6] = 'x';

    if (mode & S_IROTH) str[7] = 'r';
    if (mode & S_IWOTH) str[8] = 'w';
    if (mode & S_IXOTH) str[9] = 'x';
}

void list_contents(const char *dir_name, int depth) {

    DIR *pDIR;
    struct dirent *pDirEnt;
    struct stat file_stats;

    pDIR = opendir(dir_name);

    if (pDIR == NULL) {
        fprintf(stderr, "%s %d: opendir() failed (%s)\n", __FILE__, __LINE__, strerror(errno));
        return;
    }

    printf("%*s%s:\n", depth * 4, "", dir_name);

    while ((pDirEnt = readdir(pDIR)) != NULL) {

        if (pDirEnt->d_name[0] == '.') {
            continue;
        }

        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dir_name, pDirEnt->d_name);

        if (stat(path, &file_stats) == -1) {
            perror(path);
            continue;
        }

        char permissions[11];
        get_permissions(file_stats.st_mode, permissions);

        struct passwd *pw = getpwuid(file_stats.st_uid);
        const char *user_name = (pw != NULL) ? pw->pw_name : "unknown";

        struct group *grp = getgrgid(file_stats.st_gid);
        const char *group_name = (grp != NULL) ? grp->gr_name : "unknown";

        char time_str[20];
        strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stats.st_mtime));

        printf("%*s%s %4lu %s %s %9lu %s %s\n", (depth + 1) * 4, "", permissions, file_stats.st_nlink, user_name, group_name, file_stats.st_size, time_str, pDirEnt->d_name);

        if (S_ISDIR(file_stats.st_mode)) {

            printf("\n");
            list_contents(path, depth + 1);
            printf("\n");
        }
    }

    closedir(pDIR);
}

int main() {

    const char *start_dir = ".";
    list_contents(start_dir, 0);

return 0;
}
