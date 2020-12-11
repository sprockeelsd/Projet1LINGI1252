#include "lib_tar.h"

/**
 * Checks whether the archive is valid.
 *
 * Each non-null header of a valid archive has:
 *  - a magic value of "ustar" and a null,
 *  - a version value of "00" and no null,
 *  - a correct checksum
 *
 * @param tar_fd A file descriptor pointing to the start of a file supposed to contain a tar archive.
 *
 * @return a zero or positive value if the archive is valid, representing the number of headers in the archive,
 *         -1 if the archive contains a header with an invalid magic value,
 *         -2 if the archive contains a header with an invalid version value,
 *         -3 if the archive contains a header with an invalid checksum value
 */
int check_archive(int tar_fd) {
    //on sait qu'on est dans un header
	void* readd = malloc(sizeof(tar_header_t));
	//lire le header
	int reading = read(tar_fd,readd,sizeof(tar_header_t));
	if(reading == -1){
		free(readd);
		return 0;
	}
	//cast le header lu en la structure de données
	tar_header_t* header = ((tar_header_t*)readd);
	//printer(header);
	
	if(strcmp(header->magic,TMAGIC)){
		free(readd);
		return -1;
	}if(*(char*)header->version!=48 || *(char*)(header->version+1)!=48){
		free(readd);
		return -2;
	}
	
	//vérifier la checksum
	long int x = TAR_INT(header->chksum);
	strncpy(header->chksum, "        ", 8); //8e bit est un espace et non \0
	char* iter = (char*)header;
	long int checksum = 0;
	for(int i = 0; i < 512; i++) checksum += *(iter+i);
	
	if(checksum != x){
		free(readd);
		return -3;
	}
	//si le header est correct
	if(is_dir(tar_fd, header->name) != 0) return 1 + check_archive(tar_fd);
	
	else if(is_symlink(tar_fd, header->name) != 0) return 1 + check_archive(tar_fd);
	
	else if(is_file(tar_fd, header->name) != 0){
		if(header->size == 0) return 1 + check_archive(tar_fd);
		
		else{
			int nOfBlocksToSkip = (atoi(header->size) / 512)+1;
			size_t *nBlocks;
			*nBlocks = nOfBlocksToSkip*512*sizeof(uint8_t); 
			uint8_t* file = malloc(nOfBlocksToSkip * 512 * sizeof(uint8_t));
			ssize_t readfile = read_file(tar_fd, header->name, 0, file, nBlocks);
			return 1 + check_archive(tar_fd);
			if(readfile == -1){
				printf("reading ERROR \n");
				free(file);
				return EXIT_FAILURE;
			}
			free(file);			
		}
	}
	return 0;
}
}

/**
 * Checks whether an entry exists in the archive.
 *
 * @param tar_fd A file descriptor pointing to the start of a tar archive file.
 * @param path A path to an entry in the archive.
 *
 * @return zero if no entry at the given path exists in the archive,
 *         any other value otherwise.
 */
int exists(int tar_fd, char *path) {
    return 0;
}

/**
 * Checks whether an entry exists in the archive and is a directory.
 *
 * @param tar_fd A file descriptor pointing to the start of a tar archive file.
 * @param path A path to an entry in the archive.
 *
 * @return zero if no entry at the given path exists in the archive or the entry is not a directory,
 *         any other value otherwise.
 */
int is_dir(int tar_fd, char *path) {
    return 0;
}

/**
 * Checks whether an entry exists in the archive and is a file.
 *
 * @param tar_fd A file descriptor pointing to the start of a tar archive file.
 * @param path A path to an entry in the archive.
 *
 * @return zero if no entry at the given path exists in the archive or the entry is not a file,
 *         any other value otherwise.
 */
int is_file(int tar_fd, char *path) {
    return 0;
}

/**
 * Checks whether an entry exists in the archive and is a symlink.
 *
 * @param tar_fd A file descriptor pointing to the start of a tar archive file.
 * @param path A path to an entry in the archive.
 * @return zero if no entry at the given path exists in the archive or the entry is not symlink,
 *         any other value otherwise.
 */
int is_symlink(int tar_fd, char *path) {
    return 0;
}


/**
 * Lists the entries at a given path in the archive.
 *
 * @param tar_fd A file descriptor pointing to the start of a tar archive file.
 * @param path A path to an entry in the archive. If the entry is a symlink, it must be resolved to its linked-to entry.
 * @param entries An array of char arrays, each one is long enough to contain a tar entry
 * @param no_entries An in-out argument.
 *                   The caller set it to the number of entry in entries.
 *                   The callee set it to the number of entry listed.
 *
 * @return zero if no directory at the given path exists in the archive,
 *         any other value otherwise.
 */
int list(int tar_fd, char *path, char **entries, size_t *no_entries) {
    return 0;
}

/**
 * Reads a file at a given path in the archive.
 *
 * @param tar_fd A file descriptor pointing to the start of a tar archive file.
 * @param path A path to an entry in the archive to read from.  If the entry is a symlink, it must be resolved to its linked-to entry.
 * @param offset An offset in the file from which to start reading from, zero indicates the start of the file.
 * @param dest A destination buffer to read the given file into.
 * @param len An in-out argument.
 *            The caller set it to the size of dest.
 *            The callee set it to the number of bytes written to dest.
 *
 * @return -1 if no entry at the given path exists in the archive or the entry is not a file,
 *         -2 if the offset is outside the file total length,
 *         zero if the file was read in its entirety into the destination buffer,
 *         a positive value if the file was partially read, representing the remaining bytes left to be read.
 *
 */
ssize_t read_file(int tar_fd, char *path, size_t offset, uint8_t *dest, size_t *len) {
    return 0;
}

void printer(tar_header_t* header){
	printf("name = %s \n",header->name);
	printf("mode = %s \n",header->mode);
	printf("uid = %s \n",header->uid);
	printf("gid = %s \n",header->gid);
	printf("size = %s \n",header->size);
	printf("mtime = %s \n",header->mtime);
	printf("chksum = %ld \n",TAR_INT(header->chksum));
	printf("typeflag = %c \n",header->typeflag);
	printf("linkname = %s \n",header->linkname);
	printf("magic = %s \n",header->magic);
	printf("version1 = %d \n",*(char*)header->version);
	printf("version2 = %d \n",*(char*)(header->version+1));
	printf("uname = %s \n",header->uname);
	printf("gname = %s \n",header->gname);
	printf("devmajor = %s \n",header->devmajor);
	printf("devminor = %s \n",header->devminor);
	printf("prefix = %s \n",header->prefix);
	printf("padding = %s \n",header->padding);
}
