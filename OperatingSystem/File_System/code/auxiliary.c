#include "p5.h"
#include <stdio.h>
#include <string.h>

/* define global variables */
int seq, mask;
const char dot[60] = ".";	// current dir
const char dotdot[60] = "..";	// parent dir


/* auxiliary functions to help implement main functions */
/* start address of the first block to store bitmap
	for each block is an int array */
void Init_bitmap(int start_addr, int len, int block_bpm)
{
	int i;
	for (i=start_addr; i<(start_addr+len); i++){
		struct Bitmap bitmap;
        memset(bitmap.bitmap, 0, BLOCKSIZE);
		write_block(i, (char *)&bitmap);
		Set_bitmap(i, block_bpm);
	}
}

/* start_addr: inode_start_addr
   block_bpm: the block address of the free block management */
void Init_inode(int start_addr, int len, int block_bpm)
{
	int i;
	for (i=start_addr; i<(start_addr+len); i++){
		struct InodeArray inode_arr;
        memset(inode_arr.inodes, 0, BLOCKSIZE);
		write_block(i, (char *)&inode_arr);
		Set_bitmap(i, block_bpm); 
	}
}

void Init_rootDir(int addr, int bitmap_addr)
{
	struct Dir root_directory;
	Init_dir(&root_directory, 1);
	write_block(addr, (char *)&root_directory);
	Set_bitmap(addr, bitmap_addr);	// block 200 used
	Set_bitmap(0, 1);	// inode:0
}

void Init_dir(struct Dir *dir_tmp, int i_node)
{
	strcpy(dir_tmp->current.filename, dot);
	strcpy(dir_tmp->parent.filename, dotdot);
	dir_tmp->current.inode_num = i_node;
	dir_tmp->parent.inode_num = i_node;
	dir_tmp->exist_num = 0;
    int i;
    for(i=0; i<13; i++){
        dir_tmp->files[i].inode_num = 0;
        memset(dir_tmp->files[i].filename, 0, 60);
    }
}

/* bit_num: bit number, for example BITMAP_OFFSET is 200.
   block_addr: the block address number 2.
   Meaning that the bit-th block has been used.*/
void Set_bitmap(int bit_num, int block_addr)
{
	int addr = bit_num/(BITMAP_SIZE) + block_addr;
	int bit = bit_num%(BITMAP_SIZE);
	char buff[BLOCKSIZE];
	if(read_block(addr, buff) == 0){
		struct Bitmap *tmp = buff;
		seq = bit/INT_SIZE/8;
		mask = bit%(INT_SIZE*8);
		tmp->bitmap[seq] |= 1<<(mask);
		write_block(addr, buff);
	}
	else{
		printf("read block error.\n");
	}
}

/* return 1: bit has been set.
   return 0: bit hasn't been set.
   return -1: read_block error. */
int Test_bitmap(int bit_num, int block_addr)
{
	int addr = bit_num/BITMAP_SIZE + block_addr;
	int bit = bit_num%BITMAP_SIZE;
	char buff[BLOCKSIZE];
	if(read_block(addr, buff) == 0){
		struct Bitmap *tmp = buff;
		seq = bit/INT_SIZE/8;
		mask = bit%(INT_SIZE*8);
		if((tmp->bitmap[seq]&(1<<(mask)))!=0)
            return 1;
        else
            return 0;
	}
	return -1;
}

/* Meaning that the bit-th block is to free. */
void Clear_bitmap(int bit_num, int block_addr)
{
	int addr = bit_num/BITMAP_SIZE + block_addr;
	int bit = bit_num%BITMAP_SIZE;
	char buff[BLOCKSIZE];
	if(read_block(addr, buff) == 0){
		struct Bitmap *tmp = buff;
		seq = bit/INT_SIZE/8;
		mask = bit%(INT_SIZE*8);
		tmp->bitmap[seq] &= ~(1<<(mask));
		write_block(addr, buff);
	}
	else{
		printf("read block error.\n");
	}
}


/* split path by '/' and return path level 
   store each sub_path name in sub_path[10][60] */
