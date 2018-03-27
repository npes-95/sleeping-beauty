#ifndef WINDOW_H
#define WINDOW_H

#include <qwt/qwt_thermo.h>
#include <qwt/qwt_knob.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>

#include "../../../interfaces/adc/MCP3008.h"
#include "../../../interfaces/accelerometer/LIS3DH.h"

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

	// adc plots
	QwtPlot      *plot1_adc;
	QwtPlotCurve *curve1_adc;
	QwtPlot      *plot2_adc;
	QwtPlotCurve *curve2_adc;
	QwtPlot      *plot3_adc;
	QwtPlotCurve *curve3_adc;
	QwtPlot      *plot4_adc;
	QwtPlotCurve *curve4_adc;
	
	// accelerometer plot (plot XYZ data on same plot)
	QwtPlot      *plot_accel;
	QwtPlotCurve *curve_x_accel;
	QwtPlotCurve *curve_y_accel;
	QwtPlotCurve *curve_z_accel;
	

	// layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
	QVBoxLayout  *vLayout1;  // vertical layout
	QVBoxLayout  *vLayout2;  // vertical layout
	QVBoxLayout  *vLayout3;  // vertical layout
	QHBoxLayout  *hLayout;  // horizontal layout
	
	// adc (with pressure sensors connected)
	MCP3008 *adc;
	
	// accelerometer
	LIS3DH *accel;

	static const int plotDataSize = 100;

	// data arrays for the plot
	double xData[plotDataSize];
	double yData1[plotDataSize];
	double yData2[plotDataSize];
	double yData3[plotDataSize];
	double yData4[plotDataSize];
	double yData5[plotDataSize];
	double yData6[plotDataSize];
	double yData7[plotDataSize];


	double gain;
	int count;

//	ADCreader *adcreader;
};

#endif // WINDOW_H
