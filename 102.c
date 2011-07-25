#include <stdio.h>
#include <stdlib.h>

enum
{
	COLOR_BROWN = 0,
	COLOR_CLEAR,
	COLOR_GREEN,
};

static char colorCharMap[3] = { 'B', 'C', 'G' };

struct bucket
{
	unsigned int bins[3];	/* 0 : brown, 1 : clear, 2 : green */
};

/* BCG => BGC => CBG => CGB => GBC => GCB */
static int colorCheckOrder[6][3] = 
{
	{COLOR_BROWN, COLOR_CLEAR, COLOR_GREEN },
	{COLOR_BROWN, COLOR_GREEN, COLOR_CLEAR },
	{COLOR_CLEAR, COLOR_BROWN, COLOR_GREEN },
	{COLOR_CLEAR, COLOR_GREEN, COLOR_BROWN },
	{COLOR_GREEN, COLOR_BROWN, COLOR_CLEAR },
	{COLOR_GREEN, COLOR_CLEAR, COLOR_BROWN },
};

static unsigned int moveOfColor( struct bucket *Bucket, int color )
{
	int i;
	unsigned int ret = 0;
	for( i = COLOR_BROWN; i <= COLOR_GREEN; i++ )
	{
		if( i == color )
			continue;
		ret += Bucket->bins[i];
	}
	return ret;
}

int main( int argc, char *argv[] )
{
	struct bucket buckets[3];
	unsigned int minMoves, moves;
	int colorIndex, minColorIndex;
	
	while( scanf( "%u %u %u %u %u %u %u %u %u",
		&(buckets[0].bins[0]), &(buckets[0].bins[2]), &(buckets[0].bins[1]), 
		&(buckets[1].bins[0]), &(buckets[1].bins[2]), &(buckets[1].bins[1]), 
		&(buckets[2].bins[0]), &(buckets[2].bins[2]), &(buckets[2].bins[1]) ) != -1 )
	{
		minMoves = 0xFFFFFFFF;
		/* BCG => BGC => CBG => CGB => GBC => GCB */
		for( colorIndex = 0; colorIndex < 6; colorIndex++ )
		{
			// Move of bins = number of bins which is not the color of buckets
			moves = moveOfColor( &buckets[0], colorCheckOrder[colorIndex][0] )
					+ moveOfColor( &buckets[1], colorCheckOrder[colorIndex][1] )
					+ moveOfColor( &buckets[2], colorCheckOrder[colorIndex][2] );

/*
printf( "Calculate : %c%c%c %u\n", colorCharMap[colorCheckOrder[colorIndex][0]],
						colorCharMap[colorCheckOrder[colorIndex][1]],
						colorCharMap[colorCheckOrder[colorIndex][2]],
						moves );
*/

			if( moves < minMoves )
			{
				minMoves = moves;
				minColorIndex = colorIndex;
			}
		}

		printf( "%c%c%c %u\n", colorCharMap[colorCheckOrder[minColorIndex][0]],
							colorCharMap[colorCheckOrder[minColorIndex][1]],
							colorCharMap[colorCheckOrder[minColorIndex][2]],
							minMoves );
	}
	return 0;
}