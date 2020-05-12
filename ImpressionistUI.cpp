//
// impressionistUI.h
//
// The user interface part for the program.
//


#include <FL/fl_ask.h>

#include <math.h>
#include <cstdlib>

#include "impressionistUI.h"
#include "impressionistDoc.h"

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the 
project.  You can copy and paste these into your code and then change them to 
make them look how you want.  Descriptions for all of the widgets here can be found 
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------
	
	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions
		
		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
    m_mainWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v) 
	{	
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
    mySlider->labelfont(FL_COURIER);
    mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}
	

//------------Choice---------------------------------------
	
	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);
	
	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------
	
	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

    //---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/


//------------------------------------- Help Functions -------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o) {
	return ( (ImpressionistUI*)(o->parent()->user_data()) );
}


//--------------------------------- Callback Functions --------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) {
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}


void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) {
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp" );
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}


void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}


void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) {
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_Dialog_brush->hide();
	// whoami(o)->m_Dialog_filter->hide();
}


void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) {
	fl_message("Impressionist FLTK version for CS341, Spring 2002");
}


// callback: menu - main
void ImpressionistUI::cb_Menu_Main_brush(Fl_Menu_* o, void* v) {
	whoami(o)->m_Dialog_brush->show();
}


void ImpressionistUI::cb_Menu_Main_filter(Fl_Menu_* o, void* v) {
	whoami(o)->m_Dialog_filter->show();
}


// callback: choice
void ImpressionistUI::cb_Choice_brushType(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	int type = (int)v;
	pDoc->setBrushType(type);
	pUI->set_slider_active_state(type);
}


void ImpressionistUI::cb_Choice_strokeDir(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	int type = (int)v;
	pDoc->setStrokeDir(type);
}


// callback: slider
void ImpressionistUI::cb_Slider_brushSize(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();
	int value = int(((Fl_Slider*)o)->value());
	pDoc->setBrushSize(value);
}


void ImpressionistUI::cb_Slider_lineWidth(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();
	int value = int(((Fl_Slider*)o)->value());
	pDoc->setBrushLineWidth(value);
}


void ImpressionistUI::cb_Slider_lineAngle(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();
	int value = int(((Fl_Slider*)o)->value());
	pDoc->setBrushLineAngle(value);
}


void ImpressionistUI::cb_Slider_alpha(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();
	float value = float(((Fl_Slider*)o)->value());
	pDoc->setBrushAlpha(value);
}


// button: clear canvas
void ImpressionistUI::cb_Button_clearCanvas(Fl_Widget* o, void* v) {
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	pDoc->clearCanvas();
}


// button: apply filter
void ImpressionistUI::cb_Button_applyFilter(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();
	float kernel[9];

	for (int i = 0; i < 9; i++) {
		kernel[i] = (float)(atof(pUI->m_Input_filterInput[i]->value()));
		if (pUI->m_LightButton_normalFilter->value()) kernel[i] /= 9;
	}

	pDoc->setConvolutionKernel(kernel, 9);
	pDoc->processConvolution();
	return;
}


// light button: normal filter
void ImpressionistUI::cb_LightButton_normalFilter(Fl_Widget* o, void* v) {

}


//---------------------------------- per instance functions --------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument() {
	return m_pDoc;
}


void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}


void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
	m_origView->size(w,h);
}


void ImpressionistUI::setDocument(ImpressionistDoc* doc) {
	m_pDoc = doc;
	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;

	// init slider based on doc
	refreshSlider();
	set_slider_active_state(doc->getBrushType());
}


void ImpressionistUI::refreshSlider() {
	m_Slider_brushSize->value(m_pDoc->getBrushSize());
	m_Slider_lineWidth->value(m_pDoc->getBrushLineWidth());
	m_Slider_lineAngle->value(m_pDoc->getBrushLineAngle());
	m_Slider_alpha->value(m_pDoc->getBrushAlpha());
}


// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_Menu_Main_brush },
		// { "&Filter...",     FL_ALT + 'f', (Fl_Callback *)ImpressionistUI::cb_Menu_Main_filter },
		{ "&Clear Canvas",  FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas, 0, FL_MENU_DIVIDER },
		
		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
		{ 0 },

	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
		{ 0 },

	{ 0 }
};


