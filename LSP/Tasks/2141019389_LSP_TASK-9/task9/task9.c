#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    struct dirent *entry;
    DIR *dp;

    // Step 1: List all files and directories in the current working directory
    char cwd[1024];
    getcwd(cwd, sizeof(cwd)); // Get current directory
    printf("Current Directory: %s\n", cwd);

    dp = opendir(cwd);
    if (dp == NULL) {
        perror("opendir");
        return 1;
    }

    printf("Contents of current directory:\n");
    while ((entry = readdir(dp)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dp);

    // Step 2: Change directory to /tmp
    if (chdir("/tmp") != 0) {
        perror("chdir");
        return 1;
    }

    // Step 3: Create a new directory "testdir" in /tmp with 755 permissions
    if (mkdir("testdir", 0755) != 0) {
        perror("mkdir");
        return 1;
    }

    printf("Directory '/tmp/testdir' created successfully with permissions 755.\n");

    return 0;
}
