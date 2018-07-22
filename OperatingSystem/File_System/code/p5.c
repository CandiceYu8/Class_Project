#include "p5.h"
#include <stdio.h>
#include <string.h>

/* check to see if the device already has a file system on it,
 * and if not, create one. */
void my_mkfs()
{
	/* initialize superblock and write to disc_block 0*/
	struct SuperBlock superblock;
    superblock.built_fs = 1;
    superblock.inode_sum = INODE_MAX;
    superblock.inode_bitmap = 1;
    superblock.inode_bp_addr = 1;
    superblock.inode_start_addr = INODE_START;
    superblock.inode_free = 1;		// 0:root_dir
    superblock.file_max = MAX_FILE_LENGTH;
    superblock.block_size = 1024;
    superblock.block_sum = BLOCK_MAX;
    superblock.block_bitmap = 32;
    superblock.block_bp_addr = 2;	// 0:superblock; 1:inode_map
    superblock.block_free = BITMAP_OFFSET + 1;
	superblock.block_free_size = BLOCK_MAX - BITMAP_OFFSET - 1;		// unit: KB
    superblock.root_dir = BITMAP_OFFSET;

	memset(open_fd, 0, sizeof(open_fd));
	char buff[BLOCKSIZE];
	int dev = dev_open();
	if (dev > 0){
		read_block(0, buff);
		struct SuperBlock *read_spb = buff;
		if (read_spb->built_fs != 1){	// file system doesn't exist
			// initiate superblock
			write_block(0, (char *)&superblock);

			// free block management bitmap initialize
			Init_bitmap(superblock.block_bp_addr, superblock.block_bitmap, superblock.block_bp_addr);
			Set_bitmap(0, superblock.block_bp_addr);

			// i-node management bitmap initialize
			Init_bitmap(superblock.inode_bp_addr, superblock.inode_bitmap, superblock.block_bp_addr);
			
			// i-node struct initialize
			Init_inode(INODE_START, INODE_MAX/INODE_PER_BLOCK, superblock.block_bp_addr);

			// root directory initialize
			Init_rootDir(superblock.root_dir, superblock.block_bp_addr);

			printf("file system initialize successfully!\n");
		}
		else{
			printf("file system already exist.\n");
		}
	}
}


/* only works if all but the last component of the path already exists */
/* return -1 when cannot make the directory, otherwise 0. */
int my_mkdir(char *path)
{
	int i=0;
	char sub_path[10][60];
	int path_level = Split_path(path, sub_path);
	int par_dir_block = BITMAP_OFFSET;

	for(i=0; i<path_level-1; i++){
		// didn't find the previous directory
		par_dir_block = Find_dir_block(sub_path[i], par_dir_block);
		if(par_dir_block == -1)
			return -1; 
	}

	// test whether the directory to make is already exist
	int exist_ = Find_dir_block(sub_path[i], par_dir_block);
	if(exist_ > 0)
		return -1;

	Add_dir(sub_path[i], par_dir_block);
	return 0;
}


/* return -1 when cannot remove the directory, otherwise 0. */
int my_rmdir(char *path)
{
	int i=0;
	char sub_path[10][60];
	int path_level = Split_path(path, sub_path);
	int par_dir_block = BITMAP_OFFSET;

	for(i=0; i<path_level-1; i++){
		// didn't find the previous directory
		par_dir_block = Find_dir_block(sub_path[i], par_dir_block);
		if(par_dir_block == -1)
			return -1; 
	}

	// test whether the directory to remove is already exist
	int exist_ = Find_dir_block(sub_path[i], par_dir_block);
	if(exist_ < 0)
		return -1;

	// the directory exist and exist_ is its block number in disc
	Rm_dir(sub_path[i], par_dir_block, exist_);
	return 0;
}


/* open an exisiting file for reading or writing
   return fd which is its inode */
