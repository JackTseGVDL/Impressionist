#ifndef BRUSH_KERNEL_H
#define BRUSH_KERNEL_H


#include "ImpBrush.h"


class KernelBrush : public ImpBrush {
public:
	KernelBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin	(const Point source, const Point target);
	void BrushMove	(const Point source, const Point target);
	void BrushEnd	(const Point source, const Point target);

	char* BrushName();

	void setKernel(float* kernel);

private:
	float kernel[9];
};


#endif
