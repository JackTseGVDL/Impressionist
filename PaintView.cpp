//
// paintview.cpp
//
// The code maintaining the painting view of the input images
//


#include <cmath>
#include "impressionist.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "paintview.h"
#include "ImpBrush.h"


#define LEFT_MOUSE_DOWN		1
#define LEFT_MOUSE_DRAG		2
#define LEFT_MOUSE_UP		3
#define RIGHT_MOUSE_DOWN	4
#define RIGHT_MOUSE_DRAG	5
#define RIGHT_MOUSE_UP		6


#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#define max(a, b)	( ( (a)>(b) ) ? (a) : (b) )
#endif

static int		eventToDo;
static int		isAnEvent=0;
static Point	coord;

PaintView::PaintView(int			x, 
					 int			y, 
					 int			w, 
					 int			h, 
					 const char*	l)
						: Fl_Gl_Window(x,y,w,h,l)
{
	m_nWindowWidth	= w;
	m_nWindowHeight	= h;

}


void PaintView::draw() {
	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_FRONT_AND_BACK);
	#endif // !MESA

	if(!valid()) {
		glClearColor(0.7f, 0.7f, 0.7f, 1.0);

		// We're only using 2-D, so turn off depth 
		glDisable(GL_DEPTH_TEST);
		ortho();
		glClear(GL_COLOR_BUFFER_BIT);
	}

	Point scrollpos;// = GetScrollPosition();
	scrollpos.x = 0;
	scrollpos.y	= 0;

	m_nWindowWidth	= w();
	m_nWindowHeight	= h();

	int drawWidth, drawHeight;
	drawWidth = min( m_nWindowWidth, m_pDoc->m_nPaintWidth );
	drawHeight = min( m_nWindowHeight, m_pDoc->m_nPaintHeight );

	int startrow = m_pDoc->m_nPaintHeight - (scrollpos.y + drawHeight);
	if (startrow < 0) startrow = 0;

	m_pPaintBitstart = m_pDoc->m_ucPainting + 3 * ((m_pDoc->m_nPaintWidth * startrow) + scrollpos.x);

	m_nDrawWidth	= drawWidth;
	m_nDrawHeight	= drawHeight;

	m_nStartRow		= startrow;
	m_nEndRow		= startrow + drawHeight;
	m_nStartCol		= scrollpos.x;
	m_nEndCol		= m_nStartCol + drawWidth;

	if (m_pDoc->m_ucPainting && !isAnEvent) RestoreContent();

	double angle_r, angle_d;
	int dis_x, dis_y;

	// set cursor
	Point cursor(coord.x + m_nStartCol, m_nEndRow - coord.y);
	m_originalView->setCursor(cursor);

	// draw according to the mouse event
	if (m_pDoc->m_ucPainting && isAnEvent) {

		// Clear it after processing.
		isAnEvent	= 0;	

		Point source( coord.x + m_nStartCol, m_nEndRow - coord.y );
		Point target( coord.x, m_nWindowHeight - coord.y );
		
		// This is the event handler
		switch (eventToDo) {

		case LEFT_MOUSE_DOWN:
			if (m_pDoc->getStrokeDir() == STROKE_GRADIENT)   m_pDoc->setBrushLineAngle(getStrokeAngle_gradient(source));
			else if (m_pDoc->getStrokeDir() == STROKE_BRUSH) getStrokeAngle_brushBegin(source);

			m_pDoc->m_pCurrentBrush->BrushBegin(source, target);
			break;

		case LEFT_MOUSE_DRAG:
			if (m_pDoc->getStrokeDir() == STROKE_GRADIENT)   m_pDoc->setBrushLineAngle(getStrokeAngle_gradient(source));
			else if (m_pDoc->getStrokeDir() == STROKE_BRUSH) {
				m_pDoc->setBrushLineAngle((getStrokeAngle_brushDrag(source) + 90) % 360);
				getStrokeAngle_brushBegin(source);
			}

			m_pDoc->m_pCurrentBrush->BrushMove(source, target);
			break;

		case LEFT_MOUSE_UP:
			if (m_pDoc->getStrokeDir() == STROKE_GRADIENT)   m_pDoc->setBrushLineAngle(getStrokeAngle_gradient(source));
			else if (m_pDoc->getStrokeDir() == STROKE_BRUSH) m_pDoc->setBrushLineAngle((getStrokeAngle_brushDrag(source) + 90) % 360);

			m_pDoc->m_pCurrentBrush->BrushEnd(source, target);
			SaveCurrentContent();
			RestoreContent();
			break;
		
		case RIGHT_MOUSE_DOWN:
			if (m_pDoc->getStrokeDir() != STROKE_SLIDER) break;
			getStrokeAngle_brushBegin(source);
			SaveCurrentContent();
			break;

		case RIGHT_MOUSE_DRAG:
			if (m_pDoc->getStrokeDir() != STROKE_SLIDER) break;
			
			// draw the red line
			RestoreContent();
			glBegin(GL_LINE_STRIP);
			glColor3ub(255, 0, 0);
			glVertex2i(m_strokeStart.x, m_strokeStart.y);
			glVertex2i(source.x, source.y);
			glEnd();

			// find the gradient and the angle
			m_pDoc->setBrushLineAngle(getStrokeAngle_brushDrag(source));
			break;

		case RIGHT_MOUSE_UP:
			if (m_pDoc->getStrokeDir() != STROKE_SLIDER) break;
			m_pDoc->setBrushLineAngle(getStrokeAngle_brushDrag(source));
			RestoreContent();
			break;

		default:
			printf("Unknown event!!\n");		
			break;
		}
	}

	glFlush();

	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_BACK);
	#endif // !MESA
}


