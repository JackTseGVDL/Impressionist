// 
// impressionistDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//

#include <FL/fl_ask.H>

#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "ImpBrush.h"

// Include individual brush headers here.
#include "Brush_Point.h"
#include "Brush_Line.h"
#include "Brush_Circle.h"
#include "Brush_ScatteredPoint.h"
#include "Brush_ScatteredLine.h"
#include "Brush_ScatteredCircle.h"

#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

ImpressionistDoc::ImpressionistDoc() 
{
	// Set NULL image name as init. 
	m_imageName[0]	='\0';	

	m_nWidth		= -1;
	m_ucBitmap		= NULL;
	m_ucPainting	= NULL;

	// init brush attribute
	m_brushType = 0;
	m_brushSize = 10;
	m_lineWidth = 1;
	m_lineAngle = 0;
	m_strokeDir = 0;
	m_alpha = 1.00f;

	// create one instance of each brush
	ImpBrush::c_nBrushCount	= NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes	= new ImpBrush* [ImpBrush::c_nBrushCount];

	ImpBrush::c_pBrushes[BRUSH_POINTS]	= new PointBrush( this, "Points" );

	// brush
	ImpBrush::c_pBrushes[BRUSH_LINES]				= new LineBrush( this, "Lines" );
	ImpBrush::c_pBrushes[BRUSH_CIRCLES]				= new CircleBrush( this, "Circles" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS]	= new ScatteredPointBrush( this, "Scattered Points" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]		= new ScatteredLineBrush( this, "Scattered Lines" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES]	= new ScatteredCircleBrush( this, "Scattered Circles" );

	// convolution
	// for (int i = 0; i < 9; i++) m_kernel[i] = 0;
	// for (int i = 0; i < 6; i++) m_convolutionBuf[i] = 0;
	// Graphic_Convolution_init(&m_convolutor);
	// Graphic_Convolution_setBuffer(&m_convolutor, m_convolutionBuf, 6);
	// Graphic_Convolution_setMM(&m_convolutor, (void*)this);
	// Graphic_Convolution_setOps(&m_convolutor, Ops_Convolution_get, Ops_Convolution_set);

	// make one of the brushes current
	m_pCurrentBrush	= ImpBrush::c_pBrushes[0];

}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui) {
	m_pUI	= ui;
}


char* ImpressionistDoc::getImageName() {
	return m_imageName;
}


// getter: brush attribute
int ImpressionistDoc::getBrushSize() {
	return m_brushSize;
}


int ImpressionistDoc::getBrushLineWidth() {
	return m_lineWidth;
}


int ImpressionistDoc::getBrushLineAngle() {
	return m_lineAngle;
}


float ImpressionistDoc::getBrushAlpha() {
	return m_alpha;
}


int ImpressionistDoc::getBrushType() {
	return m_brushType;
}


int ImpressionistDoc::getStrokeDir() {
	return m_strokeDir;
}


// setter: brush attribute
void ImpressionistDoc::setBrushSize(int size) {
	m_brushSize = size;
}


void ImpressionistDoc::setBrushLineWidth(int width) {
	m_lineWidth = width;
}


void ImpressionistDoc::setBrushLineAngle(int angle) {
	// if (angle < 0) angle = 0;
	// if (angle > 359) angle = 359;
	m_lineAngle = angle;
	m_pUI->refreshSlider();
}


void ImpressionistDoc::setBrushAlpha(float alpha) {
	m_alpha = alpha;
}


void ImpressionistDoc::setBrushType(int type) {
	m_brushType = type;
	m_pCurrentBrush = ImpBrush::c_pBrushes[type];
}


void ImpressionistDoc::setStrokeDir(int dir) {
	m_strokeDir = dir;
}


//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(char *iname) {
	// try to open the image to read
	unsigned char*	data;
	int				width, 
					height;

	if ( (data=readBMP(iname, width, height))==NULL ) 
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	// reflect the fact of loading the new image
	m_nWidth		= width;
	m_nPaintWidth	= width;
	m_nHeight		= height;
	m_nPaintHeight	= height;

	// release old storage
	if ( m_ucBitmap ) delete [] m_ucBitmap;
	if ( m_ucPainting ) delete [] m_ucPainting;

	m_ucBitmap		= data;

	// allocate space for draw view
	m_ucPainting	= new unsigned char [width*height*3];
	memset(m_ucPainting, 0, width*height*3);

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
								m_pUI->m_mainWindow->y(), 
								width*2, 
								height+25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);	
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);	
	m_pUI->m_paintView->refresh();


	return 1;
}


//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(char *iname) {
	writeBMP(iname, m_nPaintWidth, m_nPaintHeight, m_ucPainting);
	return 1;
}


//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas() {
	// Release old storage
	if ( m_ucPainting ) {
		delete [] m_ucPainting;

		// allocate space for draw view
		m_ucPainting	= new unsigned char [m_nPaintWidth*m_nPaintHeight*3];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight*3);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}
	
	return 0;
}


void ImpressionistDoc::setConvolutionKernel(float* src, int size) {
}


void ImpressionistDoc::processConvolution() {
	for (int x = 0; x < 100; x++) {
		m_pUI->m_paintView->forceBrushMove(x, 20);
	}
}


//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( int x, int y ) {
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nWidth ) 
		x = m_nWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nHeight ) 
		y = m_nHeight-1;

	return (GLubyte*)(m_ucBitmap + 3 * (y*m_nWidth + x));
}


//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( const Point p ) {
	return GetOriginalPixel( p.x, p.y );
}


//void ImpressionistDoc::Ops_Convolution_get(void* mm, uint8_t *dst, uint32_t size, int32_t x, int32_t y) {
//	ImpressionistDoc* pDoc = (ImpressionistDoc*)mm;
//	memcpy(dst, pDoc->GetOriginalPixel(x, y), 3);
//}
//
//
//void ImpressionistDoc::Ops_Convolution_set(void* mm, uint8_t *src, uint32_t size, int32_t x, int32_t y) {
//	ImpressionistDoc* pDoc = (ImpressionistDoc*)mm;
//
//	glBegin(GL_POINT);
//	glColor3ub(255, 0, 0);
//	glVertex2i(x, y);
//	glEnd();
//	glFlush();
//}
