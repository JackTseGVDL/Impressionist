#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include "Brush_Circle.h"


extern float frand();


CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name) {

}


void CircleBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	// config
	int size = pDoc->getBrushSize();
	glPointSize((float)size);

	// draw
	BrushMove(source, target);
}


void CircleBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	// check if the doc existed or not
	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove    document is NULL\n");
		return;
	}

	// config
	SetColor(source);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	// draw
	glBegin(GL_POINTS);
	glVertex2d(target.x, target.y);
	glEnd();
}


void CircleBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}