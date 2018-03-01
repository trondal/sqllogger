#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <regex.h>

int params_are_ok(int argc);
int file_is_readable(char* filename);
void do_line_thingy(char* line, regex_t reg);
char* substring(const char* str, size_t begin, size_t len);
void strip(char* str);

int main(int argc, char* argv[]) {

    int params_result = params_are_ok(argc);
    if (params_result != EXIT_SUCCESS){
        printf("Error: %s\n", strerror(params_result));
        return EXIT_FAILURE;
    }

    //TODO only need to check if file exists, access rights via stdin and sudo.
    /*if (file_is_readable(argv[1]) != EXIT_SUCCESS) {
        perror("Error");
        return EXIT_FAILURE;
    }*/
    
    /* 
     * Use Posix extended regex, not PCRE. This is because I the program to be built 
     * on any Mac via homebrew as an exercise, and not have any external dependencies.
     */
    char* pattern = "(^[[:digit:]]{6}"
                    "[[:space:]]"
                    "[[:digit:]]+:[[:digit:]]+:[[:digit:]]+"
                    "[[:space:]]+"
                    "[[:digit:]]+"
                    "[[:space:]]+"
                    "(QUERY|EXECUTE)"
                    "[[:space:]]+"
                    "(SELECT|UPDATE|INSERT|DELETE)"
                    "(.*)"
                    ")|("
                    "^[[:space:]]+"
                     "[[:digit:]]+"
                     "[[:space:]]+"
                     "(QUERY|EXECUTE)"
                     "[[:space:]]+"
                     "(SELECT|UPDATE|INSERT|DELETE)"
                     "(.*))";
    regex_t reg;
    int comp = regcomp(
        &reg,
        pattern, 
        REG_ICASE | REG_EXTENDED
    );
    if (comp != 0) {
        fprintf(stderr, "Could not compile regex: code %d\n", comp);
        exit(1);
    }

    // read continously from stdin
    char *line = NULL;
    while (1) {
        size_t size;
        if (getline(&line, &size, stdin) != -1) {

            strip(line);
            
            do_line_thingy(line, reg);
        }
    }
}

void do_line_thingy(char* line, regex_t reg) {
    //strip(line);
    regmatch_t match[4];
    int res = regexec(&reg,
        line, // line to match
        4, // size of captures
        match,
        0
    );
    if (res == 0) {
        char* command = NULL;
        char* verb = NULL;
        char* sql = substring(line, match[0].rm_so, match[0].rm_eo - match[0].rm_so);
        printf("%s\n", sql);

    } else if (res == REG_NOMATCH) {
        // try for query without timestamp
    }
}


int params_are_ok(argc) {
    // do more checking here
    if (argc > 2) {
        return EINVAL;    
    }
    return EXIT_SUCCESS;
}

int file_is_readable(char* filename) {

    struct stat *statbuf;
    errno = 0;
    statbuf = malloc(sizeof(struct stat));    
    int exists = stat(filename, statbuf);
    free(statbuf);

    if (exists != 0) {
        return errno;
    }
    return EXIT_SUCCESS;
}

char* substring(const char* str, size_t begin, size_t len) { 
  if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
    return 0; 

  return strndup(str + begin, len); 
}

/* 
 * Unless we strip the newline from each line, the output will contain this as well,
 * and show a newline between each line, something I do not want.
 */
void strip(char* str) {
    int len;
    if (str == NULL) {
        return;
    }
    len = strlen(str);
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
    len = strlen(str);
    if (str[len - 1] == '\r') {
        str[len - 1] = '\0';
    }
}