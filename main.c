#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CompFile {
  char *path;
  char **contents;
  int len;
};

void eat_buffer();
void clear_term();
void show_help();
struct CompFile fetch_file(char *path);
void display_content(struct CompFile comp_f);
void edit_line(struct CompFile *comp_f, int curr_line);
void display_line(struct CompFile comp_f, int n_line);
void save_to_file(struct CompFile comp_f);
void show_number_of_lines(struct CompFile comp_f);
int main(int charc, char *charv[]) {
  char comm[20];
  if (charc > 1) {
    clear_term();
    printf("tmin 0.1\n\n");
    struct CompFile fetch_c = fetch_file(charv[1]);
    while (true) {
      printf("+ ");
      scanf("%19s", comm);
      eat_buffer();

      if (strcmp(comm, "q") == 0)
        return 1;
      else if (strcmp(comm, "cls") == 0)
        clear_term();
      else if (strcmp(comm, "h") == 0) {
        show_help();
      } else if (strcmp(comm, "v") == 0)
        display_content(fetch_c);
      else if (strncmp(comm, "v=", 2) == 0) {
        char *n_comm = comm;
        n_comm++;
        n_comm++;
        int v_int = atoi(n_comm);
        display_line(fetch_c, v_int);
      } else if (strncmp(comm, "i=", 2) == 0) {
        char *loc_comm = comm;
        loc_comm++;
        loc_comm++;
        int f_int = atoi(loc_comm);
        edit_line(&fetch_c, f_int);
      } else if (strcmp(comm, "i") == 0)
        printf("??: wrong usage of i, use i=<line> instead.\n");
      else if (strcmp(comm, "w") == 0) {
        save_to_file(fetch_c);
      }


      else if (strcmp(comm, "ln") == 0) { 
        show_number_of_lines(fetch_c);
      }
      else
        printf("??: '%s' -> invalid, use [h] for help.\n", comm);
    }
  } else {
    printf("tmin takes a filename argument: none provided!\n");
  }
  return 0;
}

void display_content(struct CompFile comp_f) {
  if (comp_f.len < 1) {
    printf("%d\n", comp_f.len);
  }
  for (int i = 0; i < comp_f.len; i++) {
    char *curr_line = comp_f.contents[i];

    if (curr_line == NULL)
      printf("%d.\n", i + 1);
    else if (strcmp(curr_line, "(null)") == 0) {
    
      printf("%d.\n", i + 1);
    }
    else
      printf("%d. %s", i + 1, curr_line);
  }
}

void clear_term() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

struct CompFile fetch_file(char *path) {
  char file_state = 'r';
  FILE *fptr;
  char **contents = calloc(1024, 1024 * sizeof(char *));
  char buf[1024];
  fptr = fopen(path, "r");
  if (fptr == NULL) {
    fptr = fopen(path, "w");
    file_state = 'w';
  }
  int count_ln = 0;
  while (fgets(buf, sizeof(buf), fptr) != NULL) {
    contents[count_ln] = strdup(buf);
    count_ln += 1;
  }
  fclose(fptr);

  struct CompFile comp_f;
  comp_f.path = path;
  comp_f.contents = contents;
  comp_f.len = count_ln;

  printf("%c: %s\n", file_state, path);
  return comp_f;
}

void edit_line(struct CompFile *comp_f, int curr_line) {
  int n_line = curr_line - 1;
  char buf[1024];
  printf("> ");
  fgets(buf, 1024, stdin);
  comp_f->contents[n_line] = strdup(buf);

  if (curr_line > (*comp_f).len)
    comp_f->len = curr_line;
}

void eat_buffer() {
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF)
    ;
}

void display_line(struct CompFile comp_f, int n_line) {
  printf("%d. %s\n", n_line, comp_f.contents[n_line - 1]);
}



void save_to_file(struct CompFile comp_f) {
  FILE *fptr;
  fptr = fopen(comp_f.path, "w");
  fprintf(fptr, "");

  fptr = fopen(comp_f.path, "a");

  for (int i=0; i < comp_f.len; i++) {
    if (comp_f.contents[i] == NULL) {
      fprintf(fptr, "\n");
    } else {
      fprintf(fptr, "%s", comp_f.contents[i]);
    }
  }
  fclose(fptr);

  printf("w: %d lines written!\n", comp_f.len);
}

void show_help() {
  printf("basic commands:\n");
  printf("h   -> display this message\n");
  printf("q   -> exit application with 1\n");
  printf("v   -> display the entire file\n");
  printf("cls -> clear stdin\n");
  printf("ln  -> Show number of lines\n");
  printf("w   -> Save file\n\n");

  printf("specific commands:\n");
  printf("v=<line>  -> show specific line\n");
  printf("i=<line>  -> insert into line\n");
}

void show_number_of_lines(struct CompFile comp_f) {
  printf("len: %d\n", comp_f.len);
}
