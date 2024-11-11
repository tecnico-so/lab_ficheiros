/*
 * open-write.c
 *
 * Simple example of opening and writing to a file.
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
    /**
     * the attributes are:
     * - O_CREAT: create the file if it does not exist
     * - O_TRUNC: erase the contents of the file
     * - O_WRONLY: open the file for writing
     *
     * the permissions are applied if the file is created:
     * - S_IRUSR: reading, user
     * - S_IWUSR: writing, user
     *
     * both the attributes and permissions are bitmasks, "clumped together"
     * using bitwise ORs
     */
    int fd = open("test.txt", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        perror("open error");
        return EXIT_FAILURE;
    }

    char buffer[] = "Hello World!\n";

    /* write a string to the file */
    int len = strlen(buffer);
    int done = 0;
    while (len > done) {
        int bytes_written = write(fd, buffer + done, len - done);

        if (bytes_written < 0) {
            perror("write error");
            return EXIT_FAILURE;
        }

        /*
         * it might not have managed to write all data.
         * if you're curious, try to find out why, in this case, the program
         * will always be able to write it all.
         */
        done += bytes_written;
    }

    /* close the file */
    close(fd);
    return EXIT_SUCCESS;
}
