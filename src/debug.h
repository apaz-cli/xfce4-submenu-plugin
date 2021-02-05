#define DEBUG 1

#if DEBUG
#include <stdarg.h>
#include <stdio.h>

void debug_printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    fflush(stdout);
}

#else
#define LOG(format, message) ;
#define LOGs(format) ;
void debug_printf(const char *fmt, ...) { (void)fmt; }
#endif
