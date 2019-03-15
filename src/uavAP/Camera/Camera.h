#include "uavAP/Core/IPC/IPC.h"
#include "uavAP/Core/IPC/Subscription.h"
#include "uavAP/Core/SensorData.h"

class Camera : public IAggregatableObject,
        public IRunnableObject {
public:
    Camera();
    SensorData data_;

    ObjectHandle<IPC> ipcHandle_;

    Subscription subscription_;

    void
    getSensorData(const SensorData& data);

    // IAggregatableObject interface
    void notifyAggregationOnUpdate(const Aggregator &agg);

    // IRunnableObject interface
public:
    bool run(RunStage stage);
};
