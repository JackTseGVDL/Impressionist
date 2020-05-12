#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include "Brush_ScatteredLine.h"


extern float frand();
extern int irand(int max);


ScatteredLineBrush::ScatteredLineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name) {

}


void ScatteredLineBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	BrushMove(source, target);
}


void ScatteredLineBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	// check if the doc existed or not
	if (pDoc == NULL) {
		printf("ScatteredLineBrush::BrushMove    document is NULL\n");
		return;
	}

	// get config
	int size = pDoc->getBrushSize();
	int width = pDoc->getBrushLineWidth();
	int angle = pDoc->getBrushLineAngle();
	int num = irand(3) + 1;
	SetColor(source);

	// draw
	glPushMatrix();
	glTranslatef(target.x, target.y, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);

	glBegin(GL_POLYGON);

	int i, dis_left, dis_right;
	for (i = 0; i < num; i++) {
		dis_left = irand(size / 2);
		dis_right = irand(size / 2);

		glVertex2i(- size / 2 + dis_left, - width / 2);
		glVertex2i(+ size / 2 + dis_right, - width / 2);
		glVertex2i(+ size / 2 + dis_right, + width / 2 + 1);
		glVertex2i(- size / 2 + dis_left, + width / 2 + 1);
	}

	glEnd();
	glPopMatrix();
}


void ScatteredLineBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}