//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "Brush_Point.h"


extern float frand();


PointBrush::PointBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name){
}


void PointBrush::BrushBegin( const Point source, const Point target ) {
	ImpressionistDoc* pDoc = GetDocument();
	BrushMove( source, target );
}


void PointBrush::BrushMove( const Point source, const Point target ) {
	ImpressionistDoc* pDoc = GetDocument();

	if ( pDoc == NULL ) {
		printf( "PointBrush::BrushMove  document is NULL\n" );
		return;
	}

	// config
	int size = pDoc->getBrushSize();
	glPointSize((float)size);
	SetColor(source);
	glDisable(GL_POINT_SMOOTH);

	// draw
	glBegin(GL_POINTS);
	glVertex2d(target.x, target.y);
	glEnd();
}


void PointBrush::BrushEnd( const Point source, const Point target ) {
	// do nothing so far
}