int Split_path(char *path, char sub_path[10][60])
{
    int i, j;
    int path_level = 0;
    char tmp[60]="";
    for(i=0; i<strlen(path); i++){
        if(path[i] == '/'){
            if(i){
                strcpy(sub_path[path_level], tmp);
                path_level++;
            }
            j=0;
            memset(tmp, 0, sizeof(tmp));
        }
        else{
            tmp[j++] = path[i];
        }
    }
    strcpy(sub_path[path_level], tmp);
    path_level++;
    return path_level;
}


/* return the free inode/block number 
   block_addr is 2(free block) or 1(free inode) */
int Find_free(int beginner, int block_addr)
{
	int result = beginner;
	while(1){
		result ++;
		if(Test_bitmap(result, block_addr) == 0){
			return result;
		}
	}
}

/* return the next directory's block number in disc
   if isn't exist, then return -1. 
   block_number is the current block number in disc */
int Find_dir_block(char path_name[60], int block_number)
{
	char buff[BLOCKSIZE];
	read_block(block_number, buff);
	struct Dir *tmp = buff;

	int i;
	for(i=0; i<13; i++){
		if(strcmp(tmp->files[i].filename, path_name) == 0){
			return Inode_to_Block(tmp->files[i].inode_num);
		}
	}
	return -1;
}

/* return the next directory's inode
   if isn't exist, then return -1. 
   block_number is the current block number in disc */
int Find_dir_inode(char path_name[60], int block_number)
{
	int i;
	char buff[BLOCKSIZE];
	read_block(block_number, buff);
	struct Dir *tmp = buff;
	for(i=0; i<13; i++){
		if(strcmp(tmp->files[i].filename, path_name) == 0){
			return tmp->files[i].inode_num;
		}
	}
	return -1;
}


/* return the block number in disc from inode
   only used for searching directory. */
int Inode_to_Block(int inode_number)
{
	int inode_addr = inode_number/INODE_PER_BLOCK + INODE_START;
	int inode_offset = inode_number%INODE_PER_BLOCK;
	char buff[BLOCKSIZE];
	read_block(inode_addr, buff);
	struct InodeArray *tmp = buff;
	return tmp->inodes[inode_offset].addr[0];
}


/* used for making directory */
void Creat_inode(int inode_number, int block_number)
{
	int inode_addr = inode_number/INODE_PER_BLOCK + INODE_START;
	int inode_offset = inode_number%INODE_PER_BLOCK;
	char buff[BLOCKSIZE];
	read_block(inode_addr, buff);
	struct InodeArray *tmp = buff;
	tmp->inodes[inode_offset].addr[0] = block_number;
	write_block(inode_addr, buff);
}


/* par_dir_block: the parent directory's block number
   Used to create a new directory. */
void Add_dir(char path_name[60], int par_dir_block)
{
	char buff[BLOCKSIZE];
	read_block(0, buff);
	struct SuperBlock *read_spb = buff;
    // test whether there is still space to add a new directory
    if(read_spb->block_free_size < 1){
        printf("There is no space in disc.\n");
        return;
    }

	int i = read_spb->inode_free;
	int b = read_spb->block_free;
	int i_add = read_spb->inode_bp_addr;
	int b_add = read_spb->block_bp_addr;

	// 1. create a new directory
	struct Dir dir_tmp;
	Init_dir(&dir_tmp, i);
	write_block(b, (char *)&dir_tmp);
	Set_bitmap(i, i_add); 
	Set_bitmap(b, b_add); 

	// 2. create a corresponding i-node
	Creat_inode(i, b);

	// 3. change free i_node
	int new_inode = Find_free(i, i_add);
	read_spb->inode_free = new_inode;

	// 4. change free block
	int new_block = Find_free(b, b_add);
	read_spb->block_free = new_block;

	// 5. modify superblock
	read_spb->block_free_size --;
	write_block(0, buff);
	
	// 6. add current directory to its parent's directory
	Add_par_dir(i, path_name, par_dir_block);
}


/* insert one sub directory/file record in parent's directory
   and add the exist_num */
void Add_par_dir(int add_inode, char path_name[60], int par_dir_block)
{
    char buff_par[BLOCKSIZE];
	read_block(par_dir_block, buff_par);
	struct Dir *par_dir = buff_par;

    if(par_dir->exist_num >= 13){
        printf("Current directory couldn't hold more sub directorys/files.\n");
        return;
    }

    int i;
    for(i=0; i<13; i++){
        if(par_dir->files[i].inode_num == 0){
            par_dir->files[i].inode_num = add_inode;
            strcpy(par_dir->files[i].filename, path_name);
            break;
        }
    } 
	par_dir->exist_num++;
	write_block(par_dir_block, buff_par);
}


