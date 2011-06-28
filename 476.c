#include <stdio.h>

#define MAX_RECTANGLE_NUM	(10)

struct rectangle
{
	double top, left, bottom, right;
};

struct rectangle rectangles[MAX_RECTANGLE_NUM];
int rectangleNum;

int main( int argc, char *argv[] )
{
	char inputType;
	double inputX, inputY;
	struct rectangle *pRect;
	int i, pointIndex, containCount;

	rectangleNum = 0;
	pRect = rectangles;
	while( 0 < scanf( " %c", &inputType ) )
	{
		if( inputType == 'r' )
		{
			scanf( " %lf %lf %lf %lf", &pRect->left, &pRect->top, &pRect->right, &pRect->bottom );
			rectangleNum++;
			pRect++;
		}else if( inputType == '*' )
		{
			break;
		}else
		{
			printf( "Error input format\n" );
			break;
		}
	}
	
	pointIndex = 0;
	while( 2 == scanf( " %lf %lf", &inputX, &inputY ) )
	{
		pointIndex++;
		if( inputX == 9999.9 && inputY == 9999.9 )
		{
			break;
		}
		
		containCount = 0;
		for( i = 0, pRect = rectangles; i < rectangleNum; i++, pRect++ )
		{
			if( inputX > pRect->left && inputX < pRect->right && inputY < pRect->top && inputY > pRect->bottom )
			{
				printf( "Point %d is contained in figure %d\n", pointIndex, i+1 );
				containCount++;
			}
		}
		if( 0 == containCount )
		{
			printf( "Point %d is not contained in any figure\n", pointIndex );
		}
	}
	
	return 0;
}
