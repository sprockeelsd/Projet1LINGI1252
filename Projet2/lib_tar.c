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
	int magicnumberofheaders = 0;
	void* readd = malloc(sizeof(tar_header_t));
	int reading = read(tar_fd,readd,sizeof(tar_header_t)); //lire le header
	if(reading == -1){
		free(readd);
		return -4;
	}
	tar_header_t* header = ((tar_header_t*)readd); //cast le header lu en la structure de données
	while(strcmp(header->name,"\0")){
		if(strcmp(header->magic,TMAGIC)){
			free(readd);
			return -1;
		}if(*(char*)header->version!=48 || *(char*)(header->version+1)!=48){
			free(readd);
			return -2;
		}
		long int x = TAR_INT(header->chksum);
		memset(header->chksum, 040, 8);
		char* iter = (char*)header;
		long int checksum = 0;
		for(int i = 0; i < 512; i++) checksum += *(iter+i);
		
		if(checksum != x){ //vérifier la checksum
			free(readd);
			return -3;
		}
		if(!TAR_INT(header->size)) magicnumberofheaders++;
		else{
			int nOfBlocksToSkip = (TAR_INT(header->size) / 512)+1;
			size_t nBlocks = nOfBlocksToSkip*512*sizeof(char);
			char* file = malloc(nBlocks);
			reading = read(tar_fd,file,nBlocks);
			if(reading == -1){
				free(file);
				free(readd);
				return -4;
			}
			free(file);
			magicnumberofheaders++;
		}
		reading = read(tar_fd,readd,sizeof(tar_header_t)); //lire le header suivant
		if(reading == -1){
			free(readd);
			return -4;
		}
		header = ((tar_header_t*)readd);
	}
	return magicnumberofheaders;
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
	if(find(tar_fd,path)==NULL) return 0;
	return 1;
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
	if(find(tar_fd,path)==NULL) return 0;
	tar_header_t* header = find(tar_fd, path);
	if(!strcmp(header->name,path)){
		if(!TAR_INT(header->size) && !TAR_INT(header->linkname)) return 1;
		else return 0;
	}
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
	if(find(tar_fd,path)==NULL) return 0;
	tar_header_t* header = find(tar_fd, path);
	if(!strcmp(header->name,path)){
		if(TAR_INT(header->size)>0 && !strcmp(header->linkname,"\0")) return 1;
		else return 0;
	}
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
        if(find(tar_fd,path)==NULL) return 0;
	tar_header_t* header = find(tar_fd, path);
	if(!strcmp(header->name,path)){
		if(!TAR_INT(header->size) && strcmp(header->linkname,"\0")) return 1;
			else return 0;
	}
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
	if(find(tar_fd,path)==NULL) return 0;
	tar_header_t* header = find(tar_fd, path);
	while(is_symlink(tar_fd,header->name)) header = find(tar_fd, header->linkname);
	if(!is_dir(tar_fd, path)) return 0;
	//enumerer les entrées
	return 1;
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
	if(find(tar_fd,path)==NULL) return 0;
	tar_header_t* header = find(tar_fd, path);
	if(!strcmp(header->name,path)){
		if(TAR_INT(header->size)>0 && !strcmp(header->linkname,"\0")) return 1;
		else return 0;
	}
	return 0;
}

void printer(tar_header_t* header){
	printf("name = %s \n",header->name);
	printf("mode = %s \n",header->mode);
	printf("uid = %s \n",header->uid);
	printf("gid = %s \n",header->gid);
	printf("size = %ld \n",TAR_INT(header->size));
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

tar_header_t* find(int tar_fd, char *path){
	//appel de check_archives?????
	void* readd = malloc(sizeof(tar_header_t));
	read(tar_fd,readd,sizeof(tar_header_t));
	tar_header_t* header = ((tar_header_t*)readd);
	while(strcmp(header->name,"\0")){
		printf("name = %s\n",header->name);
		if(!strcmp(header->name,path)) return header;
		if(TAR_INT(header->size) > 0){
			int nOfBlocksToSkip = (TAR_INT(header->size) / 512)+1;
			size_t nBlocks = nOfBlocksToSkip*512*sizeof(char);
			char* file = malloc(nBlocks);
			read(tar_fd,file,nBlocks);
			free(file);
		}
		read(tar_fd,readd,sizeof(tar_header_t));
		header = ((tar_header_t*)readd);
	}
	return NULL;
}
