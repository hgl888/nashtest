
#include "StdAfxflash.h"

#include "flashmemcop.h"


//
// A very fast memory allocator for uniform sized objects
//

typedef struct _XChunkItem {
	_XChunkBlock* block;
	_XChunkItem* nextFree;
}ChunkItem;

typedef struct _XChunkBlock {
	long tag;

	XChunkAlloc* alloc;
	_XChunkBlock* next;
	_XChunkBlock* prev;
	_XChunkItem* freeList;

 	void* mem;

	U16 nAlloc;
	U16 blockId;
	_XChunkItem items[1];
	
	void* Alloc();
	void Free(void*);
}ChunkBlock;

#define ChunkBlockHeadSize (sizeof(ChunkBlock)-sizeof(ChunkItem))

XChunkAlloc::XChunkAlloc(int size, int n, BOOL suppressGC, long tg)
{
	// Make sure the item size is a multiple of 32-bits for proper 
	// structure alignment on RISC CPUs such as the Sparc.
	itemSize = (((size - 1) / 4) + 1) * 4;

	// Enlarge the items so that there is space for the chunkblock owner pointer.
	itemSize += 4;

	blockN = n;
	tag = tg;

	blockId = 0;
	firstFree = 0;
	firstBlock = lastBlock = 0;
	noGarbageCollection = suppressGC;
	
	#ifdef DEBUG
	maxUsed = 0;
	nBlocks = 0;
	nAlloc = 0;
	#endif
}

XChunkAlloc::~XChunkAlloc()
{   
	// Free all of the blocks
	while ( firstBlock )
		FreeChunk(firstBlock);
}

ChunkBlock* XChunkAlloc::CreateChunk()
{
#if PURIFY
	return new ChunkBlock();
#else
	// Allocate a new block
	int n = blockN;
	//if(ChunkBlockHeadSize + itemSize*n==176)
	//	int v=0;
	ChunkBlock* b = (ChunkBlock*)malloc(ChunkBlockHeadSize + itemSize*n);

	b->tag = tag;
	b->alloc = this;
	b->nAlloc = 0;
	b->blockId = blockId++;
	b->freeList = 0;
	
	// Link the block at the end of the list
	b->prev = lastBlock;
	b->next = 0;
	if ( lastBlock )
		lastBlock->next = b;
	if ( !firstBlock )
		firstBlock = b;
	lastBlock = b;

	{// Add the new items to the free list
		ChunkItem* item;
		ChunkItem* next;
		int i = n;
		b->freeList = next = b->items;
		while ( true ) {
			item = next;
			next = (ChunkItem*)((char*)item+itemSize);
			item->block = b;
			if ( --i == 0 ) {
				// reached the end
				item->nextFree = 0;
				break;
			} else {
				item->nextFree = next;
			}
		}
	}
	
	firstFree = b;

	Dbg(nBlocks++;)
	
	//Dbg(if ( !noGarbageCollection )	FLASHOUTPUT("Allocate s=%i\n", itemSize);)
	return b;
#endif // PURIFY
}
	
void XChunkAlloc::FreeChunk(ChunkBlock* b)
{
#if PURIFY
	delete b;
#else
	//FLASHASSERT(b->nAlloc == 0);	// jlg the destructor now calls FreeChunk() so it is ok for the chunk to not be empty...

	// Unlink the block from the list
	if ( b == firstBlock )
		firstBlock = b->next;
	else
		b->prev->next = b->next;
		
	if ( b == lastBlock )
		lastBlock = b->prev;
	else
		b->next->prev = b->prev;
	
	// If this is the first free block, pick a new one...
	if ( firstFree == b )
		firstFree = firstBlock;
	
	// Free the memory
	free(b);
	Dbg(nBlocks--;)
#endif
}

void* XChunkAlloc::Alloc()
{
#if PURIFY
	return (void *) new char[itemSize];

#else
	if ( firstFree && !firstFree->freeList ) {
		// The current free list is empty, look for another one...
		// Note that if firstFree == 0, we can assume that there are no free items and we need a new block...
		ChunkBlock* b;
		for ( b = firstBlock; b; b = b->next ) {
			if ( b->freeList )
			 	break;
		}
	 	firstFree = b;
	}
	
	if ( !firstFree ) {
		if ( CreateChunk() == 0 ) 
			return 0;
	}
	
	ChunkBlock* b = firstFree;
	FLASHASSERT(b && b->freeList);
		
	ChunkItem* c = b->freeList;
	b->freeList = c->nextFree;
	b->nAlloc++;
	
	Dbg(nAlloc++;)
	Dbg(maxUsed = Max(maxUsed, nAlloc));
	Dbg(memset((char*)c + 4, 0xab, itemSize-4));
	
	return (char*)c + 4;	// skip over the chunkblock owner pointer
#endif // Purify
}

void XChunkAlloc::Free(void* item)
{
#if PURIFY
	delete item;
#else
	ChunkItem* i = (ChunkItem*)((char*)item - 4);	// adjust for the chunkblock owner pointer
	ChunkBlock* b = i->block;
	
	FLASHASSERT(b->alloc == this);

	Dbg(memset((char*)i + 4, 0xba, itemSize-4));	// write junk to detect dangling pointers
	
	// Add the item to the free list of the block
	i->nextFree = b->freeList;
	b->freeList = i;
	b->nAlloc--;
	
	// Free the block if it is empty
	if ( b->nAlloc == 0 && !noGarbageCollection ) {
		FreeChunk(b);
		
	} else {
		// See if this block has a lower priority than the current first free list
		if ( !firstFree || b->blockId < firstFree->blockId )
			firstFree = b;
	}
	
	Dbg(nAlloc--);
#endif // Purify
}

void XChunkAlloc::FreeEmpties()
// deallocate any empty chunks
{
#if PURIFY

#else
	// Look for empty blocks
	for ( ChunkBlock* b = firstBlock; b; ) {
		ChunkBlock* next = b->next;
		if ( b->nAlloc == 0 ) 
			FreeChunk(b);
		b = next;
	}
#endif // Purify
}


// //#ifndef _MAC
// #if ! defined( GENERATOR ) && ! defined( SPRITE_XTRA )

// Custom new and delete operators
Dbg(int cBlocksAllocated = 0;)  // Count of blocks allocated.

// User-defined operator new.
/*void *operator new(size_t size)
{
	Dbg(cBlocksAllocated++;)
    return malloc(size);
}

// User-defined operator delete.
void operator delete( void *p )
{
    free(p);
	Dbg(cBlocksAllocated--;)
}*/

#ifdef _DEBUG
void _FlashDebug()
{
	 int v=0;
}
#endif