int my_open(char *path)
{
	int i=0;
	char sub_path[10][60];
	int path_level = Split_path(path, sub_path);
	int par_dir_block = BITMAP_OFFSET;

	for(i=0; i<path_level-1; i++){
		// didn't find the previous path
		par_dir_block = Find_dir_block(sub_path[i], par_dir_block);
		if(par_dir_block == -1)
			return -1; 
	}

	// exist_:-1 the file doesn't exist; otherwise: it is its inode number
	int exist_ = Find_dir_inode(sub_path[i], par_dir_block);
	if(exist_){
		Fd_inode = exist_;
		Fd_index = 0;
		Fd_offset = 0;
		for(i=0; i<MAX_OPEN_FILES; i++){
			if(open_fd[i] == 0){
				open_fd[i] = exist_;
				break;
			}
		}
	}
	return exist_;
}


/* open a new file for writing only */
int my_creat(char *path)
{
	int i=0;
	char sub_path[10][60];
	int path_level = Split_path(path, sub_path);
	int par_dir_block = BITMAP_OFFSET;

	for(i=0; i<path_level-1; i++){
		// didn't find the previous path
		par_dir_block = Find_dir_block(sub_path[i], par_dir_block);
		if(par_dir_block == -1)
			return -1; 
	}
	
	// test whether the file already exist
	int exist_ = Find_dir_block(sub_path[i], par_dir_block);
	if(exist_ > 0)
		return -1;
	
	// printf("my_creat: par_dir_block %d sub_path %s\n", par_dir_block, sub_path[i]);
	int inode_ = Add_file(sub_path[i], par_dir_block);
	Fd_inode = inode_;
	Fd_index = 0;
	Fd_offset = 0;
	for(i=0; i<MAX_OPEN_FILES; i++){
		if(open_fd[i] == 0){
			open_fd[i] = inode_;
			break;
		}
	}
	return inode_;
}


/* sequentially read from a file 
   fd: the inode of the file 
   buf: char buf[count] is the content to write to disc 
   count: the size of the file, in Byte 
   return: -1: failed, count: succeed */
int my_read(int fd, void *buf, int count)
{
	int i;
	int result = 0;
	char * tmp = buf;
	int sizet = count;
	// test whether the fd exist
	if(Fd_inode != fd)
		return -1;
	char read_unit[BLOCKSIZE];
	Read_all_blocks(fd);

	while(count > 0){
		if(Fd_index==6 || Fd_index==263 || (Fd_index-264>=0 &&(Fd_index-264)%257==0)){
			Fd_index++;
			continue;
		}
		read_block(inode_array[Fd_index], read_unit);

		if(count < (BLOCKSIZE - Fd_offset)){
			memcpy(tmp+result, read_unit+Fd_offset, count);
			result += count;
			count -= count;
			Fd_offset += count;
		}
		else{
			memcpy(tmp+result, read_unit+Fd_offset, BLOCKSIZE - Fd_offset);
			count -= (BLOCKSIZE - Fd_offset);
			result += (BLOCKSIZE - Fd_offset);
			Fd_index ++;
			Fd_offset = 0;
		}
	}
	return result;
}


/* sequentially write to a file 
   fd: the inode of the file 
   buf: char buf[count] is the content to write to disc 
   count: the size of the file, in Byte 
   return: -1: failed, count: succeed */
