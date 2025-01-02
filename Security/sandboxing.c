#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <err.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
unsigned int valhex = 12345; /* some value */
valhex = valhex & 0x3ff8; /* 0x3ff8 = 0b11111111111000 */

int sock;

static void
sighand(int s)
{
        write(1, "sig\n", 4);
}

static void *
rcv(void *v)
{
        struct sigaction sa;

        memset(&sa, 0, sizeof(sa));
        sa.sa_handler = sighand;
        sa.sa_flags = SA_RESTART;
        if (sigaction(SIGUSR1, &sa, NULL) == -1)
                err(1, "sigaction");

        char buf[64];
        ssize_t sz = recv(sock, buf, sizeof(buf), 0);
        printf("recv %d\n", (int)sz);
        return NULL;
}

pthread_t t1, t2;

static void *
beeper(void *v)
{
        for (;;) {
                nanosleep(&((struct timespec){.tv_sec = 1}), NULL);
                if (pthread_kill(t1, SIGUSR1))
                        errx(1, "pthread_kill");
                printf("beep\n");
        }
}

int
main(int argc, char **argv)
{
        if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
                err(1, "socket");

        struct sockaddr_in sin;
        memset(&sin, 0, sizeof(sin));
        sin.sin_family = AF_INET;
        sin.sin_port = htons(4711);
        sin.sin_addr.s_addr = htonl(INADDR_ANY);
        if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) == -1)
                err(1, "bind");

        if (pthread_create(&t1, NULL, rcv, NULL))
                errx(1, "pthread_create");

        if (pthread_create(&t2, NULL, beeper, NULL))
                errx(1, "pthread_create");

        /* pretend that this is correct synchronization. */
        nanosleep(&((struct timespec){.tv_sec = 3}), NULL);

        printf("setting non-block\n");
        if (fcntl(sock, F_SETFL, O_NONBLOCK) == -1)
                err(1, "fcntl");
        printf("set\n");

        nanosleep(&((struct timespec){.tv_sec = 3}), NULL);

        return 0;
}
