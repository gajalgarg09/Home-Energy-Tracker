#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QValueAxis>

class GUI : public QWidget {
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    ~GUI();

private slots:
    void onLoginClicked();
    void onAddDataClicked();
    void onViewReportClicked();
    void showUsageChart();

private:
    QtCharts::QChartView *chartView;
};

#endif
