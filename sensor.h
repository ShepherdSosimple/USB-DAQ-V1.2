#ifndef SENSOR_H
#define SENSOR_H

#include <QQueue>

//基类:传感器
class Sensor
{
public:
    int num;  //传感器对应的采集卡端口
    QQueue<float> voltages; //传感器电压值队列
    float voltage; //传感器电压值
    Sensor();
    explicit Sensor(int n);
    ~Sensor();    
};


//派生类：光电开关（模拟量形式）
class Photoelec: public Sensor
{
private:
    const float max_v = 10.0;
    const float min_v = 1.0;
public:
    bool arrive;
    Photoelec();
    Photoelec(int  n);
    ~Photoelec();
    bool IsArrive();
};


//派生类：力传感器
class ForceSensor: public Sensor
{
public:
    ForceSensor();
    ForceSensor(int n);

    bool processFlag;//力数据处理标志
    quint64 counts;
    ~ForceSensor();
};



#endif // SENSOR_H
