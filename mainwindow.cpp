#include "mainwindow.h"
#include "ui_mainwindow.h"

#define M_PI       3.14159265358979323846

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    k = 0;

    pointsV.resize(2000);
    pointsI.resize(2000);


    for (int i=0;i<2000;i++)
    {

        angle =i*M_PI/180.0;

        sin_angleV = 3*cos(angle) + (qrand() % 3)/10.0;
        sin_angleI = 3*sin(angle) + (qrand() % 3)/10.0;

        pointsV[i].setX(angle);
        pointsV[i].setY(sin_angleV);

        pointsI[i].setX(angle);
        pointsI[i].setY(sin_angleI*0.5);
    }





    series = new QLineSeries();
    series->setUseOpenGL(true);
    series->setPen(QPen("black"));



    series2 = new QLineSeries();
    series2->setUseOpenGL(true);
    series2->setPen(QPen("red"));



 /*   series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7.3, 4);
    series->append(10, 5);
    series->append(11, 3);

    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    */


    for (int i=0;i<2000;i++)
    {
        qreal angle = i*M_PI/180.0;
        qreal sin_angle = 3*sin(angle);

        series->append(angle, sin_angle);

        series2->append(angle, sin_angle*0.5);
    }

    // Font for graph axes
    QFont font;
    font.setPixelSize(7);


    chart = new QChart();
    chart->legend()->hide();


    QValueAxis *axisX = new QValueAxis;
    axisX->setTickCount(20);
    axisX->setLabelsFont(font);

    chart->addAxis(axisX, Qt::AlignBottom);


    QValueAxis *axisY = new QValueAxis;

     axisY->setLabelsFont(font);
    axisY->setLinePenColor(series->pen().color());

    chart->addSeries(series);

    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisX);
    series->attachAxis(axisY);


    QValueAxis *axisY3 = new QValueAxis;

    axisY3->setLabelsFont(font);

    chart->addSeries(series2);

     axisY3->setLinePenColor(series2->pen().color());

     axisY3->setRange(-3.0, 3.0);
    // axisY3->setGridLinePen((series2->pen()));


    chart->addAxis(axisY3, Qt::AlignRight);
    series2->attachAxis(axisX);
    series2->attachAxis(axisY3);


 //   chart->addSeries(series2);


    // You have to create this
//     chart->createDefaultAxes();






 //   chart->axisX()->setLabelsFont(font);
   // chart->axisY()->setLabelsFont(font);


// We need performance
  ui->widget->setRenderHint(QPainter::Antialiasing, false);


   // chart->setTitle("Simple line chart example");

    // QChartView *chartView = new QChartView(chart);

    ui->widget->setChart(chart);






}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{


   // QVector<QPointF> oldPoints = series->points();





    krono.startChrono();


    // Geri çek
    for (int i=0;i<1800;i++)
    {
        pointsV[i].setY(pointsV[i+200].y());
        pointsI[i].setY(pointsI[i+200].y());
    }

    for (int i=1800;i<2000;i++)
    {
        pointsV[i].setY(0.0);
        pointsI[i].setY(0.0);
    }




    series->replace(pointsV);

    series2->replace(pointsI);

    ui->lbTime->setText(QString::number(krono.getElapsed_us()));

  //  qDebug("Elapsed : %f", krono.getElapsed_us());

}

void MainWindow::on_actionQuit_triggered()
{

}

void MainWindow::on_pushButton_2_clicked()
{
     close();
}
