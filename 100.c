#include <stdio.h>
#include <stdlib.h>

/* As question mentioned, valid value is 1 ~ 10000000 */
#define MAX_LENGTH_VALUE (1000000)
#define MAX_CYCLE_QUEUE  (1000)

/* Save calculated cycle length for corresponding value */
unsigned int cycleLengthCache[MAX_LENGTH_VALUE] = {0};

/* Queue cycle length calculation value until the cycle length of value is already saved in cycleLengthCache */
unsigned int cycleLengthQueue[MAX_CYCLE_QUEUE] = {0};

/* Length of cycle length calculatioin queue */
unsigned int cycleLengthQueueSize;

/* Return cycle length for value */
unsigned int getCycleLength( unsigned int value )
{
	/* Use unsigned int to prevent value overflow */
	unsigned int tmpValue, tmpLength;
	cycleLengthQueueSize = 0;

	tmpLength = 1;
	while( 1 )
	{
		if( value <= 0 )
		{
			printf( "ERROR : value overflow(%d)\n", value );
			fflush(stdout);
			return 0;
		}

		/* Store value into calucation queue */
		cycleLengthQueue[cycleLengthQueueSize++] = value;

		/* Terminating condition
		   1. Value is in range provided in question
		   2. Cycle length for value is found, this also includes find previous calculated cycle length
		*/
		if( value < MAX_LENGTH_VALUE && 0 != cycleLengthCache[value] )
		{
			tmpLength = cycleLengthCache[value];
			break;
		}

		/* Update next value */
		if( value & 0x1 )
		{
			tmpValue = 3 * value + 1;
		}else
		{
			tmpValue = value / 2;
		}
		
		value = tmpValue;
		
		/* Queue is out of use, this should never happen */
		if( cycleLengthQueueSize >= MAX_CYCLE_QUEUE )
		{
			printf( "ERROR : queue size of %d overflow\n", cycleLengthQueue[0] );
			fflush(stdout);
			return 0;
		}
	}

	/* Dequeue the cycle length calculation, tmpLength the cycle length of current queued value*/
	while( 0 != cycleLengthQueueSize )
	{
		tmpValue = cycleLengthQueue[--cycleLengthQueueSize];

		if( tmpValue < MAX_LENGTH_VALUE && 0 == cycleLengthCache[tmpValue] )
		{
			/* Update cycle length for value is value is in range provided by question */
			cycleLengthCache[tmpValue] = tmpLength;
		}
		tmpLength++;
	}

	return cycleLengthCache[cycleLengthQueue[0]];
}

int main(int argc, char *argv[])
{
	unsigned int start, end, tmp, tmpLength, maxLength;

	cycleLengthCache[1] = 1;
	/* Get input */
	while( 2 == scanf( "%d %d", &start, &end ) )
	{
		/* Print input value */
		printf( "%d %d ", start, end );

		/* Make sure start is smaller than end */
		if( end < start )
		{
			tmp = start;
			start = end;
			end = tmp;
		}
		
		/* Find max cycle length */
		maxLength = 0;
		for( tmp = start; tmp <= end; tmp++ )
		{
			tmpLength = getCycleLength(tmp);

			if( maxLength < tmpLength )
				maxLength = tmpLength;
		}
		
		/* Print result */
		printf( "%d\n", maxLength );
	}
	return 0;
}