#include "render.h"

void __Init() {
    setlocale(LC_ALL, "en_US.UTF-8");

    viewport.clock = clock();

    viewport.viewport_size.x = 0;
    viewport.viewport_size.y = 0;

    viewport.viewport_buffer = malloc(200*200);
}

unsigned int iter = 0;
void __Update(double delta, void (*update_function)(double delta)) {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &viewport.viewport_size);
    int status;
    if (fork() == 0) {
        char* arguments[2] = { "clear", NULL };
        status = execvp("clear", arguments);
    }
	wait(&status);
    update_function(delta);

    viewport.viewport_buffer[viewport.viewport_size.x * viewport.viewport_size.y + 1] = 0x00;

    printf("%f - %d : %dx%d\n", delta, iter, viewport.viewport_size.x, viewport.viewport_size.y);
    printf("%ls\n", viewport.viewport_buffer);
    iter++;


    viewport.clock = clock();
}

struct __Viewport viewport = {
    .Init = __Init,
    .Update = __Update
};