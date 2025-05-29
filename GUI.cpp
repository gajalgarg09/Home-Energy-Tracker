#include "GUI.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "EnergyTracker.h"
#include "UserAuth.h"
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QValueAxis>

GUI::GUI(QWidget *parent) : QWidget(parent), chartView(new QtCharts::QChartView(this)) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *titleLabel = new QLabel("Home Energy Tracker", this);
    QPushButton *addDataButton = new QPushButton("Add Data", this);
    QPushButton *viewReportButton = new QPushButton("View Report", this);
    QPushButton *loginButton = new QPushButton("Login", this);
    QPushButton *showChartButton = new QPushButton("Show Usage Chart", this);

    layout->addWidget(titleLabel);
    layout->addWidget(addDataButton);
    layout->addWidget(viewReportButton);
    layout->addWidget(loginButton);
    layout->addWidget(showChartButton);
    layout->addWidget(chartView);

    setLayout(layout);
    setWindowTitle("Home Energy Tracker");
    resize(600, 400);

    connect(loginButton, &QPushButton::clicked, this, &GUI::onLoginClicked);
    connect(addDataButton, &QPushButton::clicked, this, &GUI::onAddDataClicked);
    connect(viewReportButton, &QPushButton::clicked, this, &GUI::onViewReportClicked);
    connect(showChartButton, &QPushButton::clicked, this, &GUI::showUsageChart);
}

GUI::~GUI() {}

void GUI::onLoginClicked() { /* Call login function in UserAuth */ }
void GUI::onAddDataClicked() { /* Open dialog for adding data in EnergyTracker */ }
void GUI::onViewReportClicked() { /* Display report in EnergyTracker */ }

void GUI::showUsageChart() {
    QtCharts::QLineSeries *series = new QtCharts::QLineSeries();
    series->append(1, 1.5);  // Replace with real data
    series->append(2, 2.5);
    series->append(3, 3.0);
    series->append(4, 2.7);
    series->append(5, 3.3);

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Daily Energy Usage");

    QtCharts::QCategoryAxis *xAxis = new QtCharts::QCategoryAxis();
    xAxis->append("Day 1", 1);
    xAxis->append("Day 2", 2);
    xAxis->append("Day 3", 3);
    xAxis->append("Day 4", 4);
    xAxis->append("Day 5", 5);
    chart->addAxis(xAxis, Qt::AlignBottom);
    series->attachAxis(xAxis);

    QtCharts::QValueAxis *yAxis = new QtCharts::QValueAxis();
    yAxis->setRange(0, 5);
    chart->addAxis(yAxis, Qt::AlignLeft);
    series->attachAxis(yAxis);

    chartView->setChart(chart);
}
