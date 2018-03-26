#ifndef WINDOW_H
#define WINDOW_H

#include <qwt/qwt_thermo.h>
#include <qwt/qwt_knob.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>

#include "../../../interfaces/adc/MCP3008.h"

#include <QBoxLayout>

// #include "adcreader.h"

// class definition 'Window'
class Window : public QWidget
{
	// must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class
	Q_OBJECT

public:
	Window(); // default constructor - called when a Window is declared without arguments

	~Window();

	void timerEvent( QTimerEvent * );

public slots:
	void setGain(double gain);

// internal variables for the window class
private:
	QwtPlot      *plot1;
	QwtPlotCurve *curve1;
	QwtPlot      *plot2;
	QwtPlotCurve *curve2;
	QwtPlot      *plot3;
	QwtPlotCurve *curve3;
	QwtPlot      *plot4;
	QwtPlotCurve *curve4;
	

	// layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
	QVBoxLayout  *vLayout1;  // vertical layout
	QVBoxLayout  *vLayout2;  // vertical layout
	QHBoxLayout  *hLayout;  // horizontal layout
	
	// adc
	MCP3008 *adc;

	static const int plotDataSize = 100;

	// data arrays for the plot
	double xData[plotDataSize];
	double yData1[plotDataSize];
	double yData2[plotDataSize];
	double yData3[plotDataSize];
	double yData4[plotDataSize];

	double gain;
	int count;

//	ADCreader *adcreader;
};

#endif // WINDOW_H
