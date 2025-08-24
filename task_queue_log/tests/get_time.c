#include <stdio.h>
#include <time.h>

void get_timestamp(char* buffer, size_t size) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

int main() {
    char ts[30];
    get_timestamp(ts, sizeof(ts));
    printf("Now: %s\n", ts);
    return 0;
}
