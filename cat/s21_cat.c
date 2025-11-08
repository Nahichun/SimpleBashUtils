#include "s21_cat.h"

int main(int argc, char **argv) {
  if (argc == 1) {
    process_file(NULL, stdin, "stdin");
    return 0;
  }
  char *flag = NULL;
  int file_count = 0;

  for (int i = 1; i < argc; i++) {
    if (is_flag(argv[i])) {
      if (flag == NULL) {
        flag = argv[i];
      } else {
        fprintf(stderr, "cat: multiple flags not supported\n");
        return 1;
      }
    } else {
      file_count++;
    }
  }

  if (file_count == 0) {
    process_file(flag, stdin, "stdin");
  } else {
    for (int i = 1; i < argc; i++) {
      if (is_flag(argv[i])) {
        continue;
      }

      if (strcmp(argv[i], "-") == 0) {
        process_file(flag, stdin, "stdin");
      } else {
        FILE *file = fopen(argv[i], "rb");
        if (file == NULL) {
          fprintf(stderr, "cat: %s: %s\n", argv[i], strerror(errno));
          continue;
        }
        process_file(flag, file, argv[i]);
        fclose(file);
      }
    }
  }

  if (fflush(stdout) == EOF) {
    perror("cat: write error");
    return 1;
  }

  return 0;
}

int is_flag(const char *s) {
  if (s == NULL || strlen(s) < 2) return 0;
  return (s[0] == '-');
}

int is_blank_line(const char *str) {
  if (str == NULL) return 1;

  for (; *str != '\0'; str++) {
    if (!isspace((unsigned char)*str) && *str != '\n' && *str != '\r') return 0;
  }
  return 1;
}

void process_file(const char *flag, FILE *f, const char *filename) {
  if (f == NULL) {
    fprintf(stderr, "cat: %s: invalid file pointer\n", filename);
    return;
  }

  if (flag == NULL) {
    handle_regular(f);
  } else if (strcmp(flag, "-b") == 0 ||
             strcmp(flag, "--number-nonblank") == 0) {
    handle_b_flag(f);
  } else if (strcmp(flag, "-n") == 0 || strcmp(flag, "--number") == 0) {
    handle_n_flag(f);
  } else if (strcmp(flag, "-e") == 0) {
    handle_e_flag(f);
  } else if (strcmp(flag, "-E") == 0 || strcmp(flag, "--show-ends") == 0) {
    handle_E_flag(f);
  } else if (strcmp(flag, "-t") == 0) {
    handle_t_flag(f);
  } else if (strcmp(flag, "-T") == 0 || strcmp(flag, "--show-tabs") == 0) {
    handle_T_flag(f);
  } else if (strcmp(flag, "-s") == 0 || strcmp(flag, "--squeeze-blank") == 0) {
    handle_s_flag(f);
  } else {
    fprintf(stderr, "cat: invalid option -- '%s'\n", flag);
    handle_regular(f);
  }
}

void handle_regular(FILE *f) {
  char buffer[BUFFER_SIZE];
  size_t bytes_read;

  while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, f)) > 0) {
    if (fwrite(buffer, 1, bytes_read, stdout) != bytes_read) {
      perror("cat: write error");
      break;
    }
  }

  if (ferror(f)) {
    perror("cat: read error");
  }
}

void handle_b_flag(FILE *f) {
  int line_number = 1;
  bool in_line = false;
  int c;

  while ((c = fgetc(f)) != EOF) {
    if (!in_line) {
      if (c != '\n') {
        printf("%6d\t", line_number++);
        in_line = true;
      }
    }

    putchar(c);

    if (c == '\n') {
      in_line = false;
    }
  }

  if (ferror(f)) {
    perror("cat: read error");
  }
}

void handle_n_flag(FILE *f) {
  int line_number = 1;
  bool at_line_start = true;
  int c;

  while ((c = fgetc(f)) != EOF) {
    if (at_line_start) {
      printf("%6d\t", line_number++);
      at_line_start = false;
    }

    putchar(c);

    if (c == '\n') {
      at_line_start = true;
    }
  }

  if (ferror(f)) {
    perror("cat: read error");
  }
}

void handle_E_flag(FILE *f) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (c == '\n') {
      printf("$\n");
    } else {
      putchar(c);
    }
  }

  if (ferror(f)) {
    perror("cat: read error");
  }
}

void handle_e_flag(FILE *f) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    unsigned char uc = (unsigned char)c;

    if (uc == '\n') {
      printf("$\n");
    } else if (uc == '\t') {
      putchar('\t');
    } else if (uc < 32 || uc >= 127) {
      show_non_printable(uc);
    } else {
      putchar(uc);
    }
  }

  if (ferror(f)) {
    perror("cat: read error");
  }
}

void handle_T_flag(FILE *f) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (c == '\t') {
      printf("^I");
    } else {
      putchar(c);
    }
  }

  if (ferror(f)) {
    perror("cat: read error");
  }
}

void handle_t_flag(FILE *f) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    unsigned char uc = (unsigned char)c;

    if (uc == '\t') {
      printf("^I");
    } else if (uc == '\n') {
      putchar('\n');
    } else if (uc < 32 || uc >= 127) {
      show_non_printable(uc);
    } else {
      putchar(uc);
    }
  }

  if (ferror(f)) {
    perror("cat: read error");
  }
}

void handle_s_flag(FILE *f) {
  int c;
  bool last_was_blank = false;
  bool in_blank_line = false;

  while ((c = fgetc(f)) != EOF) {
    if (c == '\n') {
      if (!in_blank_line) {
        in_blank_line = true;
        putchar(c);
      } else {
        if (!last_was_blank) {
          putchar(c);
          last_was_blank = true;
        }
      }
    } else {
      in_blank_line = false;
      last_was_blank = false;
      putchar(c);
    }
  }

  if (ferror(f)) {
    perror("cat: read error");
  }
}

void show_non_printable(unsigned char c) {
  if (c == 127) {  // DEL
    printf("^?");
  } else if (c < 32) {  // Control characters
    printf("^%c", c + 64);
  } else if (c >= 128 && c < 128 + 32) {  // Meta + control
    printf("M-^%c", c - 128 + 64);
  } else if (c >= 128) {  // Meta characters
    printf("M-%c", c - 128);
  } else {
    putchar(c);  // Should not happen
  }
}