int PaintView::handle(int event) {
	switch(event) {
	case FL_ENTER:
	    redraw();
		break;

	case FL_PUSH:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DOWN;
		else
			eventToDo=LEFT_MOUSE_DOWN;
		isAnEvent=1;
		redraw();
		break;

	case FL_DRAG:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DRAG;
		else
			eventToDo=LEFT_MOUSE_DRAG;
		isAnEvent=1;
		redraw();
		break;

	case FL_RELEASE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_UP;
		else
			eventToDo=LEFT_MOUSE_UP;
		isAnEvent=1;
		redraw();
		break;

	case FL_MOVE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		redraw();
		break;

	default:
		return 0;
		break;
	}

	return 1;
}


void PaintView::refresh() {
	redraw();
}


void PaintView::resizeWindow(int width, int height) {
	resize(x(), y(), width, height);
}


void PaintView::forceBrushMove(int x, int y) {
	coord.x = x;
	coord.y = y;
	eventToDo = LEFT_MOUSE_DRAG;
	isAnEvent = 1;
	draw();
}


void PaintView::SaveCurrentContent() {
	// Tell openGL to read from the front buffer when capturing
	// out paint strokes
	glReadBuffer(GL_FRONT);

	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei( GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	
	glReadPixels( 0, 
				  m_nWindowHeight - m_nDrawHeight, 
				  m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart );
}


void PaintView::RestoreContent() {
	glDrawBuffer(GL_BACK);

	glClear(GL_COLOR_BUFFER_BIT);

	glRasterPos2i( 0, m_nWindowHeight - m_nDrawHeight );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glPixelStorei( GL_UNPACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	glDrawPixels( m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart);

//	glDrawBuffer(GL_FRONT);
}


void PaintView::setOriginalView(OriginalView* view) {
	m_originalView = view;
}


// private
void PaintView::getStrokeAngle_brushBegin(const Point point) {
	m_strokeStart.x = point.x;
	m_strokeStart.y = point.y;
}


int PaintView::getStrokeAngle_brushDrag(const Point point) {
	double angle_r, angle_d;

	// calculate
	if (point.x - m_strokeStart.x == 0) {
		angle_d = point.y - m_strokeStart.y > 0 ? 90 : 270;
	}
	else {
		angle_r = atan((double)(point.y - m_strokeStart.y) / (double)(point.x - m_strokeStart.x));
		angle_d = (angle_r * 180.0f) / M_PI;

		// fix degree of the arctan
		if (point.x - m_strokeStart.x > 0) {
			if (point.y - m_strokeStart.y > 0) ;
			else							   angle_d = 360 + angle_d;
		}
		else {
			if (point.y - m_strokeStart.y > 0) angle_d = 180 + angle_d;
			else							   angle_d = 180 + angle_d;
		}
	}

	return (int)angle_d;
}


int PaintView::getStrokeAngle_gradient(const Point point) {
	int dis_x, dis_y;
	Point point_temp;
	GLubyte color_temp[3];
	int color_sum[2];

	// dis_x
	point_temp.x = point.x - 1;
	point_temp.y = point.y;
	memcpy(color_temp, m_pDoc->GetOriginalPixel(point_temp), 3);
	color_sum[0] = color_temp[0] + color_temp[1] + color_temp[2];

	point_temp.x = point.x + 1;
	point_temp.y = point.y;
	memcpy(color_temp, m_pDoc->GetOriginalPixel(point_temp), 3);
	color_sum[1] = color_temp[0] + color_temp[1] + color_temp[2];
	
	dis_x = color_sum[1] - color_sum[0];

	// dis_y
	point_temp.x = point.x;
	point_temp.y = point.y - 1;
	memcpy(color_temp, m_pDoc->GetOriginalPixel(point_temp), 3);
	color_sum[0] = color_temp[0] + color_temp[1] + color_temp[2];

	point_temp.x = point.x;
	point_temp.y = point.y + 1;
	memcpy(color_temp, m_pDoc->GetOriginalPixel(point_temp), 3);
	color_sum[1] = color_temp[0] + color_temp[1] + color_temp[2];

	dis_y = color_sum[1] - color_sum[0];

	// calculate
	double angle_r, angle_d;

	if (dis_x == 0) {
		angle_d = dis_y > 0 ? 90 : 270;
	}
	else {
		angle_r = atan(dis_y / dis_x);
		angle_d = (angle_r * 180.0f) / M_PI;

		// fix degree of the arctan
		if (dis_x > 0) {
			if (dis_y > 0);
			else		    angle_d = 360 + angle_d;
		}
		else {
			if (dis_y > 0)  angle_d = 180 + angle_d;
			else			angle_d = 180 + angle_d;
		}
	}

	return ((int)angle_d + 90 ) % 360;
}
