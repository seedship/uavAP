#include "uavAP/Camera/Camera.h"
#include "uavAP/Core/Scheduler/MultiThreadingScheduler.h"
#include "uavAP/Core/Runner/SimpleRunner.h"
#include "uavAP/Core/TimeProvider/SystemTimeProvider.h"
#include <memory>
#include <iostream>


int main(int argc, char** argv) {
    auto cam = std::make_shared<Camera>();
    auto ipc = std::make_shared<IPC>();
    auto sched = std::make_shared<MultiThreadingScheduler>();
    auto timeprovider = std::make_shared<SystemTimeProvider>();

    Aggregator agg;
    SimpleRunner runner(agg);
    agg.add(sched);
    agg.add(cam);
    agg.add(ipc);
    agg.add(timeprovider);

    if (runner.runAllStages())
    {
        return 1;
    }

    while(1);
}

Camera::Camera()
{
}

void Camera::getSensorData(const SensorData &data)
{
    std::cout << data.groundSpeed << " " << data.airSpeed<< "\n";
}

void Camera::notifyAggregationOnUpdate(const Aggregator &agg)
{
    ipcHandle_.setFromAggregationIfNotSet(agg);
}

bool Camera::run(RunStage stage)
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
                std::bind(&Camera::getSensorData, this, std::placeholders::_1));

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
