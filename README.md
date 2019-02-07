# qtcharts_sample
### Qt 5.7 Sample QtCharts Application

QtCharts bileşeni Qt çerçevesi ile grafik çizdirmek için kullanılan bir bileşen. Daha önce Qwt ya da QCustomPlot gibi farklı üçüncü parti bileşenleri kullanmış olanalar için yerel bir (native) bir çözüm olarak tercih edilebilir. Açık kaynak tarafında Digia tarafından GPL lisansı ile dağıtılmaktadır. Qt 5.7 ile sürümü ile açık kaynak dağıtımına eklenmiştir. OpenGL desteği etkin olarak kullanılabilmektedir.

Bu bileşeni kullanabilmek için ilk QtCreator **.pro** (proje) dosyasına **charts** kütüphanesini ekleniyor. 

`
QT += core gui charts
`

Daha sonra proje başlık dosyasına (header) gerekli kütüphane başlıklarını ve charts kullanımını aktifleştiren direktifi ekliyoruz.

```C++
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE
```

QtCreator tasarım ortamına qthcarts bileşen desteğini ekleyebilmek için aracı bir sınıf kullanıyoruz. Bu uygulamada bu sınıfın adı **ChartView** olarak seçilmiş olup sınıfa ait dosyalar proje ağacında yer almaktadır. Daha sonra QtCreator form tasarımı üzerine **widget** bileşeni ekleyiyoruz. Bu bileşene sağ tıklayarak ulaştığımız **Promote to** komutu ile widget bileşenini QChartView sınıfına bağlıyoruz. Bu işlemin ardından çizim yapabilmek için gereken veri yapısını tanımlıyoruz.

```C++
QLineSeries *seriesV;
QVector<QPointF> pointsV;
QValueAxis *axisX, *axisY;
QChart *chart;
```

* QLineSeries: Adından da anlaşıldığı gibi çizgi grafiği çizdirmek için gereken nesne. Çizim için gereken diziyi noktalar halinde tutuyor (x ve y olarak).

* QVector<QPointF>: QLineSeries üzerinde bir değişiklik yapıldığından direk olarak çizime yansımaktadır. Eğer QLineSeries üzerinden güncelleme işlemi fazla ise çizim performansı düşebilmektedir. Bu nedenle çizimi yapılacak olan değerler QPointF dizisinde tutulmaktadır. Bu dizi üzerinde işlemler tamamlandıktan sonra **replace** metodu kullanılarak QPointF verisi QLineSeries sınıfına aktarılmaktadır. Böylelikle performans kaybı da yaşanmamaktadır.

* QValueAxis: Bu sınıflar ile eksenler ayarlanmaktadır. Bir chart görüntüsü üzerine iki farklı Y- ekseni bindirilebilmektedir. Eksenler hem QtChart hem de QLineSeries sınıfları ile tanımlı nesnelere **attach** metodu ile bağlanmalıdır.

* QtChart: Çizim işlemlerinin gerçekleştirilmesini sağlayan nesnedir.

### Örnek Uygulama
Örnek uygulama olarak toplam 200 adet noktaya sahip olan bir grafiğe ait çizim işlemi gerçekleştirilmiştir. Bu uygulama şu adımları içermektedir:

1. QPontF tipindeki vektörü ***(pointsV)*** 200 elemana gemişlet.
2. pointsV elemanlarının X ve Y değerlerini ayarla.
3. QLineSeries tipindeki ***seriesV*** nesnesine bu noktaları ***replace*** metodu ile aktar.
4. QtChart sınıfından chart nesnesini üret.
5. Eksenleri üret ve ayarlarını yap.
6. seriesV nesnesini QtChart bileşenine ekle.
7. Eksenleri QtChart bileşenine bağla.
8. Eksenleri seriesV nesnesine bağla.

Aşağıdaki kod bloğu 3. adıma kadar olan işlemleri içermektedir.

```C++
pointsV.resize(200);

for (int i=0;i<200;i++) {
    pointsV[i].setX(i/1.0);
    pointsV[i].setY(i/1.0);
}

seriesV = new QLineSeries();
seriesV->setUseOpenGL(true);
seriesV->setPen(QPen("blue"));

/* Bu işleme gerek kalmadı. replace metodu otomatik olarak seriyi genişletiyor.
for (int i=0;i<200;i++)
    seriesV->append(i/1.0, 1000.0);
*/

seriesV->replace(pointsV);
```

Uygulamanın geride kalan adımları ise şu şekilde kodlanmıştır. Burada X- ekseni ve ona ait olan grafiğin rengi QPen ile mavi olarak ayarlanmıştır. Oluşturulan eksenler seri nesnelerine de atanmaktadır. Kodun sonunda grafik, **promoted widget** sınıfı içinde görüntülenmektedir. Bu işlemlerin tamamı uygulama açılırken bir kez yapılmaktadır. Grafik güncelleme işlemi sadece replace yordamı ile yapımaktadır. **QChartView** sınıfına ait Antialiasing özelliği performans kaybı yaşanmaması için kapatılmıştır.

```C++
// Font for graph axes
QFont font;
font.setPixelSize(7);

chart = new QChart();
chart->legend()->hide();

axisX = new QValueAxis;
// axisX->setTickCount(20);
axisX->setLabelsFont(font);
axisX->setRange(0.0, 200.0);

axisY = new QValueAxis;
axisY->setLabelsFont(font);
axisY->setLinePenColor(seriesV->pen().color());
axisY->setRange(0.0, 50000.0);

chart->addSeries(seriesV);

chart->addAxis(axisX, Qt::AlignBottom);
chart->addAxis(axisY, Qt::AlignLeft);

// Dikkat, burasi onemli !!!
seriesV->attachAxis(axisX);
seriesV->attachAxis(axisY);

// We need performance
ui->widget->setRenderHint(QPainter::Antialiasing, false);
ui->widget->setChart(chart);
```
