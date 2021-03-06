#include "test_workers.h"
#include "awesome_farm.h"
#include <stdio.h>
#include <string.h>

int main() {
    AF_ACTIVATE_WORKERS(worker_1,worker_2)

    af_client_result_t *result = af_init("localhost", 6379);
    if (result->status == AF_CLIENT_ERROR) {
        printf("Error: %s\n", result->msg);
        free(result);
        return 1;
    }
    free(result);

    char str[255];
    for (int i = 1; i < 100; i++) {
        sprintf(str, "Hello %i", i);
        AF_SCHEDULE(worker_1, result, str, i);
        AF_SCHEDULE(worker_2, result, i, i * 3);
    }

    af_cleanup();
}
