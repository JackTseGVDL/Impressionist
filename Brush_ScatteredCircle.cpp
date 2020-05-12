#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include "Brush_ScatteredCircle.h"


extern float frand();
extern int irand(int max);


ScatteredCircleBrush::ScatteredCircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name) {

}


void ScatteredCircleBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	// config
	int size = pDoc->getBrushSize();
	glPointSize((float)size);

	// draw
	BrushMove(source, target);
}


void ScatteredCircleBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	// check if the doc existed or not
	if (pDoc == NULL) {
		printf("ScatteredCircleBrush::BrushMove    document is NULL\n");
		return;
	}

	// config
	SetColor(source);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	int size = pDoc->getBrushSize();
	int num = irand(3) + 1;

	// draw
	glBegin(GL_POINTS);

	int i, dis_x, dis_y;
	for (i = 0; i < num; i++) {
		dis_x = irand(size) - size / 2;
		dis_y = irand(size) - size / 2;
		glVertex2d(target.x + dis_x, target.y + dis_y);
	}

	glEnd();
}


void ScatteredCircleBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}