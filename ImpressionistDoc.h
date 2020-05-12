// 
// impressionistDoc.h
//
// header file for Doc 
//


#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h


#include "impressionist.h"
#include "bitmap.h"


class ImpressionistUI;


class ImpressionistDoc {
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int		loadImage(char *iname);			// called by the UI to load image
	int		saveImage(char *iname);			// called by the UI to save image


	int     clearCanvas();                  // called by the UI to clear the drawing canvas
	void	setSize(int size);				// set the UI size
	char*	getImageName();					// get the current image name

	// getter: brush attribute
	int		getBrushSize();
	int		getBrushLineWidth();
	int		getBrushLineAngle();
	float	getBrushAlpha();
	int		getBrushType();
	int		getStrokeDir();
	
	// setter: brush attribute
	void	setBrushSize(int size);
	void	setBrushLineWidth(int width);
	void	setBrushLineAngle(int angle);
	void	setBrushAlpha(float alpha);
	void	setBrushType(int type);
	void	setStrokeDir(int dir);

	// setter: convolution attribute
	void	setConvolutionKernel(float* src, int size);
	void	processConvolution();
	

// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth, 
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, 
					m_nPaintHeight;	
	// Bitmaps for original image and painting.
	unsigned char*	m_ucBitmap;
	unsigned char*	m_ucPainting;


	// The current active brush.
	ImpBrush*			m_pCurrentBrush;

	// brush attribute
	int m_brushType;
	int m_brushSize;
	int m_lineWidth;
	int m_lineAngle;
	float m_alpha;
	int m_strokeDir;
	int m_xgrad, m_ygrad;

	// convolution attribute
	// struct Convolutor m_convolutor;
	// float m_kernel[9];
	// uint8_t m_convolutionBuf[6];

	// ui
	ImpressionistUI*	m_pUI;

// Operations
public:
	GLubyte* GetOriginalPixel( int x, int y );
	GLubyte* GetOriginalPixel( const Point p );

	// static void Ops_Convolution_get(void* mm, uint8_t* dst, uint32_t size, int32_t x, int32_t y);
	// static void Ops_Convolution_set(void* mm, uint8_t* src, uint32_t size, int32_t x, int32_t y);


private:
	char			m_imageName[256];

};


extern void MessageBox(char *message);


#endif
