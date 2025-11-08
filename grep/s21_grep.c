#include "s21_grep.h"

int main(int argc, char* argv[]) {
  char pattern_buffer[4096] = {0};
  int e_flag = 0;
  int i_flag = 0;
  int v_flag = 0;
  int c_flag = 0;
  int l_flag = 0;
  int n_flag = 0;

  if (parse_flags(argc, argv, pattern_buffer, &e_flag, &i_flag, &v_flag,
                  &c_flag, &l_flag, &n_flag)) {
    process_files(argc, argv, pattern_buffer, e_flag, i_flag, v_flag, c_flag,
                  l_flag, n_flag);
  }

  return 0;
}

int parse_flags(int argc, char* argv[], char* pattern_buffer, int* e_flag,
                int* i_flag, int* v_flag, int* c_flag, int* l_flag,
                int* n_flag) {
  const char* options = "e:ivcln";
  int pattern_count = 0;
  int option;

  while ((option = getopt(argc, argv, options)) != -1) {
    if (option == 'e') {
      *e_flag = 1;
      if (pattern_count > 0) {
        strcat(pattern_buffer, "|");
      }
      pattern_count++;
      strcat(pattern_buffer, optarg);
    } else if (option == 'i') {
      *i_flag = 1;
    } else if (option == 'v') {
      *v_flag = 1;
    } else if (option == 'c') {
      *c_flag = 1;
    } else if (option == 'l') {
      *l_flag = 1;
    } else if (option == 'n') {
      *n_flag = 1;
    } else {
      fprintf(stderr, "Invalid option\n");
      return 0;
    }
  }
  return 1;
}

void process_files(int argc, char* argv[], const char* pattern, int e_flag,
                   int i_flag, int v_flag, int c_flag, int l_flag, int n_flag) {
  regex_t regex;
  int regex_options = REG_EXTENDED;
  const char* search_pattern = pattern;

  if (i_flag) {
    regex_options |= REG_ICASE;
  }

  if (!e_flag) {
    search_pattern = argv[optind++];
  }

  char buffer[4096];
  int total_files_matched = 0;

  for (int i = optind; i < argc; i++) {
    int matched_lines = 0;
    int total_lines = 0;
    int regex_result;

    FILE* file = fopen(argv[i], "r");
    if (!file) {
      fprintf(stderr, "Cannot open file: %s\n", argv[i]);
      continue;
    }

    regcomp(&regex, search_pattern, regex_options);

    while (fgets(buffer, sizeof(buffer), file)) {
      total_lines++;
      regex_result = regexec(&regex, buffer, 0, NULL, 0);
      int is_match = (regex_result == 0);

      if (v_flag) {
        is_match = !is_match;
      }

      if (is_match) {
        matched_lines++;
        total_files_matched++;

        if (l_flag) {
          break;
        }

        if (!c_flag) {
          if (argc - optind > 1) {
            printf("%s:", argv[i]);
          }
          if (n_flag) {
            printf("%d:", total_lines);
          }
          printf("%s", buffer);
        }
      }
    }

    fclose(file);
    regfree(&regex);

    if (l_flag && matched_lines > 0) {
      printf("%s\n", argv[i]);
    } else if (c_flag) {
      if (argc - optind > 1) {
        printf("%s:", argv[i]);
      }
      int result_count = v_flag ? (total_lines - matched_lines) : matched_lines;
      printf("%d\n", result_count);
    }
  }
}