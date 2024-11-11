/*
 * open-read.c
 *
 * Simple example of opening and reading to a file.
 *
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    /*
     *
     * the attributes are:
     * - O_RDONLY: open the file for reading
     *
     */
    int fd = open("test.txt", O_RDONLY);

    if (fd < 0) {
        perror("open error");
        return EXIT_FAILURE;
    }

    char buffer[128];
    memset(buffer, 0, sizeof(buffer));

    /* read the contents of the file */
    int done = 0;
    while (done < sizeof(buffer) - 1) {
        int bytes_read = read(fd, buffer + done, sizeof(buffer) - 1 - done);
        if (bytes_read < 0) {
            perror("read error");
            return EXIT_FAILURE;
        }

        /* if we read 0 bytes, we're done */
        if (bytes_read == 0) {
            break;
        }

        /*
         * it might not have managed to read all data.
         * like on open-write, if you're curious, try to find out why, in this
         * case, the program will always be able to read it all.
         */
        done += bytes_read;
    }

    printf("%s", buffer);

    /* close the file */
    close(fd);

    return EXIT_SUCCESS;
}
