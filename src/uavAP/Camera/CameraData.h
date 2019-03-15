#include "uavAP/Core/IPC/IPC.h"
#include "uavAP/Core/IPC/Subscription.h"
#include "uavAP/Core/SensorData.h"

class CameraData : public IAggregatableObject,
        public IRunnableObject {
public:
    CameraData();

    ObjectHandle<IPC> ipcHandle_;

    Subscription subscription_;

    void
    updateSensorData(const SensorData& data);

    // IAggregatableObject interface
    void notifyAggregationOnUpdate(const Aggregator &agg);

    // IRunnableObject interface
    bool run(RunStage stage);

    double getX();
    double getY();
    double getZ();
    double getGroundSpeed();
    TimePoint getTimeStamp();

private:
    SensorData data_;
    double x_;
    double y_;
    double z_;
    double groundspeed_;
    TimePoint timestamp_;
};
