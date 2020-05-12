#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include "Brush_ScatteredPoint.h"


extern float frand();
extern int irand(int max);


ScatteredPointBrush::ScatteredPointBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name) {

}



void ScatteredPointBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	BrushMove(source, target);
}


void ScatteredPointBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	// check if the doc existed or not
	if (pDoc == NULL) {
		printf("ScatteredPointBrush::BrushMove    document is NULL\n");
		return;
	}

	// config
	int size = pDoc->getBrushSize();
	glPointSize(1.00f);
	glDisable(GL_POINT_SMOOTH);

	// draw
	glBegin(GL_POINTS);

	int x, y;
	for (y = -size / 2; y < size / 2; y++) {
		for (x = -size / 2; x < size / 2; x++) {
			if (irand(2) == 0) continue;

			Point point(source.x + x, source.y + y);
			SetColor(point);
			glVertex2d((GLdouble)(target.x + x), (GLdouble)(target.y + y));

		}
	}

	glEnd();
}


void ScatteredPointBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}