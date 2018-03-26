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
	}

	curve1 = new QwtPlotCurve;
	plot1 = new QwtPlot;
	plot1->setTitle("ADC Channel 1");
	curve2 = new QwtPlotCurve;
	plot2 = new QwtPlot;
	plot2->setTitle("ADC Channel 2");
	curve3 = new QwtPlotCurve;
	plot3 = new QwtPlot;
	plot3->setTitle("ADC Channel 3");
	curve4 = new QwtPlotCurve;
	plot4 = new QwtPlot;
	plot4->setTitle("ADC Channel 4");
	
	// make a plot curve from the data and attach it to the plot
	curve1->setSamples(xData, yData1, plotDataSize);
	curve1->attach(plot1);
	curve2->setSamples(xData, yData2, plotDataSize);
	curve2->attach(plot2);
	curve3->setSamples(xData, yData3, plotDataSize);
	curve3->attach(plot3);
	curve4->setSamples(xData, yData4, plotDataSize);
	curve4->attach(plot4);
	
	// measure 0-3v3
	plot1->setAxisScale(0, 0.0, 3.3);
	plot1->replot();
	plot1->show();
	plot2->setAxisScale(0, 0.0, 3.3);
	plot2->replot();
	plot2->show();
	plot3->setAxisScale(0, 0.0, 3.3);
	plot3->replot();
	plot3->show();
	plot4->setAxisScale(0, 0.0, 3.3);
	plot4->replot();
	plot4->show();
	
	// adc	
	adc = new MCP3008();


	// set up the layout - knob above thermometer
	vLayout1 = new QVBoxLayout;
	vLayout1->addWidget(plot1);
	vLayout1->addWidget(plot2);
	
	vLayout2 = new QVBoxLayout;
	vLayout2->addWidget(plot3);
	vLayout2->addWidget(plot4);	


	// plot to the left of knob and thermometer
	hLayout = new QHBoxLayout;
	hLayout->addLayout(vLayout1);
	hLayout->addLayout(vLayout2);

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
	double chan1 = (double)adc->readChannel(0) / (double)1024;
	double chan2 = (double)adc->readChannel(1) / (double)1024;
	double chan3 = (double)adc->readChannel(2) / (double)1024;
	double chan4 = (double)adc->readChannel(3) / (double)1024;

	// add the new input to the plot
	memmove( yData1, yData1+1, (plotDataSize-1) * sizeof(double) );
	yData1[plotDataSize-1] = chan1;
	curve1->setSamples(xData, yData1, plotDataSize);
	plot1->replot();
	
	// add the new input to the plot
	memmove( yData2, yData2+1, (plotDataSize-1) * sizeof(double) );
	yData2[plotDataSize-1] = chan2;
	curve2->setSamples(xData, yData2, plotDataSize);
	plot2->replot();
	
	// add the new input to the plot
	memmove( yData3, yData3+1, (plotDataSize-1) * sizeof(double) );
	yData3[plotDataSize-1] = chan3;
	curve3->setSamples(xData, yData3, plotDataSize);
	plot3->replot();
	
	// add the new input to the plot
	memmove( yData4, yData4+1, (plotDataSize-1) * sizeof(double) );
	yData4[plotDataSize-1] = chan4;
	curve4->setSamples(xData, yData4, plotDataSize);
	plot4->replot();
}


// this function can be used to change the gain of the A/D internal amplifier
void Window::setGain(double gain)
{
	// for example purposes just change the amplitude of the generated input
	this->gain = gain;
}
