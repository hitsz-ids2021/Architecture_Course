/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "1",
    /* First member's full name */
    "csapp",
    /* First member's email address */
    "@hit.edu",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};

//字大小和双字大小
#define WSIZE 4
#define DSIZE 8
//当堆内存不够时，向内核申请的堆空间
#define CHUNKSIZE (1<<12)
//将val放入p开始的4字节中
#define PUT(p,val) (*(unsigned int*)(p) = (val))
//获得头部和脚部的编码
#define PACK(size, alloc) ((size) | (alloc))
//从头部或脚部获得块大小和已分配位
#define GET_SIZE(p) (*(unsigned int*)(p) & ~0x7)
#define GET_ALLO(p) (*(unsigned int*)(p) & 0x1)
//获得块的头部和脚部
#define HDRP(bp) ((char*)(bp) - WSIZE)
#define FTRP(bp) ((char*)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)
//获得上一个块和下一个块
#define NEXT_BLKP(bp) ((char*)(bp) + GET_SIZE(HDRP(bp)))
#define PREV_BLKP(bp) ((char*)(bp) - GET_SIZE((char*)(bp) - DSIZE))

#define MAX(x,y) ((x)>(y)?(x):(y))
static char *heap_listp = 0;

static void *extend_heap(size_t words);
static void *coalesce(void *bp);
static void *find_fit(size_t size);
static void place(void *bp,size_t asize);

/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
	if((heap_listp = mem_sbrk(4*WSIZE)) == (void*)-1)	//申请4字空间
		return -1;
	PUT(heap_listp, 0);	//填充块
	PUT(heap_listp+1*WSIZE, PACK(DSIZE, 1));	//序言块头部
	PUT(heap_listp+2*WSIZE, PACK(DSIZE, 1));	//序言块脚部
	PUT(heap_listp+3*WSIZE, PACK(0, 1));		//结尾块
	
	heap_listp += DSIZE;	//指向序言块有效载荷的指针
	
	if(extend_heap(CHUNKSIZE/WSIZE) == NULL)	//申请更多的堆空间
		return -1;
	return 0;
}

static void *extend_heap(size_t words){
    	char *bp;
	size_t size;
	size = words%2 ? (words+1)*WSIZE : words*WSIZE;	//对大小双字对对齐
	if((bp = mem_sbrk(size)) == (void*)-1)	//申请空间
		return NULL;
	PUT(HDRP(bp), PACK(size, 0));	//设置头部
	PUT(FTRP(bp), PACK(size, 0));	//设置脚部
	PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));	//设置新的结尾块
	//合并旧堆的最后一个可能出现的空闲块  
	return coalesce(bp);
}

static void *coalesce(void *bp){
	size_t prev_alloc = GET_ALLO(FTRP(PREV_BLKP(bp)));	//获得前面块的已分配位
	size_t next_alloc = GET_ALLO(HDRP(NEXT_BLKP(bp)));	//获得后面块的已分配位
	size_t size = GET_SIZE(HDRP(bp));	//获得当前块的大小
	
	if(prev_alloc && next_alloc){
		return bp;
	}else if(prev_alloc && !next_alloc){
		size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
		PUT(HDRP(bp), PACK(size, 0));
		PUT(FTRP(bp), PACK(size, 0));
	}else if(!prev_alloc && next_alloc){
		size += GET_SIZE(FTRP(PREV_BLKP(bp)));
		PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
		PUT(FTRP(bp), PACK(size, 0));
		bp = PREV_BLKP(bp);
	}else{
		size += GET_SIZE(HDRP(NEXT_BLKP(bp))) +
				GET_SIZE(FTRP(PREV_BLKP(bp)));
		PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
		PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
		bp = PREV_BLKP(bp);
	}
	return bp;
}

/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
	size_t asize;
	void *bp;
	
	if(size == 0)
		return NULL;
	//满足最小块要求和对齐要求，size是有效负载大小
	asize = size<=DSIZE ? 2*DSIZE : DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE);
	//匹配
	if((bp = find_fit(asize)) != NULL){
		place(bp, asize);
		return bp;
	}
	if((bp = extend_heap(MAX(CHUNKSIZE, asize)/WSIZE)) == NULL)
		return NULL;
	place(bp, asize);
	return bp;
}

static void *find_fit(size_t asize)
/* $end mmfirstfit-proto */
{
    /* $begin mmfirstfit */
    /* First-fit search */
	void *bp;

	for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
	if (!GET_ALLO(HDRP(bp)) && (asize <= GET_SIZE(HDRP(bp)))) {
		return bp;
        }
    }
    return NULL; /* No fit */
}

static void place(void *bp,size_t asize){
    size_t csize = GET_SIZE(HDRP(bp));
    if((csize-asize)>=(2*DSIZE)){
        PUT(HDRP(bp),PACK(asize,1));
        PUT(FTRP(bp),PACK(asize,1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp),PACK(csize-asize,0));
        PUT(FTRP(bp),PACK(csize-asize,0));
    }else{
        PUT(HDRP(bp),PACK(csize,1));
        PUT(FTRP(bp),PACK(csize,1));
    }
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr){
	size_t size = GET_SIZE(HDRP(ptr));
	PUT(HDRP(ptr), PACK(size, 0));
	PUT(FTRP(ptr), PACK(size, 0));

	coalesce(ptr);
} 

void *mm_realloc(void *ptr, size_t size)
{
    size_t oldsize;
    void *newptr;

    /* If size == 0 then this is just free, and we return NULL. */
    if(size == 0) {
        mm_free(ptr);
        return 0;
    }

    /* If oldptr is NULL, then this is just malloc. */
    if(ptr == NULL) {
        return mm_malloc(size);
    }

    newptr = mm_malloc(size);

    /* If realloc() fails the original block is left untouched  */
    
    if(!newptr) {
        return 0;
    }

    /* Copy the old data. */
    oldsize = GET_SIZE(HDRP(ptr));
    if(size < oldsize) oldsize = size;
    memcpy(newptr, ptr, oldsize);

    /* Free the old block. */
    mm_free(ptr);

    return newptr;
}











