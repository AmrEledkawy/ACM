#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef DEBUG

#define MAX_BOX_DIMENSION	(10)
#define MAX_BOX_NUM			(30)

struct boxStackRecord
{
	int previousBox;
	int stackCount;
};

struct boxDataRecord
{
	int dimension[MAX_BOX_DIMENSION];
	int index;
};


static struct boxDataRecord boxData[MAX_BOX_NUM];
static int boxDimension, boxNum;

static struct boxStackRecord boxStack[MAX_BOX_NUM];
static int maxStack, maxStackBox;

static int compareBoxDimension(const void *a, const void *b)
{
	int dimA = *(int *)a, dimB = *(int *)b;
	
	/*
	 * Return positive while latter is larger, so we can get descending order
	 */
	return (dimB - dimA);
}

static int compareBox(const void *a, const void *b)
{
	const struct boxDataRecord *boxA = (const struct boxDataRecord *)a,
							*boxB = (const struct boxDataRecord *)b;
	const int *boxDimA = boxA->dimension, *boxDimB = boxB->dimension;
	int i;
	
	/*
	 * Return negative while latter is larger, so we can get ascending order
	 */
	for ( i = 0; i < boxDimension; i++ ) {
		if ( boxDimA[i] > boxDimB[i] )
			return 1;
		else if ( boxDimA[i] < boxDimB[i] )
			return -1;
	}
	
	return 0;
}

static int isBoxLarger( struct boxDataRecord *boxA, struct boxDataRecord *boxB )
{
	int *boxDimA = boxA->dimension, *boxDimB = boxB->dimension;
	int i;
	
	for ( i = 0; i < boxDimension; i++ ) {
		if( boxDimA[i] <= boxDimB[i] )
			return -1;
	}
	
	return 1;
}

static int getBoxProfile(void)
{
	int i, j, ret;

	if ( scanf( "%d %d", &boxNum, &boxDimension ) <= 0 ) {
		return 0;
	}

	memset( boxData, 0, sizeof(boxData) );

	for ( i = 0; i < boxNum; i++ ) {
		boxData[i].index = i;
		for ( j = 0; j < boxDimension; j++ ) {
			scanf( "%d", &boxData[i].dimension[j] );
		}
		
		/*
		 * Sort dimensions of box in descending order
		 */
		qsort( boxData[i].dimension, boxDimension, sizeof(int), compareBoxDimension );
	}
	
	/*
	 * Order boxes in dimension ascending order
	 */
	qsort( boxData, boxNum, sizeof(struct boxDataRecord), compareBox );
	
	return 1;
}

static void findMaxStack(void)
{
	int i, j;

	maxStack = 0;
	maxStackBox = -1;

	for ( i = 0; i < boxNum; i++ ) {
		
		boxStack[i].previousBox = -1;
		boxStack[i].stackCount = 0;
		
		for ( j = 0; j < i; j++ ) {
			if ( isBoxLarger( &boxData[i], &boxData[j] ) > 0 ) {
#ifdef DEBUG
printf( "Box %d can put in Box %d\n", j, i );
#endif
				/*
				 * box[j] can be stack into box[i]
				 */
				if( boxStack[j].stackCount > boxStack[i].stackCount ) {
					boxStack[i].stackCount = boxStack[j].stackCount;
					boxStack[i].previousBox = j;
#ifdef DEBUG
printf( "Box %d, stack count %d, previous Box %d\n", i, boxStack[i].stackCount, boxStack[i].previousBox );
#endif

				}
			}
		}
		boxStack[i].stackCount++;
		
		if ( boxStack[i].stackCount > maxStack ) {
			maxStack = boxStack[i].stackCount;
			maxStackBox = i;
#ifdef DEBUG
printf( "max Stack %d, maxStackBox %d\n", maxStack, maxStackBox );
#endif
		}
		
	}
}

static void dumpMaxStack( int currentBoxIndex )
{
	if( currentBoxIndex < 0 )
		return;

	dumpMaxStack( boxStack[currentBoxIndex].previousBox );
	
	printf( "%d ", boxData[currentBoxIndex].index + 1 );
}

static void printResult(void)
{
	printf( "%d\n", maxStack );
#ifdef DEBUG
	printf( "Max Stack Box %d\n", maxStackBox );
#endif
	dumpMaxStack( maxStackBox );
	printf( "\n" );
}

#ifdef DEBUG
static void printBoxProfile(void)
{
	int i, j;
	
	printf( "======= Box Profile =======\n" );
	printf( "%d boxes of dimension %d\n", boxNum, boxDimension );
	
	for ( i = 0; i < boxNum; i++ ) {
		printf( "Box %2d, index %2d : ", i, boxData[i].index );
		for ( j = 0; j < boxDimension; j++ ) {
			printf( "%4d ", boxData[i].dimension[j] );
		}
		printf( "\n" );
	}
	printf( "==========================\n" );
}

static int printStackInfo(void)
{
	int i, j;
	
	printf( "======= Stack Info =======\n" );
	
	for ( i = 0; i < boxNum; i++ ) {
		printf( "Box %2d, index %d, previous box %2d, stack count %2d\n", i, boxData[i].index, boxStack[i].previousBox, boxStack[i].stackCount );
	}
	printf( "==========================\n" );
}
#endif

int main( int argc, char *argv[] )
{
	while ( getBoxProfile() ) {
		
#ifdef DEBUG
		printBoxProfile();
#endif
	
		findMaxStack();
	
#ifdef DEBUG
		printStackInfo();
#endif

		printResult();
	}
	
	return 0;
}
