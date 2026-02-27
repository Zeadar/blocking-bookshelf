#include "blocktimer.h"
#include <stdio.h>
#include <stdlib.h>

#define F_EXIT_MSG "%s exited abnormally (%d)...\n"

#ifdef DEBUGBUILD
void command_log_debug(const char *command, const int line,
                       const char *filename) {
    printf("[%s:%d] -- %s\n", filename, line, command);
    if (is_not_root)
        return;
    int ret = system(command);
    if (ret != 0) {
        fprintf(stderr, F_EXIT_MSG, command, ret);
        exit(ret);
    }
}
#else
void command_log_debug(const char *command) {
    if (is_not_root) {
        printf("%s\n", command);
        return;
    }
    int ret = system(command);
    if (ret != 0) {
        fprintf(stderr, F_EXIT_MSG, command, ret);
        exit(ret);
    }
}
#endif
