#include "uavAP/Core/Logging/APLogger.h"
#include "uavAP/Camera/CameraData.h"
#include "uavAP/Core/Scheduler/MultiThreadingScheduler.h"
#include "uavAP/Core/Runner/SimpleRunner.h"
#include "uavAP/Core/TimeProvider/SystemTimeProvider.h"
#include <memory>
#include <iostream>


int main(int argc, char** argv)
{
	APLogger::instance()->setLogLevel(LogLevel::DEBUG);
	APLogger::instance()->setModuleName("Camera");
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


    while(1)
    {
    	APLOG_ERROR << "x: " << cam_data->getX();
		APLOG_ERROR << "y: " << cam_data->getY();
		APLOG_ERROR << "z: " << cam_data->getZ();
		APLOG_ERROR << "ground speed: " << cam_data->getGroundSpeed();
		APLOG_ERROR << "timestamp: " << cam_data->getTimeStamp();
		APLOG_ERROR << "";
    }
}
