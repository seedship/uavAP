#include "uavAP/Camera/CameraData.h"
#include "uavAP/Core/Scheduler/MultiThreadingScheduler.h"
#include "uavAP/Core/Runner/SimpleRunner.h"
#include "uavAP/Core/TimeProvider/SystemTimeProvider.h"
#include <memory>
#include <iostream>


int main(int argc, char** argv) {
    auto cam_data = std::make_shared<CameraData>();
    auto ipc = std::make_shared<IPC>();
    auto sched = std::make_shared<MultiThreadingScheduler>();
    auto timeprovider = std::make_shared<SystemTimeProvider>();

    Aggregator agg;
    SimpleRunner runner(agg);
    agg.add(sched);
    agg.add(cam_data);
    agg.add(ipc);
    agg.add(timeprovider);

    if (runner.runAllStages())
    {
        return 1;
    }

    while(1);
}