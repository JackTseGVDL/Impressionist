//
// impressionistUI.h
//
// The header file for the UI part
//

#ifndef ImpressionistUI_h
#define ImpressionistUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_file_chooser.H>		// FLTK file chooser
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>

#include "Impressionist.h"
#include "OriginalView.h"
#include "PaintView.h"

#include "ImpBrush.h"

class ImpressionistUI {
public:
	ImpressionistUI();

	// The FLTK widgets
	Fl_Window*			m_mainWindow;
	Fl_Menu_Bar*		m_menubar;
								
	PaintView*			m_paintView;
	OriginalView*		m_origView;

	// dialog
	Fl_Window* m_Dialog_brush;
	Fl_Window* m_Dialog_filter;

	// choice
	Fl_Choice*	m_Choice_brushType;
	Fl_Choice*	m_Choice_strokeDir;

	// slider
	Fl_Slider*	m_Slider_brushSize;
	Fl_Slider*	m_Slider_lineWidth;
	Fl_Slider*	m_Slider_lineAngle;
	Fl_Slider*	m_Slider_alpha;

	// button
	Fl_Button*  m_Button_clearCanvas;
	Fl_Button*	m_Button_applyFilter;
	
	// light button
	Fl_Light_Button* m_LightButton_normalFilter;
	Fl_Light_Button* m_LightButton_edgeClipping;

	// input
	Fl_Input* m_Input_filterInput[9];

	// light button list0

	// Member functions
	void				setDocument(ImpressionistDoc* doc);
	ImpressionistDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);

	void				refreshSlider();

private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

	// Static class members
	static Fl_Menu_Item		menuitems[];
	static Fl_Menu_Item		menu_brushType[NUM_BRUSH_TYPE + 1];
	static Fl_Menu_Item		menu_strokeDir[NUM_STROKE_DIR + 1];

	static ImpressionistUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 
	// static
	static void	cb_load_image(Fl_Menu_* o, void* v);
	static void	cb_save_image(Fl_Menu_* o, void* v);
	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void	cb_exit(Fl_Menu_* o, void* v);
	static void	cb_about(Fl_Menu_* o, void* v);

	static void cb_Menu_Main_brush(Fl_Menu_* o, void* v);
	static void cb_Menu_Main_filter(Fl_Menu_* o, void* v);

	static void	cb_Choice_brushType(Fl_Widget* o, void* v);
	static void cb_Choice_strokeDir(Fl_Widget* o, void* v);

	static void	cb_Slider_brushSize(Fl_Widget* o, void* v);
	static void cb_Slider_lineWidth(Fl_Widget* o, void* v);
	static void cb_Slider_lineAngle(Fl_Widget* o, void* v);
	static void cb_Slider_alpha(Fl_Widget* o, void* v);

	static void	cb_Button_clearCanvas(Fl_Widget* o, void* v);
	static void cb_Button_applyFilter(Fl_Widget* o, void* v);

	static void cb_LightButton_normalFilter(Fl_Widget* o, void* v);

	// Helper
	void set_slider_active_state(int type);
};

#endif
