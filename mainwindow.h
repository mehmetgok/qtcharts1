#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

#include "clsChrono.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;


    int k;

     QLineSeries *seriesV;
     QLineSeries *seriesI;

     QVector<QPointF> pointsV;
     QVector<QPointF> pointsI;

     QValueAxis *axisYV;
     QValueAxis *axisYI;

     QValueAxis *axisX;

     double angle;
     double sin_angleV;
     double sin_angleI;

     QChart *chart;

     clsChrono krono;

};

#endif // MAINWINDOW_H
