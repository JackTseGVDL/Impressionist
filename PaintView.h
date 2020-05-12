//
// paintview.h
//
// The header file for painting view of the input images
//

#ifndef PAINTVIEW_H
#define PAINTVIEW_H

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include "OriginalView.h"


class ImpressionistDoc;


class PaintView : public Fl_Gl_Window {
public:
	PaintView(int x, int y, int w, int h, const char* l);
	void draw();
	int handle(int event);

	void refresh();
	void resizeWindow(int width, int height);
	void SaveCurrentContent();
	void RestoreContent();

	void setOriginalView(OriginalView *view);

	// force action
	void forceBrushMove(int x, int y);

	ImpressionistDoc *m_pDoc;

private:
	GLvoid* m_pPaintBitstart;
	int		m_nDrawWidth,
			m_nDrawHeight,
			m_nStartRow, 
			m_nEndRow,
			m_nStartCol, 
			m_nEndCol,
			m_nWindowWidth, 
			m_nWindowHeight;
	OriginalView* m_originalView;

	// stroke config
	Point m_strokeStart;
	void getStrokeAngle_brushBegin(const Point point);
	int  getStrokeAngle_brushDrag(const Point point);
	int  getStrokeAngle_gradient(const Point point);
};

#endif