/* par_dir_block: the parent directory's block number
   cur_dir_block: the current directory's block number
   Used to remove a directory. */
void Rm_dir(char path_name[60], int par_dir_block, int cur_dir_block)
{
	char buff[BLOCKSIZE];
	read_block(0, buff);
	struct SuperBlock *read_spb = buff;

	int i = read_spb->inode_free;
	int b = read_spb->block_free;
	int i_add = read_spb->inode_bp_addr;
	int b_add = read_spb->block_bp_addr;

	// 1. remove the directory both in disc and its i-node bitmap
    // and there is no need to modify corresponding blocks in disc
    int cur_inode = Find_dir_inode(path_name, par_dir_block);
	Clear_bitmap(cur_inode, i_add); 
	Clear_bitmap(cur_dir_block, b_add); 

	// 2. change free i_node
	if(cur_inode < i)
	    read_spb->inode_free = cur_inode;

	// 3. change free block
	if(cur_dir_block < b)
	    read_spb->block_free = cur_dir_block;

	// 4. modify superblock
	read_spb->block_free_size ++;
	write_block(0, buff);
	
	// 5. remove current directory from its parent's directory
    Clear_par_dir(cur_inode, par_dir_block);
}


/* par_dir_block: the parent directory's block number
   cur_inode: the current directory's inode
   Used to remove a directory. */
void Rm_file(int cur_inode, int par_dir_block)
{
	char buff[BLOCKSIZE];
	read_block(0, buff);
	struct SuperBlock *read_spb = buff;

	int i = read_spb->inode_free;
	int b = read_spb->block_free;
	int i_add = read_spb->inode_bp_addr;
	int b_add = read_spb->block_bp_addr;

    int inode_addr = cur_inode/INODE_PER_BLOCK + INODE_START;
	int inode_offset = cur_inode%INODE_PER_BLOCK;
	char buff_inode[BLOCKSIZE];
	read_block(inode_addr, buff_inode);
	struct InodeArray *tmp = buff_inode;

    // change free i_node
	if(cur_inode < i)
	    read_spb->inode_free = cur_inode;
    // clear inode bitmap 
    Clear_bitmap(cur_inode, i_add);

	// change free block
    int cur_dir_block = tmp->inodes[inode_offset].addr[0];
	if(cur_dir_block < b)
	    read_spb->block_free = cur_dir_block;

    // clear free block bitmap 
    Read_all_blocks(cur_inode);
    
    int j;
    int sum = 0;
    for(j=0; j<INODE_ARRAR_SIZE; j++){
        if(inode_array[j]){
            sum++;
            Clear_bitmap(inode_array[j], b_add);
        }
        else{
            break;
        }
    }
    read_spb->block_free_size += sum;
    memset(inode_array, 0, sizeof(inode_array));

    Save_all_blocks(cur_inode);

	// modify superblock
	write_block(0, buff);

	// remove current file from its parent's directory
    Clear_par_dir(cur_inode, par_dir_block);
}



/* change the del_inode in parent's directory to 0
   and minus the exist_num */
void Clear_par_dir(int del_inode, int par_dir_block)
{
    char buff_par[BLOCKSIZE];
	read_block(par_dir_block, buff_par);
	struct Dir *par_dir = buff_par;

    int i;
    for(i=0; i<13; i++){
        if(par_dir->files[i].inode_num == del_inode){
            par_dir->files[i].inode_num = 0;
            memset(par_dir->files[i].filename, 0, 60);
            break;
        }
    } 
	par_dir->exist_num--;
	write_block(par_dir_block, buff_par);
}


