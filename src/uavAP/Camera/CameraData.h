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

    double x;
    double y;
    double z;
    double groundspeed;

private:
    SensorData data_;
};