// Menu: brush type
Fl_Menu_Item ImpressionistUI::menu_brushType[NUM_BRUSH_TYPE + 1] = {
	{"Points",				FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_Choice_brushType, (void *)BRUSH_POINTS},
	{"Lines",				FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_Choice_brushType, (void *)BRUSH_LINES},
	{"Circles",				FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_Choice_brushType, (void *)BRUSH_CIRCLES},
	{"Scattered Points",	FL_ALT+'q', (Fl_Callback *)ImpressionistUI::cb_Choice_brushType, (void *)BRUSH_SCATTERED_POINTS},
	{"Scattered Lines",		FL_ALT+'m', (Fl_Callback *)ImpressionistUI::cb_Choice_brushType, (void *)BRUSH_SCATTERED_LINES},
	{"Scattered Circles",	FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_Choice_brushType, (void *)BRUSH_SCATTERED_CIRCLES},
	{0}
};


// Menu: stroke direction
Fl_Menu_Item ImpressionistUI::menu_strokeDir[NUM_STROKE_DIR + 1] = {
	{"Slider/Right Mouse",	FL_ALT + 's', (Fl_Callback*)ImpressionistUI::cb_Choice_strokeDir, (void*)STROKE_SLIDER},
	{"Gradient",			FL_ALT + 'g', (Fl_Callback*)ImpressionistUI::cb_Choice_strokeDir, (void*)STROKE_GRADIENT},
	{"Brush Direction",		FL_ALT + 'b', (Fl_Callback*)ImpressionistUI::cb_Choice_strokeDir, (void*)STROKE_BRUSH},
	{0}
};


//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "Impressionist");
	m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
	// install menu bar
	m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
	m_menubar->menu(menuitems);

	// Create a group that will hold two sub windows inside the main
	// window
	Fl_Group* group = new Fl_Group(0, 25, 600, 275);

	// install paint view window
	m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
	m_paintView->box(FL_DOWN_FRAME);

	// install original view window
	m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
	m_origView->box(FL_DOWN_FRAME);
	m_origView->deactivate();

	// connect paint view and original view
	m_paintView->setOriginalView(m_origView);

	group->end();
	Fl_Group::current()->resizable(group);
    m_mainWindow->end();

	// dialog: brush
	m_Dialog_brush = new Fl_Window(400, 325, "Brush Dialog");

	// choice: brush type
	m_Choice_brushType = new Fl_Choice(50, 10, 150, 25,"&Brush");
	m_Choice_brushType->user_data((void*)(this));
	m_Choice_brushType->menu(menu_brushType);
	m_Choice_brushType->callback(cb_Choice_brushType);

	// choice: stroke direction
	m_Choice_strokeDir = new Fl_Choice(50, 45, 150, 25, "&Stroke Direction");
	m_Choice_strokeDir->user_data((void*)(this));
	m_Choice_strokeDir->menu(menu_strokeDir);
	m_Choice_strokeDir->callback(cb_Choice_strokeDir);

	// button: clear canvas
	m_Button_clearCanvas = new Fl_Button(240, 10, 150, 25, "&Clear Canvas");
	m_Button_clearCanvas->user_data((void*)(this));
	m_Button_clearCanvas->callback(cb_Button_clearCanvas);

	// slider: brush size
	m_Slider_brushSize = new Fl_Value_Slider(10, 80, 300, 20, "Size");
	m_Slider_brushSize->user_data((void*)(this));
	m_Slider_brushSize->type(FL_HOR_NICE_SLIDER);
    m_Slider_brushSize->labelfont(FL_COURIER);
    m_Slider_brushSize->labelsize(12);
	m_Slider_brushSize->minimum(1);
	m_Slider_brushSize->maximum(40);
	m_Slider_brushSize->step(1);
	m_Slider_brushSize->value(1);
	m_Slider_brushSize->align(FL_ALIGN_RIGHT);
	m_Slider_brushSize->callback(cb_Slider_brushSize);

	// slider: line width
	m_Slider_lineWidth = new Fl_Value_Slider(10, 80 + 1 * 30, 300, 20, "Line Width");
	m_Slider_lineWidth->user_data((void*)(this));
	m_Slider_lineWidth->type(FL_HOR_NICE_SLIDER);
	m_Slider_lineWidth->labelfont(FL_COURIER);
	m_Slider_lineWidth->labelsize(12);
	m_Slider_lineWidth->minimum(1);
	m_Slider_lineWidth->maximum(40);
	m_Slider_lineWidth->step(1);
	m_Slider_lineWidth->value(1);
	m_Slider_lineWidth->align(FL_ALIGN_RIGHT);
	m_Slider_lineWidth->callback(cb_Slider_lineWidth);

	// slider: line angle
	m_Slider_lineAngle = new Fl_Value_Slider(10, 80 + 2 * 30, 300, 20, "Line Angle");
	m_Slider_lineAngle->user_data((void*)(this));
	m_Slider_lineAngle->type(FL_HOR_NICE_SLIDER);
	m_Slider_lineAngle->labelfont(FL_COURIER);
	m_Slider_lineAngle->labelsize(12);
	m_Slider_lineAngle->minimum(0);
	m_Slider_lineAngle->maximum(359);
	m_Slider_lineAngle->step(1);
	m_Slider_lineAngle->value(0);
	m_Slider_lineAngle->align(FL_ALIGN_RIGHT);
	m_Slider_lineAngle->callback(cb_Slider_lineAngle);

	// slider: alpha
	m_Slider_alpha = new Fl_Value_Slider(10, 80 + 3 * 30, 300, 20, "Alpha");
	m_Slider_alpha->user_data((void*)(this));
	m_Slider_alpha->type(FL_HOR_NICE_SLIDER);
	m_Slider_alpha->labelfont(FL_COURIER);
	m_Slider_alpha->labelsize(12);
	m_Slider_alpha->minimum(0.00f);
	m_Slider_alpha->maximum(01.00f);
	m_Slider_alpha->step(0.01f);
	m_Slider_alpha->value(0.00f);
	m_Slider_alpha->align(FL_ALIGN_RIGHT);
	m_Slider_alpha->callback(cb_Slider_alpha);

	// light button: edge clipping
	m_LightButton_edgeClipping = new Fl_Light_Button(10, 80 + 4 * 30, 150, 25, "&Edge Clipping");
	m_LightButton_edgeClipping->user_data((void*)(this));

    m_Dialog_brush->end();

	// dialog: filter
	//m_Dialog_filter = new Fl_Window(400, 325, "Filter Dialog");

	// button: apply filter
	/*m_Button_clearCanvas = new Fl_Button(10, 10, 100, 25, "&Apply Filter");
	m_Button_clearCanvas->user_data((void*)(this));
	m_Button_clearCanvas->callback(cb_Button_applyFilter);*/

	// light button: normal filter
	/*m_LightButton_normalFilter = new Fl_Light_Button(135, 10, 100, 25, "Normalize");
	m_LightButton_normalFilter->user_data((void*)(this));
	m_LightButton_normalFilter->callback(cb_LightButton_normalFilter);*/

	// input: filter input
	// currently the size of filter can only be 3 * 3
	/*for (int i = 0; i < 9; i++) {
		m_Input_filterInput[i] = new Fl_Input(10 + (i % 3) * 35, 45 + (i / 3) * 35, 25, 25);
		m_Input_filterInput[i]->user_data((void*)(this));
		m_Input_filterInput[i]->value("1");
	}

	m_Dialog_filter->end();*/
}


