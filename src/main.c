#include <dirent.h>
#include <libgen.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define NORMAL_COLOR "\x1B[0m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"

// void show_dir_content(char *path) {
//   DIR *d = opendir(path); // open the path
//   if (d == NULL)
//     return;           // if was not able, return
//   struct dirent *dir; // for the directory entries
//   while ((dir = readdir(d)) !=
//          NULL) // if we were able to read somehting from the directory
//   {
//     if (dir->d_type !=
//         DT_DIR) // if the type is not directory just print it with blue color
//       printf("%s%s\n", BLUE, dir->d_name);
//     else if (dir->d_type == DT_DIR && strcmp(dir->d_name, ".") != 0 &&
//              strcmp(dir->d_name, "..") != 0) // if it is a directory
//     {
//       printf("%s%s\n", GREEN, dir->d_name); // print its name in green
//       char d_path[255]; // here I am using sprintf which is safer than strcat
//       sprintf(d_path, "%s/%s", path, dir->d_name);
//       show_dir_content(d_path); // recall with the new path
//     }
//   }
//   closedir(d); // finally close the directory
// }

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