int my_write(int fd, void *buf, int count)
{
	int i;
	int result = 0;
	char *tmp = buf;
	int sizet = count;
	// test whether the fd exist
	if(Fd_inode != fd)
		return -1;

	char buff_sup[BLOCKSIZE];
	read_block(0, buff_sup);
	struct SuperBlock *read_spb = buff_sup;
	// if there is enough space to write
	if(read_spb->block_free_size <= count/BLOCKSIZE)
		return -1;
	int b_addr = read_spb->block_bp_addr;
	int b_free = read_spb->block_free;

	Read_all_blocks(fd);

	char write_unit[BLOCKSIZE];
	while(count > 0){
		if(inode_array[Fd_index] == 0){
			inode_array[Fd_index] = b_free;
			Set_bitmap(b_free, b_addr);
			b_free = Find_free(b_free, b_addr);
			read_spb->block_free = b_free;
			read_spb->block_free_size--;

			if(Fd_index==6){
				struct First_ fir;
				write_block(inode_array[Fd_index], (char *)&fir);
				Fd_index++;
				continue;
			}
			else if(Fd_index==263){
				struct Second_1 sec1;
				write_block(inode_array[Fd_index], (char *)&sec1);
				Fd_index++;
				continue;
			} 
			else if(Fd_index-264>=0 &&(Fd_index-264)%257==0 ){
				struct Second_2 sec2;
				write_block(inode_array[Fd_index], (char *)&sec2);
				Fd_index++;
				continue;
			}
		}
		read_block(inode_array[Fd_index], write_unit);
		if(count < (BLOCKSIZE - Fd_offset)){
			memcpy(write_unit+Fd_offset, tmp+result, count);
			write_block(inode_array[Fd_index], write_unit);
			result += count;
			Fd_offset += count;
			count -= count;
		}
		else{
			memcpy(write_unit+Fd_offset, tmp+result, BLOCKSIZE - Fd_offset);
			write_block(inode_array[Fd_index], write_unit);
			count -= (BLOCKSIZE - Fd_offset);
			result += (BLOCKSIZE - Fd_offset);
			Fd_index ++;
			Fd_offset = 0;
		}
	}

	write_block(0, buff_sup);
	Save_all_blocks(fd);
	return result;
}


/* release the fd, return 0: success, -1: failed to find the fd */
int my_close(int fd)
{
	int i;
	for(i=0; i<MAX_OPEN_FILES; i++){
		if(open_fd[i] == fd){
			Fd_inode = 0;
			Fd_index = 0;
			Fd_offset = 0;
			open_fd[i] = 0;
			return 0;
		}
	}
	return -1;
}


/* remove a file and free all its blocks, succeed return 0.
   if the file doesn't exist, return -1 */
int my_remove(char *path)
{
	int i=0;
	char sub_path[10][60];
	int path_level = Split_path(path, sub_path);
	int par_dir_block = BITMAP_OFFSET;

	for(i=0; i<path_level-1; i++){
		// didn't find the previous path
		par_dir_block = Find_dir_block(sub_path[i], par_dir_block);
		if(par_dir_block == -1)
			return -1; 
	}
	
	// test whether the file already exist
	int inode = Find_dir_inode(sub_path[i], par_dir_block);
	if(inode < 0)
		return -1;
	Rm_file(inode, par_dir_block);
	return 0;
}


/* rename a file, also support move, for example from "/foo/bar0" to "/qqq" 
   if old file doesn't exist, return -1; otherwise return 0 */
int my_rename(char *old, char *new)
{
	int i=0;
	char sub_path_old[10][60], sub_path_new[10][60];
	int path_level_old = Split_path(old, sub_path_old);
	int path_level_new = Split_path(new, sub_path_new);
	int par_dir_block = BITMAP_OFFSET;

	// didn't find the old file
	for(i=0; i<path_level_old-1; i++){
		par_dir_block = Find_dir_block(sub_path_old[i], par_dir_block);
		if(par_dir_block == -1)
			return -1; 
	}
	int i_node = Find_dir_inode(sub_path_old[i], par_dir_block);
	if(i_node == -1)
		return -1;
	// remove old file from old path, just clear it from its parent's directory
	Clear_par_dir(i_node, par_dir_block);

	// add new file name to new path, its inode is the old inode
	par_dir_block = BITMAP_OFFSET;
	for(i=0; i<path_level_new-1; i++){
		par_dir_block = Find_dir_block(sub_path_new[i], par_dir_block);
		if(par_dir_block == -1)
			return -1; 
	}
	Add_par_dir(i_node, sub_path_new[i], par_dir_block);
	return 0;
}
