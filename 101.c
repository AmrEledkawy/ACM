#include <stdio.h>
#include <string.h>

#define MAX_BLOCK_NUM	(25)

struct block
{
	int currentColumn;
	int topBlock;
	int bottomBlock;
};

struct block blockData[MAX_BLOCK_NUM];
int blockColumn[MAX_BLOCK_NUM];

int main( int argc, char *argv[] )
{
	int blockNum, i, j;
	int srcBlock, tgtBlock, srcColumn, tgtColumn;
	char action[8], relate[8];
	
	/* Initialize block table */
	scanf( " %d", &blockNum );
	for( i = 0; i < blockNum; i++ )
	{
		blockColumn[i] = i;
		blockData[i].currentColumn = i;
		blockData[i].topBlock = -1;
		blockData[i].bottomBlock = -1;
	}
		
	while( 1 )
	{
		scanf( " %4s", action );
		if( 0 == strncmp( action, "quit", 4 ) )
		{
			break;
		}else
		{
			scanf( " %d %4s %d", &srcBlock, relate, &tgtBlock );
			
			srcColumn = blockData[srcBlock].currentColumn;
			tgtColumn = blockData[tgtBlock].currentColumn;
			
			if( srcColumn == tgtColumn )
				continue;

			/* Clean blocks on top of src */
			if( 0 == strncmp( action, "move", 4 ) )
			{
				for( j = blockData[srcBlock].topBlock; j >= 0; j = i )
				{
					i = blockData[j].topBlock;
					blockData[j].currentColumn = j;
					blockData[j].topBlock = -1;
					blockData[j].bottomBlock = -1;
					blockColumn[j] = j;
				}
				blockData[srcBlock].topBlock = -1;
			}
			
			/* Clean blocks on top of target */
			if( 0 == strncmp( relate, "onto", 4 ) )
			{
				for( j = blockData[tgtBlock].topBlock; j >= 0; j = i )
				{
					i = blockData[j].topBlock;
					blockData[j].currentColumn = j;
					blockData[j].topBlock = -1;
					blockData[j].bottomBlock = -1;
					blockColumn[j] = j;
				}
				blockData[tgtBlock].topBlock = -1;
			}

			/* Find top of target block */
			for( j = blockData[tgtBlock].topBlock; j >= 0; j = blockData[j].topBlock )
			{
				tgtBlock = j;
			}

			blockData[tgtBlock].topBlock = srcBlock;
			blockData[blockData[srcBlock].bottomBlock].topBlock = -1;
			blockData[srcBlock].bottomBlock = tgtBlock;
			while( srcBlock >= 0 )
			{
				blockData[srcBlock].currentColumn = blockData[tgtBlock].currentColumn;
				blockColumn[srcBlock] = -1;
				srcBlock = blockData[srcBlock].topBlock;
			}

/* debug */
/*
for( i = 0; i < blockNum; i++ )
{
printf( "%d:", i );
for( j = blockColumn[i]; j >= 0; j = blockData[j].topBlock )
{
	printf( " %d", j );
}
printf( "\n" );
}
*/
		}
	}
	
	/* Print block layout */
	for( i = 0; i < blockNum; i++ )
	{
		printf( "%d:", i );
		for( j = blockColumn[i]; j >= 0; j = blockData[j].topBlock )
		{
			printf( " %d", j );
		}
		printf( "\n" );
	}
	
	return 0;
}
