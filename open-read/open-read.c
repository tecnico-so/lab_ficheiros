/*
 * open-read.c
 *
 * Simple example of opening and reading to a file.
 *
 */

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char *argv[])
{
   /*
    *
    * the attributes are:
    * - O_RDONLY: open the file for reading
    *
    */
   int fd = open("test.txt", O_RDONLY);
   if (fd < 0){
      fprintf(stderr, "open error: %s\n", strerror(errno));
      return -1;
   }

   char buffer[128];
   memset(buffer,0,sizeof(buffer));

   /* read the contents of the file */
   int bytes_read = read(fd, buffer, sizeof(buffer));
   if (bytes_read < 0){
      fprintf(stderr, "read error: %s\n", strerror(errno));
      return -1;
   }

   printf("%s",buffer);

   /* close the file */
   close(fd);

   return 0;
}
