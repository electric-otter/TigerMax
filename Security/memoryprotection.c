    #include <stdio.h>
    #include <unistd.h>
    #include <malloc.h>
    #include <sys/mman.h>

    int main() {
        size_t pagesize = sysconf(_SC_PAGESIZE);

        printf("pagesize...........: %lu\n", pagesize);

        char* m;
        size_t len = 12345;
        len = (len + pagesize - 1) / pagesize * pagesize;
        posix_memalign(&m, pagesize, len);

        printf("page aligned memory: %lx - %lx\n", (unsigned long) m, (unsigned long) m + len);

        printf("protecting 0 till m..."); fflush(stdout);
        mprotect(0, (size_t) m, PROT_NONE);
        printf("done\n");

        printf("protecting (m + len) till ?..."); fflush(stdout);
        mprotect(m + len, 0x7fffffff, PROT_NONE);
        printf("done\n");

        printf("trying to modify memory..."); fflush(stdout);
        *(m - 1000) = 5;
        printf("done: %i\n", *(m - 1000));

        free(m);
    }
