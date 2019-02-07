# qtcharts_sample
### Qt 5.7 Sample QtCharts Application

QtCharts bileşeni Qt çerçevesi ile grafik çizdirmek için kullanılan bir bileşen. Daha önce Qwt ya da QCustomPlot gibi farklı üçüncü parti bileşenleri kullanmış olanalar için yerel bir (native) bir çözüm olarak tercih edilebilir. Açık kaynak tarafında Digia tarafından GPL lisansı ile dağıtılmaktadır. Qt 5.7 ile sürümü ile açık kaynak dağıtımına eklenmiştir. OpenGL desteği etkin olarak kullanılabilmektedir.

Bu bileşeni kullanabilmek için ilk QtCreator **.pro** (proje) dosyasına **charts** kütüphanesini ekleniyor. 

`
QT += core gui charts
` 

Daha sonra proje başlık dosyasına (header) gerekli kütüphane başlıklarını ve charts kullanımını aktifleştiren direktifi ekliyoruz.

`
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE
`
QtCreator tasarım ortamına qthcarts bileşen desteğini ekleyebilmek için aracı bir sınıf kullanıyoruz. Bu uygulamada bu sınıfın adı **ChartView** olarak seçilmiş olup sınıfa ait dosyalar proje ağacında yer almaktadır. Daha sonra QtCreator form tasarımı üzerine **widget** bileşeni ekleyiyoruz. Bu bileşene sağ tıklayarak ulaştığımız **Promote to** komutu ile widget bileşenini QChartView sınıfına bağlıyoruz. Bu işlemin ardından çizim yapabilmek için gereken veri yapısını tanımlıyoruz.

`
QLineSeries *seriesV;
QVector<QPointF> pointsV;
QValueAxis *axisX, *axisY;
QChart *chart;
`

* QLineSeries: Adından da anlaşıldığı gibi çizgi grafiği çizdirmek için gereken nesne. X ve Y koordinatları ayrı ayrı ayarlanıyor.