/* return fd(inode) if there is room for one file, otherwise return -1 */
int Add_file(char path_name[60], int par_dir_block)
{
    char buff[BLOCKSIZE];
	read_block(0, buff);
	struct SuperBlock *read_spb = buff;
    // test whether there is still space to add a new directory
    if(read_spb->block_free_size < 1){
        printf("There is no space in disc.\n");
        return -1;
    }

	int i = read_spb->inode_free;
	int b = read_spb->block_free;
	int i_add = read_spb->inode_bp_addr;
	int b_add = read_spb->block_bp_addr;

	// 1. create a new file
	Set_bitmap(i, i_add); 
	Set_bitmap(b, b_add); 

    // 2. create a corresponding i-node
	Creat_inode(i, b);

	// 3. change free i_node
	int new_inode = Find_free(i, i_add);
	read_spb->inode_free = new_inode;

	// 4. change free block
	int new_block = Find_free(b, b_add);
	read_spb->block_free = new_block;

	// 5. modify superblock
	read_spb->block_free_size --;
	write_block(0, buff);
	
	// 6. add new file to its parent's directory
	Add_par_dir(i, path_name, par_dir_block);

    return i;
}



/* read and put all block numbers in disc to inode_array */
void Read_all_blocks(int inode)
{
    int inode_addr = inode/INODE_PER_BLOCK + INODE_START;
	int inode_offset = inode%INODE_PER_BLOCK;
	char buff_inode[BLOCKSIZE];
	read_block(inode_addr, buff_inode);
	struct InodeArray *tmp = buff_inode;

    int i, j;
	int num = 0;
    char first_buff[BLOCKSIZE];
    char sec_buff[BLOCKSIZE];
    int first_number = tmp->inodes[inode_offset].first_level;
    int second_number = tmp->inodes[inode_offset].second_level;
    struct First_ *first_;
    struct Second_1 *second_1;
    struct Second_2 *second_2;

	// put all the block number in inode_array
	memset(inode_array, 0, sizeof(inode_array));
	for(i=0; i<6; i++){
		inode_array[num++] = tmp->inodes[inode_offset].addr[i];
	}

    if(first_number){
        inode_array[num++] = first_number;
        read_block(first_number, first_buff);
        first_ = first_buff;
        for(i=0; i<256; i++){
            inode_array[num++] = first_->addr[i];
        }
    }
    else
        return;

    if(second_number){
        inode_array[num++] = second_number;
        read_block(second_number, first_buff);
        second_1 = first_buff;
        for(i=0; i<256; i++){
            if(second_1->addr[i]){
                inode_array[num++] = second_1->addr[i];
                read_block(second_1->addr[i], sec_buff);
                second_2 = sec_buff;
                for(j=0; j<256; j++){
                    inode_array[num++] = second_2->addr[j];
                }
            }
            else{
                return;
            }
        }
    }
}

/* write back all block numbers in disc from inode_array */
void Save_all_blocks(int inode)
{
    int inode_addr = inode/INODE_PER_BLOCK + INODE_START;
	int inode_offset = inode%INODE_PER_BLOCK;
	char buff_inode[BLOCKSIZE];
	read_block(inode_addr, buff_inode);
	struct InodeArray *tmp = buff_inode;

    int i, j;
	int num = 0;
    int first_number;
    int second_number;
    char fir_buff[BLOCKSIZE];
    char sec_buff[BLOCKSIZE];
    struct First_ *first_;
    struct Second_1 *second_1;
    struct Second_2 *second_2;
    int block_to_write;

	// put all the block number in inode_array back to disc
	for(i=0; i<6; i++){
		tmp->inodes[inode_offset].addr[i] = inode_array[num++];
	}

    first_number = inode_array[num++];
    if(first_number){
        tmp->inodes[inode_offset].first_level = first_number;
        read_block(first_number, fir_buff);
        first_ = fir_buff;
        for(i=0; i<256; i++){
            first_->addr[i] = inode_array[num++];
        }
        write_block(first_number, fir_buff);
    }

    second_number = inode_array[num++];
    if(second_number){
        tmp->inodes[inode_offset].second_level = second_number;
        read_block(second_number, fir_buff);
        second_1 = fir_buff;

        for(i=0; i<256; i++){
            block_to_write = inode_array[num++];
            second_1->addr[i] = block_to_write;
            if(block_to_write){
                read_block(block_to_write, sec_buff);
                second_2 = sec_buff;
                for(j=0; j<256; j++){
                    second_2->addr[j] = inode_array[num++];
                }
                write_block(block_to_write, sec_buff);
            }
            else{
                break;
            }
        }
        write_block(second_number, fir_buff);
    }
    write_block(inode_addr, buff_inode);
}