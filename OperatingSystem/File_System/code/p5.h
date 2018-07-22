
#ifndef P5_H
#define P5_H

#define MAX_FILE_NAME_LENGTH 200
#define MAX_OPEN_FILES 10
#define INODE_MAX 5024
#define INODE_START 34
#define MAX_FILE_LENGTH (50 * 1024 * 1024)
#define BLOCK_MAX 250000
#define BITMAP_OFFSET 200
#define INT_SIZE sizeof(int)
#define BITMAP_SIZE (1024*8)
#define INODE_SIZE sizeof(struct Inode)
#define INODE_PER_BLOCK (BLOCKSIZE/INODE_SIZE)
#define BLOCKSIZE 1024
#define INODE_ARRAR_SIZE (8+256+256*257+1)

int Fd_inode;
int Fd_index;
int Fd_offset;
int inode_array[INODE_ARRAR_SIZE];
int open_fd[MAX_OPEN_FILES];

/* define structs */
struct SuperBlock{
	int built_fs;

	int inode_sum;
	int inode_bitmap;
	int inode_bp_addr;
	int inode_start_addr;
	int inode_free;
	int file_max;

	int block_size;
	int block_sum;
	int block_bitmap;
	int block_bp_addr;
	int block_free;
	int block_free_size;

	int root_dir;
 
	int rest[242];   
};


struct Inode{
	int addr[6];
	int first_level;
	int second_level;
};

struct First_{
    int addr[256];
};

struct Second_1{    // point to the block number in disc 
    int addr[256];
};

struct Second_2{
    int addr[256];
};

struct Dir_element{
	int inode_num;
	char filename[60];
};


struct Dir{
	int exist_num;	// apart from current and parent
	struct Dir_element current;
	struct Dir_element parent;
	struct Dir_element files[13];

	int rest[15];
};

struct Bitmap{
	int bitmap[BLOCKSIZE/INT_SIZE];
};

struct InodeArray{
	struct Inode inodes[INODE_PER_BLOCK];
};


/* file API */
extern int my_open (char * path);
extern int my_creat (char * path);
extern int my_read (int fd, void * buf, int count);
extern int my_write (int fd, void * buf, int count);
extern int my_close (int fd);

extern int my_remove (char * path);
extern int my_rename (char * old, char * new);
extern int my_mkdir (char * path);
extern int my_rmdir (char * path);

extern void my_mkfs ();

/* auxiliary functions to implement file APIs */
extern void Init_bitmap(int start_addr, int len, int block_bpm);
extern void Init_inode(int start_addr, int len, int block_bpm);
extern void Init_rootDir(int addr, int bitmap_addr);
extern void Set_bitmap(int bit_num, int block_addr);
extern int Test_bitmap(int bit_num, int block_addr);
extern void Clear_bitmap(int bit_num, int block_addr);
extern int Split_path(char *path, char sub_path[10][60]);
extern void Init_dir(struct Dir *dir_tmp, int i_node);
extern int Find_free(int beginner, int block_addr);
extern void Add_dir(char path_name[60], int par_dir_block);
extern void Rm_dir(char path_name[60], int par_dir_block, int cur_dir_block);
extern int Inode_to_Block(int inode_number);
extern void Creat_inode(int inode_number, int block_number);
extern int Find_dir_block(char path_name[60], int block_number);
extern int Find_dir_inode(char path_name[60], int block_number);
extern void Clear_par_dir(int del_inode, int par_dir_block);
extern void Add_par_dir(int add_inode, char path_name[60], int par_dir_block);
extern int Add_file(char path_name[60], int par_dir_block);          
extern void Rm_file(int cur_inode, int par_dir_block);
extern void Read_all_blocks(int inode);
extern void Save_all_blocks(int inode);

/* provided by the lower layer */
typedef char block [BLOCKSIZE];

extern int dev_open ();
extern int read_block (int block_num, char * block);
extern int write_block (int block_num, char * block);

#endif /* P5_H */

