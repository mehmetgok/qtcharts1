/*
    - We subclass chartview to promote to
*/


#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts/QChartView>


QT_CHARTS_USE_NAMESPACE


class ChartView : public QChartView
{
public:
     ChartView(QWidget *parent = 0);
};

#endif // CHARTVIEW_H
