////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2018 University of Illinois Board of Trustees
//
// This file is part of uavAP.
//
// uavAP is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// uavAP is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////
/*
 * MissionControlHelper.h
 *
 *  Created on: Jul 27, 2017
 *      Author: mircot
 */

#ifndef UAVAP_MISSIONCONTROL_MISSIONCONTROLHELPER_H_
#define UAVAP_MISSIONCONTROL_MISSIONCONTROLHELPER_H_

#include "uavAP/Core/DataPresentation/Content.h"
#include "uavAP/Core/DataPresentation/DataPresentationFactory.h"
#include "uavAP/Core/Framework/Helper.h"
#include "uavAP/Core/IPC/IPC.h"
#include "uavAP/Core/Scheduler/SchedulerFactory.h"
#include "uavAP/Core/TimeProvider/TimeProviderFactory.h"
#include "uavAP/MissionControl/DataHandling/MissionControlDataHandling.h"
#include "uavAP/MissionControl/GlobalPlanner/GlobalPlannerFactory.h"
#include "uavAP/MissionControl/MissionPlanner/MissionPlannerFactory.h"

class MissionControlHelper: public Helper
{
public:
	MissionControlHelper()
	{
		addDefaultCreator<IPC>("ipc");
		addDefaultCreator<MissionControlDataHandling>("data_handling");

		addDefault<SchedulerFactory>("scheduler");
		addDefault<TimeProviderFactory>("time_provider");
		addDefault<DataPresentationFactory<Content,Target>>("data_presentation");

		addFactory<MissionPlannerFactory>("planner");
		addFactory<GlobalPlannerFactory>("global_planner");
	}
};

#endif /* UAVAP_MISSIONCONTROL_MISSIONCONTROLHELPER_H_ */
