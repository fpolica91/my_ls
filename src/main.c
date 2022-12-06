#include <dirent.h>
#include <libgen.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define NORMAL_COLOR "\x1B[0m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"


void my_ls(char *path) {

  DIR *dir = opendir(path);
  if (dir == NULL)
    return;
  struct dirent *dp;

  while ((dp = readdir(dir)) != NULL) {
    if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) {
      continue;
    }
    // if it is file
    if (dp->d_type != DT_DIR) {
      printf("%s%s\n", BLUE, dp->d_name);
    } else if (dp->d_type == DT_DIR) {
      printf("%s%s\n", GREEN, dp->d_name);
      char d_path[255];
      sprintf(d_path, "%s/%s", path, dp->d_name);
      my_ls(d_path);
    }
  }
  closedir(dir);
}

int main() {
  char cwd[PATH_MAX];
  getcwd(cwd, sizeof(cwd));
  my_ls(cwd);
  return 0;
}
