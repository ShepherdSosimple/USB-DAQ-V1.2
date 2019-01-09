#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "USBDAQ_DLL_V12.h"
#include "sensor.h"
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QDateTime>
#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
#include <QChartView>
#include <QVBoxLayout>
#include <QDebug>


QT_CHARTS_USE_NAMESPACE

const int CHA_NUM = 3; //采集卡通道使用数
const int SAMPLE_FREQ = 30000; //总采样频率
//传感器
ForceSensor forceSens(0);  //通道0：一维力传感器
Photoelec   upperPhoto(1); //通道1：上部光电开关
Photoelec   lowerPhoto(2); //通道2：下部光电开关
//绘图
QChart *forceChart ; //力_绘图
QLineSeries *forceSeries; //力数据坐标存放
//文件
QFile forceInfoFile("foceInfoFile.txt"); //输出文件：力传感器信息

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化力/力矩波形图
    forceChart = new QChart;
    forceSeries = new QLineSeries;
    forceChart->addSeries(forceSeries);
    //QChartView *forceView = new QChartView(forceChart);
    //forceView->setRubberBand(QChartView::RectangleRubberBand);
    forceChart->setTitle(tr("Dynamic force curve"));
    QValueAxis *axisX = new QValueAxis;
    axisX->setLabelFormat("%g");
    axisX->setRange(0,100);
    axisX->setTitleText("Force");
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(-10.0,10.0);
    axisY->setTitleText("Time");
    forceChart->setAxisX(axisX,forceSeries);
    forceChart->setAxisY(axisY,forceSeries);


    QChartView *forceView = new QChartView(forceChart);//声明QChartView 并创建实例，加载chart

    QGridLayout *baseLayout = new QGridLayout(); //便于显示，创建网格布局

    baseLayout->addWidget(forceView, 1, 0);
    ui->widget->setLayout(baseLayout); //显示到QWidget控件
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*************************************定时器事件********************************/
void MainWindow::timerEvent(QTimerEvent *event)
{
    //读取采集卡缓存，分发数据
    if(event->timerId() == dataAcquTimer)
    {
        int bufferNum = 0; //缓存中数据的个数
        int readNum = 0; //从缓存读取数据的个数
        int i;
        //float buffer[3000] ;
        bufferNum = GetAdBuffSizeV12();
        float *buffer = new float[bufferNum];
        //qDebug()<<bufferNum;
        readNum = bufferNum-bufferNum%CHA_NUM; //从缓存中读取完全n组通道数据
        ReadAdBuffV12(buffer, readNum);
        for(i=0; i<(readNum/CHA_NUM); i++){
            forceSens.voltages.enqueue(buffer[i*CHA_NUM]);
            upperPhoto.voltages.enqueue(buffer[i*CHA_NUM+1]);
            lowerPhoto.voltages.enqueue(buffer[i*CHA_NUM+2]);//分发数据，扫描通道顺序3 1 2
            qDebug()<<"aaaa"<<buffer[i*CHA_NUM]<<"bbbb"<<buffer[i*CHA_NUM+1]<<"cccc"<<buffer[i*CHA_NUM+2];
        }
        delete []buffer;
        if(!forceSens.processFlag){
            forceSens.voltages.clear(); //若力传感器未打开数据处理，则清空电压队列
        }
    }

    //更新光电开关状态
    if(event->timerId() == photoTimer)
    {
        upperPhoto.IsArrive();
        lowerPhoto.IsArrive();
    }

    //力传感器数据记录、更新定时器
    if(event->timerId() == forSensorTimer)
    {
        //输出力传感器原始数据
        forceInfoFile.open(QIODevice::Append | QIODevice::Text);
        QTextStream out(&forceInfoFile);
        while(!forceSens.voltages.isEmpty()){
            float a;
            forceSens.counts++;
            a = forceSens.voltages.dequeue();
            out<<qSetFieldWidth(30)<<left<<a<<qSetFieldWidth(0)<<endl; //输出力数据至文档
            forceSens.voltage = a;
        }
        forceInfoFile.close();
    }

    //力传感器数据绘制显示定时器
    if(event->timerId() == forceChartTimer)
    {
        updateChartData();
    }
}

void MainWindow::updateChartData()
{
    int i;
    QVector<QPointF> oldData = forceSeries->pointsVector();
    QVector<QPointF> data;

    if(oldData.size() < 97){
        data = forceSeries->pointsVector();
    } else {
        for(i = 1; i< oldData.size(); ++i) {
            data.append(QPointF(i-1,oldData.at(i).y()));
        }
    }

    qint64 size = data.size();
    for(i=0;i<1;++i) {
        data.append(QPointF(i+size, forceSens.voltage));
    }

    forceSeries->replace(data);
}

void MainWindow::on_actionConnect_Device_triggered()
{
    if(!OpenUsbV12()){
        MADContinuConfigV12(0,0,CHA_NUM-1,1,SAMPLE_FREQ); //多通道差分连续采样：-10~10V，频率每通道SAMPLE_FREQ/CHA_NUM
        dataAcquTimer = startTimer(1,Qt::PreciseTimer); //开启采集卡缓存读取定时器：20ms 精确
        photoTimer = startTimer(25,Qt::PreciseTimer); //开启光电开关状态更新定时器：25ms 精确
    }else{
        QMessageBox::warning(this, tr("警告！"),
                                   tr("打开采集卡失败，请检查接线 ！"),
                                  QMessageBox::Yes);
    }
}

void MainWindow::on_actionDisconnect_Device_triggered()
{
    killTimer(dataAcquTimer);
    ADContinuStopV12();
    if(!CloseUsbV12()){

    }else{
        QMessageBox::warning(this, tr("警告！"),
                                   tr("关闭采集卡失败 ！"),
                                  QMessageBox::Yes);
    }
}

void MainWindow::on_forSensorStart_pushButton_clicked()
{
    forSensorTimer = startTimer(1, Qt::PreciseTimer); //开启力传感器数据记录处理定时器：20ms 精确
    forceChartTimer = startTimer(30, Qt::PreciseTimer); //开启力传感器数据绘制处理定时器：100ms 精确
    forceSens.processFlag = true;
}

void MainWindow::on_forSensorStop_pushButton_clicked()
{
    forceSens.processFlag = false;
    killTimer(forSensorTimer);
    killTimer(forceChartTimer);
    forceSens.counts = 0;
}
