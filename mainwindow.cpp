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

        angle = i*M_PI/180.0;

        sin_angleV = 9.0*cos(angle) + (qrand() % 3)/10.0;
        sin_angleI = 3.0*sin(angle) + (qrand() % 3)/10.0;

        pointsV[i].setX(angle);
        pointsV[i].setY(sin_angleV);

        pointsI[i].setX(angle);
        pointsI[i].setY(sin_angleI*0.5);
    }

    seriesV = new QLineSeries();
    seriesV->setUseOpenGL(true);
    seriesV->setPen(QPen("black"));

    seriesI = new QLineSeries();
    seriesI->setUseOpenGL(true);
    seriesI->setPen(QPen("red"));


// Alternatif kullanim sekli
 /*
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7.3, 4);
    series->append(10, 5);
    series->append(11, 3);

    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
*/


// Buna gerek kalmadı. replace yordamı ihtiyaç duyulan bellek
// alanını otomatik olarak ayarlıyor.

/*    for (int i=0;i<2000;i++)
    {
        qreal angle = i*M_PI/180.0;
        qreal sin_angle = 3*sin(angle);

        seriesV->append(angle, sin_angle);

        seriesI->append(angle, sin_angle*0.5);
    }
*/

    seriesV->replace(pointsV);
    seriesI->replace(pointsI);


    // Font for graph axes
    QFont font;
    font.setPixelSize(7);


    chart = new QChart();
    chart->legend()->hide();


    QValueAxis *axisX = new QValueAxis;
    // axisX->setTickCount(20);
    axisX->setLabelsFont(font);
 //   axisX->setRange(0.0, 2000.0);

    chart->addAxis(axisX, Qt::AlignBottom);


    axisYV = new QValueAxis;

    axisYV->setLabelsFont(font);
    axisYV->setLinePenColor(seriesV->pen().color());
    axisYV->setRange(-10.0, 10.0);

    chart->addSeries(seriesV);

    // Gerilim degerleri icin gereken Y- ekseni
    chart->addAxis(axisYV, Qt::AlignLeft);

    seriesV->attachAxis(axisX);
    seriesV->attachAxis(axisYV);

    // Akım degerleri icin gereken Y- ekseni
    axisYI = new QValueAxis;
    axisYI->setLabelsFont(font);

    chart->addSeries(seriesI);
    axisYI->setLinePenColor(seriesI->pen().color());

    axisYI->setRange(-3.0, 3.0);
    // axisY3->setGridLinePen((series2->pen()));


    chart->addAxis(axisYI, Qt::AlignRight);
    seriesI->attachAxis(axisX);
    seriesI->attachAxis(axisYI);

    // Eğer eksenler otomatik olarak ayarlanmaz ise
    // chart->createDefaultAxes();

    // chart->axisX()->setLabelsFont(font);
    // chart->axisY()->setLabelsFont(font);


    // We need performance
    ui->widget->setRenderHint(QPainter::Antialiasing, false);


    // chart->setTitle("Simple line chart example");
    ui->widget->setChart(chart);

}

MainWindow::~MainWindow()
{


    delete seriesV;
    delete seriesI;

    delete axisYI;
    delete axisYV;

    delete axisX;

    delete chart;

    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

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


    seriesV->replace(pointsV);
    seriesI->replace(pointsI);

    ui->lbTime->setText(QString::number(krono.getElapsed_us()) + tr(" us"));

  //  qDebug("Elapsed : %f", krono.getElapsed_us());

}


void MainWindow::on_pushButton_2_clicked()
{
     close();
}
