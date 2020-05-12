#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include "Brush_Line.h"


extern float frand();


LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name) {

}


void LineBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc *pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	BrushMove(source, target);
}


void LineBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	// check if the doc existed or not
	if (pDoc == NULL) {
		printf("LineBrush::BrushMove    document is NULL\n");
		return;
	}

	// get size
	int size = pDoc->getBrushSize();
	int width = pDoc->getBrushLineWidth();
	int angle = pDoc->getBrushLineAngle();
	SetColor(source);

	// draw
	// verison 1
	// glBegin(GL_LINE_STRIP);
	// SetColor(source);
	// glVertex2i(target.x - size / 2, target.y);
	// glVertex2i(target.x + size / 2, target.y);
	
	// version 2
	// glBegin(GL_POLYGON);
	// glVertex2i(target.x - size / 2, target.y - width / 2);
	// glVertex2i(target.x + size / 2, target.y - width / 2);
	// glVertex2i(target.x + size / 2, target.y + width / 2 + 1);
	// glVertex2i(target.x - size / 2, target.y + width / 2 + 1);

	// verion 3
	glPushMatrix();
	glTranslatef(target.x, target.y, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	
	glBegin(GL_POLYGON);
	glVertex2i(- size / 2, - width / 2);
	glVertex2i(+ size / 2, - width / 2);
	glVertex2i(+ size / 2, + width / 2 + 1);
	glVertex2i(- size / 2, + width / 2 + 1);

	glEnd();
	glPopMatrix();
}


void LineBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}
