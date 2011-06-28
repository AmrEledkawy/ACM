#include <stdio.h>

#define MAX_SHAPE_NUM	(10)

struct point
{
	double x, y;
};

struct rectangleData
{
	struct point topLeft, bottomRight;
};

struct circleData
{
	struct point center;
	double radius;
};

struct triangleData
{
	struct point vertix[4];
	/* 4th element is 1st element, for vector calculation */
};

#define SHAPE_RECTANGLE		(1)
#define SHAPE_CIRCLE		(2)
#define SHAPE_TRIANGLE		(3)
struct shape
{
	int shapeType;
	union
	{
		struct triangleData triangle;
		struct circleData circle;
		struct rectangleData rectangle;
	} shapeData;
};

struct shape shapes[MAX_SHAPE_NUM];
int shapeNum;

int main( int argc, char *argv[] )
{
	char inputType;
	double inputX, inputY, result, signCount;
	struct shape *pShape;
	struct point vector, vector2;
	int i, j, pointIndex, containCount;

	shapeNum = 0;
	pShape = shapes;
	while( 0 < scanf( " %c", &inputType ) )
	{
		if( 'r' == inputType )
		{
			pShape->shapeType = SHAPE_RECTANGLE;
			scanf( " %lf %lf %lf %lf", &pShape->shapeData.rectangle.topLeft.x,
									&pShape->shapeData.rectangle.topLeft.y,
									&pShape->shapeData.rectangle.bottomRight.x,
									&pShape->shapeData.rectangle.bottomRight.y );
		}else if( 'c' == inputType )
		{
			pShape->shapeType = SHAPE_CIRCLE;
			scanf( " %lf %lf %lf", &pShape->shapeData.circle.center.x,
								&pShape->shapeData.circle.center.y,
								&pShape->shapeData.circle.radius );
			/*
				Double up radius directly so we don't need to apply sqrt while
				comparing distance from point to center
			*/
			pShape->shapeData.circle.radius *= pShape->shapeData.circle.radius;
		}else if( 't' == inputType )
		{
			pShape->shapeType = SHAPE_TRIANGLE;
			scanf( " %lf %lf %lf %lf %lf %lf", &pShape->shapeData.triangle.vertix[0].x,
											&pShape->shapeData.triangle.vertix[0].y,
											&pShape->shapeData.triangle.vertix[1].x,
											&pShape->shapeData.triangle.vertix[1].y,
											&pShape->shapeData.triangle.vertix[2].x,
											&pShape->shapeData.triangle.vertix[2].y );
			pShape->shapeData.triangle.vertix[3].x = pShape->shapeData.triangle.vertix[0].x;
			pShape->shapeData.triangle.vertix[3].y = pShape->shapeData.triangle.vertix[0].y;
		}else if( '*' == inputType )
		{
			break;
		}else
		{
			printf( "Error input format\n" );
			break;
		}
		shapeNum++;
		pShape++;
	}
	
	pointIndex = 0;
	while( 2 == scanf( " %lf %lf", &inputX, &inputY ) )
	{
		pointIndex++;
		if( inputX == 9999.9 && inputY == 9999.9 )
		{
			break;
		}
/*
printf( "Point (%lf, %lf)\n", inputX, inputY );
*/
		containCount = 0;
		for( i = 0, pShape = shapes; i < shapeNum; i++, pShape++ )
		{
			if( SHAPE_RECTANGLE == pShape->shapeType )
			{
/*
printf( "Rectangle(%d) : x : (%lf - %lf) y : (%lf - %lf)\n", i+1,
			pShape->shapeData.rectangle.topLeft.x,
			pShape->shapeData.rectangle.bottomRight.x,
			pShape->shapeData.rectangle.bottomRight.y,
			pShape->shapeData.rectangle.topLeft.y );
*/
				if( inputX > pShape->shapeData.rectangle.topLeft.x &&
					inputX < pShape->shapeData.rectangle.bottomRight.x &&
					inputY > pShape->shapeData.rectangle.bottomRight.y &&
					inputY < pShape->shapeData.rectangle.topLeft.y )
				{
					printf( "Point %d is contained in figure %d\n", pointIndex, i+1 );
					containCount++;
				}
			}else if( SHAPE_CIRCLE == pShape->shapeType )
			{
/*
printf( "Circle(%d) : %lf %lf %lf\n", i+1,
			pShape->shapeData.circle.center.x,
			pShape->shapeData.circle.center.y,
			pShape->shapeData.circle.radius );
*/
				vector.x = inputX - pShape->shapeData.circle.center.x;
				vector.y = inputY - pShape->shapeData.circle.center.y;
				if( ((vector.x * vector.x) + (vector.y * vector.y)) < pShape->shapeData.circle.radius )
				{
					printf( "Point %d is contained in figure %d\n", pointIndex, i+1 );
					containCount++;
				}
			}else if( SHAPE_TRIANGLE == pShape->shapeType )
			{
/*
printf( "Triangle(%d) : (%lf, %lf) (%lf, %lf) (%lf, %lf) (%lf, %lf)\n", i+1,
			pShape->shapeData.triangle.vertix[0].x,
			pShape->shapeData.triangle.vertix[0].y,
			pShape->shapeData.triangle.vertix[1].x,
			pShape->shapeData.triangle.vertix[1].y,
			pShape->shapeData.triangle.vertix[2].x,
			pShape->shapeData.triangle.vertix[2].y,
			pShape->shapeData.triangle.vertix[3].x,
			pShape->shapeData.triangle.vertix[3].y );
*/
				signCount = 0;
				for( j = 0; j < 3; j++ )
				{
					/*
						The algorithm comes from http://nanyecehui.blog.163.com/blog/static/191820012011278442740/
					*/
					vector.x = pShape->shapeData.triangle.vertix[j].x - inputX;
					vector.y = pShape->shapeData.triangle.vertix[j].y - inputY;
					
					vector2.x = pShape->shapeData.triangle.vertix[j+1].x - inputX;
					vector2.y = pShape->shapeData.triangle.vertix[j+1].y - inputY;
					
					result = vector2.x * vector.y - vector.x * vector2.y;
/*
printf( "Result %d of (%lf, %lf) with line (%lf, %lf)-(%lf, %lf) is %lf\n",
			j+1, inputX, inputY,
			pShape->shapeData.triangle.vertix[j].x, pShape->shapeData.triangle.vertix[j].y,
			pShape->shapeData.triangle.vertix[j+1].x, pShape->shapeData.triangle.vertix[j+1].y,
			result );
*/
					/* result == 0 indicates point is on edge, use small numbers other than 0 is to solve computer calculation bias issue */
					if( result >= -0.00000001 && result <= 0.00000001 )
					{
						break;
					}else if( result > 0.00000001 )
					{
						signCount++;
					}else if ( result < -0.00000001 )
					{
						signCount--;
					}
				}
				if( signCount == 3 || signCount == -3 )
				{
					printf( "Point %d is contained in figure %d\n", pointIndex, i+1 );
					containCount++;
				}
			}
		}
		if( 0 == containCount )
		{
			printf( "Point %d is not contained in any figure\n", pointIndex );
		}
	}
	
	return 0;
}
