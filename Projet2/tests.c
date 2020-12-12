#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "lib_tar.h"
//tar --posix --pax-option delete=".*" --pax-option delete="*time*" --no-xattrs --no-acl --no-selinux -c fichier1 fichier2 ... >   archive.tar
/**
 * You are free to use this file to write tests for your implementation
 */

void debug_dump(const uint8_t *bytes, size_t len) {
    for (int i = 0; i < len;) {
        printf("%04x:  ", (int) i);

        for (int j = 0; j < 16 && i + j < len; j++) {
            printf("%02x ", bytes[i + j]);
        }
        printf("\t");
        for (int j = 0; j < 16 && i < len; j++, i++) {
            printf("%c ", bytes[i]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
	if (argc < 2) {
	printf("Usage: %s tar_file\n", argv[0]);
	return -1;
	}

	int fd = open(argv[1] , O_RDONLY);
	if (fd == -1) {
	perror("open(tar_file)");
	return -1;
	}

	//size_t offset = 0;
	uint8_t* dest = malloc(1000*sizeof(char*));
	size_t* len = malloc(sizeof(size_t));
	*len = 1000; 
	size_t* no_entries = malloc(sizeof(size_t));
	*no_entries = 10;
	char **entries = malloc(10*sizeof(char*));
	int ret;
	
	/*ret = check_archive(fd);
	printf("check_archive returned %d\n", ret);

	fd = open(argv[1] , O_RDONLY);
	ret = exists(fd, "skeleton/tests.c");
	printf("exists returned %d\n", ret);

	fd = open(argv[1] , O_RDONLY);
	ret = is_dir(fd, "skeleton/");
	printf("isDir returned %d\n", ret);

	fd = open(argv[1] , O_RDONLY);
	ret = is_file(fd, "skeleton/");
	printf("isFile returned %d\n", ret);

	fd = open(argv[1] , O_RDONLY);
	ret = is_symlink(fd, "skeleton/");
	printf("isSymlink returned %d\n", ret);

	fd = open(argv[1] , O_RDONLY);
	ret = read_file(fd, "Projet1LINGI1252/LINFO1252.pdf", offset, dest, len);
	printf("readFile returned %d\n", ret);*/

	fd = open(argv[1] , O_RDONLY);
	ret = list(fd, "Projet1LINGI1252/Projet2/", entries, no_entries);
	printf("list returned %d\n", ret);
	
	free(entries);
	free(no_entries);
	free(len);
	free(dest);
	return 0;
}
