#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include "Brush_Kernel.h"


KernelBrush::KernelBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name) {

	// init kernel
	for (int i = 0; i < 9; i++) kernel[i] = 0.11f;
}


void KernelBrush::BrushBegin(const Point source, const Point target) {
	BrushMove(source, target);
}


void KernelBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();

	// kernel handling
	GLubyte *temp;
	int result[3];
	GLubyte* result_byte;

	result[0] = 0;
	result[1] = 0;
	result[2] = 0;

	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			temp = pDoc->GetOriginalPixel(source.x + x - 1, source.y + y - 1);
			result[0] += result[0] * kernel[y * 3 + x];
			result[1] += result[1] * kernel[y * 3 + x];
			result[2] += result[2] * kernel[y * 3 + x];	
		}
	}

	for (int i = 0; i < 3; i++) {
		if (result[i] < 0) result[i] = 0;
		if (result[i] > 255) result[i] = 255;
		result_byte[i] = (GLubyte)(result[i]);
	}

	// config
	glColor3ubv(result_byte);
	glDisable(GL_POINT_SMOOTH);

	// draw
	glBegin(GL_POINTS);
	glVertex2d(target.x, target.y);
	glEnd();
}


void KernelBrush::BrushEnd(const Point source, const Point target) {
	// do nothing
}


char* KernelBrush::BrushName() {
	return NULL;
}


void KernelBrush::setKernel(float* k) {
	for (int i = 0; i < 9; i++) kernel[i] = k[i];
}
