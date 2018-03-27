#include "window.h"
#include "adcreader.h"

#include <cmath>  // for sine stuff


Window::Window() : gain(5), count(0)
{

	// set up the initial plot data (0)
	for( int index=0; index<plotDataSize; ++index )
	{
		xData[index] = index;
		yData1[index] = 0;
		yData2[index] = 0;
		yData3[index] = 0;
		yData4[index] = 0;
		yData5[index] = 0;
		yData6[index] = 0;
		yData7[index] = 0;
	}
	
	// init adc plots
	curve1_adc = new QwtPlotCurve;
	plot1_adc = new QwtPlot;
	plot1_adc->setTitle("ADC Channel 1");
	curve2_adc = new QwtPlotCurve;
	plot2_adc = new QwtPlot;
	plot2_adc->setTitle("ADC Channel 2");
	curve3_adc = new QwtPlotCurve;
	plot3_adc = new QwtPlot;
	plot3_adc->setTitle("ADC Channel 3");
	curve4_adc = new QwtPlotCurve;
	plot4_adc = new QwtPlot;
	plot4_adc->setTitle("ADC Channel 4");
	
	// init accel plot and curves
	curve_x_accel = new QwtPlotCurve;
	curve_y_accel = new QwtPlotCurve;
	curve_z_accel = new QwtPlotCurve;
	
	plot_accel = new QwtPlot;
	plot_accel->setTitle("Accelerometer (XYZ)");
	
	// make a plot curve from the data and attach it to the plot
	curve1_adc->setSamples(xData, yData1, plotDataSize);
	curve1_adc->attach(plot1_adc);
	curve2_adc->setSamples(xData, yData2, plotDataSize);
	curve2_adc->attach(plot2_adc);
	curve3_adc->setSamples(xData, yData3, plotDataSize);
	curve3_adc->attach(plot3_adc);
	curve4_adc->setSamples(xData, yData4, plotDataSize);
	curve4_adc->attach(plot4_adc);
	
	curve_x_accel->setSamples(xData, yData5, plotDataSize);
	curve_x_accel->attach(plot_accel);
	curve_x_accel->setPen(Qt::red);
	curve_y_accel->setSamples(xData, yData6, plotDataSize);
	curve_y_accel->attach(plot_accel);
	curve_y_accel->setPen(Qt::green);
	curve_z_accel->setSamples(xData, yData7, plotDataSize);
	curve_z_accel->attach(plot_accel);
	curve_z_accel->setPen(Qt::blue);
	
	// measure 0-3v3
	plot1_adc->setAxisScale(0, 0.0, 3.3);
	plot1_adc->replot();
	plot1_adc->show();
	plot2_adc->setAxisScale(0, 0.0, 3.3);
	plot2_adc->replot();
	plot2_adc->show();
	plot3_adc->setAxisScale(0, 0.0, 3.3);
	plot3_adc->replot();
	plot3_adc->show();
	plot4_adc->setAxisScale(0, 0.0, 3.3);
	plot4_adc->replot();
	plot4_adc->show();
	plot_accel->setAxisScale(0, 0.0, 10);
	plot_accel->replot();
	plot_accel->show();
	
	// adc	
	adc = new MCP3008();
	
	// accelerometer
	accel = new LIS3DH();


	// set up the layout
	vLayout1 = new QVBoxLayout;
	vLayout1->addWidget(plot1_adc);
	vLayout1->addWidget(plot2_adc);
	
	vLayout2 = new QVBoxLayout;
	vLayout2->addWidget(plot3_adc);
	vLayout2->addWidget(plot4_adc);
	
	vLayout3 = new QVBoxLayout;
	vLayout3->addWidget(plot_accel);	


	// plot to the left of knob and thermometer
	hLayout = new QHBoxLayout;
	hLayout->addLayout(vLayout1);
	hLayout->addLayout(vLayout2);
	hLayout->addLayout(vLayout3);

	setLayout(hLayout);
	
	
	

	// This is a demo for a thread which can be
	// used to read from the ADC asynchronously.
	// At the moment it doesn't do anything else than
	// running in an endless loop and which prints out "tick"
	// every second.
	//adcreader = new ADCreader();
	//adcreader->start();
}

Window::~Window() {
	// tells the thread to no longer run its endless loop
	//adcreader->quit();
	// wait until the run method has terminated
	//adcreader->wait();
	//delete adcreader;
}

void Window::timerEvent( QTimerEvent * )
{
	double chan1_adc = (double)adc->readChannel(0) / (double)1024;
	double chan2_adc = (double)adc->readChannel(1) / (double)1024;
	double chan3_adc = (double)adc->readChannel(2) / (double)1024;
	double chan4_adc = (double)adc->readChannel(3) / (double)1024;
	
	double accel_x = (double)accel->readX() / (double)16384;
	double accel_y = (double)accel->readY() / (double)16384;
	double accel_z = (double)accel->readZ() / (double)16384;

	// add chan1 input to the plot
	memmove( yData1, yData1+1, (plotDataSize-1) * sizeof(double) );
	yData1[plotDataSize-1] = chan1_adc;
	curve1_adc->setSamples(xData, yData1, plotDataSize);
	plot1_adc->replot();
	
	// add chan2 input to the plot
	memmove( yData2, yData2+1, (plotDataSize-1) * sizeof(double) );
	yData2[plotDataSize-1] = chan2_adc;
	curve2_adc->setSamples(xData, yData2, plotDataSize);
	plot2_adc->replot();
	
	// add chan3 input to the plot
	memmove( yData3, yData3+1, (plotDataSize-1) * sizeof(double) );
	yData3[plotDataSize-1] = chan3_adc;
	curve3_adc->setSamples(xData, yData3, plotDataSize);
	plot3_adc->replot();
	
	// add chan4 input to the plot
	memmove( yData4, yData4+1, (plotDataSize-1) * sizeof(double) );
	yData4[plotDataSize-1] = chan4_adc;
	curve4_adc->setSamples(xData, yData4, plotDataSize);
	plot4_adc->replot();
	
	// add XYZ input to the plot
	memmove( yData5, yData5+1, (plotDataSize-1) * sizeof(double) );
	yData5[plotDataSize-1] = accel_x;
	curve_x_accel->setSamples(xData, yData5, plotDataSize);
	memmove( yData6, yData6+1, (plotDataSize-1) * sizeof(double) );
	yData6[plotDataSize-1] = accel_y;
	curve_y_accel->setSamples(xData, yData6, plotDataSize);
	memmove( yData7, yData7+1, (plotDataSize-1) * sizeof(double) );
	yData7[plotDataSize-1] = accel_z;
	curve_z_accel->setSamples(xData, yData7, plotDataSize);
	plot_accel->replot();
}


// this function can be used to change the gain of the A/D internal amplifier
void Window::setGain(double gain)
{
	// for example purposes just change the amplitude of the generated input
	this->gain = gain;
}
