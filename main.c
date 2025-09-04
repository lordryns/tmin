#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct CompFile{
  char **contents;
  int len;
};



void eat_buffer();
void clear_term(); 
struct CompFile fetch_file(char *path);
void display_content(struct CompFile comp_f);
void edit_line(struct CompFile comp_f, int curr_line);


int main(int charc, char *charv[])
{
  char comm[20];
  if (charc > 1)
  {
    clear_term(); printf("tmin 0.1\n\n");
    struct CompFile fetch_c = fetch_file(charv[1]);
    while (true)
    {
      printf("+ ");scanf("%19s", comm);
      eat_buffer();

    if (strcmp(comm, "q") == 0) return 1;
    else if (strcmp(comm, "v") == 0) display_content(fetch_c);
    else if (strncmp(comm, "i=", 2) == 0) 
    {
      char *loc_comm = comm;
      loc_comm++; loc_comm++;
      int f_int = atoi(loc_comm);
      edit_line(fetch_c, f_int);
    }
    else if (strcmp(comm, "i") == 0) printf("??: wrong usage of i, use i=<line> instead.\n");
    else printf("??: '%s' -> invalid, use [h] for help.\n", comm);
  }
  } 
  else 
  {
    printf("Not enough arguments!\n");
  }
  return 0;
}

void display_content(struct CompFile comp_f)
{
  for (int i=0; i < comp_f.len; i++)
  {
    char *curr_line = comp_f.contents[i];
    printf("%d. %s", i + 1, curr_line);
  }
}

void clear_term() 
{
#ifdef _WIN32
  system("cls");
#else 
  system("clear");
#endif
}


struct CompFile fetch_file(char *path) 
{
  FILE *fptr;
  char **contents = malloc(1024 * sizeof(char *)); char buf[1024];
  fptr = fopen(path, "r");

  int count_ln = 0;
  while (fgets(buf, sizeof(buf), fptr) != NULL) 
  {
    contents[count_ln] = strdup(buf);
    count_ln += 1;
  }
  fclose(fptr);


  struct CompFile comp_f;
  comp_f.contents = contents;
  comp_f.len = count_ln;

  return comp_f;
}


void edit_line(struct CompFile comp_f, int curr_line)
{
  char buf[1024];
  printf("> "); fgets(buf, 1024, stdin);
  printf("%s", buf);
  
}


void eat_buffer()
{
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF);
}
