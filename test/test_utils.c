#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

clock_t base;

static void
start_time() {
	base = clock();
}

static void
log_time(const char *msg, ...) {
	clock_t elapsed = clock() - base;
	va_list list;
	va_start(list, msg);
	vprintf(msg, list);
	printf(" in %d milliseconds.\n", elapsed * 1000 / CLOCKS_PER_SEC);
}