// Helper
void ImpressionistUI::set_slider_active_state(int type) {
	switch (type) {
	case BRUSH_POINTS:
		m_Choice_strokeDir->deactivate();
		m_Slider_brushSize->activate();
		m_Slider_lineWidth->deactivate();
		m_Slider_lineAngle->deactivate();
		break;

	case BRUSH_LINES:
		m_Choice_strokeDir->activate();
		m_Slider_brushSize->activate();
		m_Slider_lineWidth->activate();
		m_Slider_lineAngle->activate();
		break;

	case BRUSH_CIRCLES:
		m_Choice_strokeDir->deactivate();
		m_Slider_brushSize->activate();
		m_Slider_lineWidth->deactivate();
		m_Slider_lineAngle->deactivate();
		break;

	case BRUSH_SCATTERED_POINTS:
		m_Choice_strokeDir->deactivate();
		m_Slider_brushSize->activate();
		m_Slider_lineWidth->deactivate();
		m_Slider_lineAngle->deactivate();
		break;

	case BRUSH_SCATTERED_LINES:
		m_Choice_strokeDir->activate();
		m_Slider_brushSize->activate();
		m_Slider_lineWidth->activate();
		m_Slider_lineAngle->activate();
		break;

	case BRUSH_SCATTERED_CIRCLES:
		m_Choice_strokeDir->deactivate();
		m_Slider_brushSize->activate();
		m_Slider_lineWidth->deactivate();
		m_Slider_lineAngle->deactivate();
		break;
	};
}
