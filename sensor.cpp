#include "sensor.h"
#include "USBDAQ_DLL_V12.h"
#include <QQueue>

/************传感器基类*************/
Sensor::Sensor()
{
    num = -1;
}

Sensor::Sensor(int n)
{
    num = n;
}

Sensor::~Sensor()
{

}


/*************光电开关类**************/
Photoelec::Photoelec()
{

}

Photoelec::Photoelec(int n) : Sensor(n)
{

}

Photoelec::~Photoelec()
{

}
//判断是否到达
bool Photoelec::IsArrive()
{
    float voltage;
    while(!voltages.isEmpty())
    {
        voltage = voltages.dequeue();
        if(voltage<max_v && voltage>min_v){ //遮光时高电平
            arrive = true;
        }else{
            arrive = false;
        }
    }
    if(arrive){
        return true;
    }else{
        return false;
    }
}

/*************力传感器类**************/
ForceSensor::ForceSensor()
{
    processFlag = false;
    counts = 0;
}

ForceSensor::ForceSensor(int n):Sensor(n)
{
    processFlag = false;
    counts = 0;
}



ForceSensor::~ForceSensor()
{

}
