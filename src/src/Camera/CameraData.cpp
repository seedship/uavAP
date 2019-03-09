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
    x = data.position[0];
    y = data.position[1];
    z = data.position[2];
    groundspeed = data.groundSpeed;
    std::cout << data.groundSpeed << " " << data.airSpeed<< "\n";
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
                std::bind(&Camera::updateSensorData, this, std::placeholders::_1));

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
