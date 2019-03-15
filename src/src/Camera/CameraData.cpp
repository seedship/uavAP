#include "uavAP/Camera/CameraData.h"
#include "uavAP/Core/Scheduler/MultiThreadingScheduler.h"
#include "uavAP/Core/Runner/SimpleRunner.h"
#include "uavAP/Core/TimeProvider/SystemTimeProvider.h"
#include <memory>
#include <iostream>

CameraData::CameraData()
{
}

void CameraData::updateSensorData(const SensorData &data)
{
    data_ = data;
    x_ = data.position[0];
    y_ = data.position[1];
    z_ = data.position[2];
    groundspeed_ = data.groundSpeed;

}

void CameraData::notifyAggregationOnUpdate(const Aggregator &agg)
{
    ipcHandle_.setFromAggregationIfNotSet(agg);
}

bool CameraData::run(RunStage stage)
{
    switch (stage)
    {
    case RunStage::INIT:
    {
        if (!ipcHandle_.isSet())
        {
            APLOG_ERROR << "IPC Missing.";
            return true;
        }

        break;
    }
    case RunStage::NORMAL:
    {
        auto ipc = ipcHandle_.get();

        subscription_ = ipcHandle_.get()->subscribeOnSharedMemory<SensorData>("sensor_data",
                std::bind(&CameraData::updateSensorData, this, std::placeholders::_1));

        APLOG_WARN << "Created Subscription";

        if (!subscription_.connected())
        {
            APLOG_ERROR << "Sensor Data Subscription Missing.";
            return true;
        }

        break;
    }
    default:
    {
        break;
    }
    }

    return false;
}

double CameraData::getX() {
	return x_;
}

double CameraData::getY() {
	return y_;
}

double CameraData::getZ() {
	return z_;
}

double CameraData::getGroundSpeed(){
	return groundspeed_;
}

TimePoint CameraData::getTimeStamp() {
	return timestamp_;
}
