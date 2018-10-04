#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 64

void copy_file_with_comments(char source[], char destination[]);
void copy_file_without_comments(char source[], char destination[]);

int main() {
  char source[BUFFER_SIZE];

  printf("Source filename: ");
  fgets(source, BUFFER_SIZE, stdin);
  // Remove the newline from the end of char[] by setting it to empty; ''
  source[strlen(source)-1] = '\0';
  
  copy_file_with_comments(source, "with_comments.c");
  copy_file_without_comments(source, "without_comments.c");
}

void copy_file_with_comments(char source[], char destination[]) {
  char character;
  remove(destination);

  FILE *old_file = fopen(source, "r");
  FILE *new_file = fopen(destination, "w+");
  
  while((character = fgetc(old_file)) != EOF)
    fputc(character, new_file);

  fclose(old_file);
  fclose(new_file);
}

void copy_file_without_comments(char source[], char destination[]) {
  char character;
  remove(destination);

  FILE *old_file = fopen(source, "r");
  FILE *new_file = fopen(destination, "w+");
  enum BOOLEAN {false, true};
  enum BOOLEAN is_comment = false;

  while((character = fgetc(old_file)) != EOF) {
    switch(is_comment) {
    case false:
      if(character == '/')
        is_comment = true;
      else
        fputc(character, new_file);
      break;
    case true:
      if(character == '/')
        is_comment = false;
      break;
    }
  }

  fclose(old_file);
  fclose(new_file);
}
