#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int dataAcquTimer; //采集卡定时器
    int photoTimer; //光电开关状态更新定时器
    int forSensorTimer; //力传感器数据记录处理定时器
    int forceChartTimer; //力传感器数据显示定时器

protected:
    void timerEvent(QTimerEvent *);
    void updateChartData();
private slots:
    void on_actionConnect_Device_triggered();
    void on_actionDisconnect_Device_triggered();
    void on_forSensorStart_pushButton_clicked();
    void on_forSensorStop_pushButton_clicked();
};

#endif // MAINWINDOW_H
