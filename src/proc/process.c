#include "proc/process.h"

#include "apps/apps.h"

void program_init() {

}

struct program *program_search(const char *name, size_t length) {
    return NULL;
}

struct program helloworld_app = {
    .name="helloworld",
    .main=helloworld_main,
    .data=NULL,
    .data_size=0,
};
