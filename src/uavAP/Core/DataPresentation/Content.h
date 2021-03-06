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
 * Content.h
 *
 *  Created on: Aug 3, 2018
 *      Author: mircot
 */

#ifndef UAVAP_CORE_DATAPRESENTATION_CONTENT_H_
#define UAVAP_CORE_DATAPRESENTATION_CONTENT_H_

#include <uavAP/Core/EnumMap.hpp>

/**
 * @brief Defines the Target for forwarding of packets. Only used in uavAP.
 */
enum class Target
{
	INVALID,        //!< INVALID
	FLIGHT_ANALYSIS, //!< Forward to FlightAnalysis
	FLIGHT_CONTROL, //!< Forward to FlightControl
	MISSION_CONTROL, //!< Forward to MissionControl
	COMMUNICATION,  //!< Forward to Communication
	API             //!< Forward to API
};

/**
 * @brief Content definitions.
 */
enum class Content
{
	INVALID,                	//!< INVALID
	//UAVAP to GS
	SENSOR_DATA,            	//!< SENSOR_DATA
	MISSION,                	//!< MISSION
	TRAJECTORY,             	//!< TRAJECTORY
	PID_STATUS,             	//!< PID_STATUS
	INSPECTING_METRICS,			//!< INSPECTING_METRICS
	LOCAL_PLANNER_STATUS,   	//!< LOCAL_PLANNER_STATUS
	SAFETY_BOUNDS,          	//!< SAFETY_BOUNDS
	CONTROLLER_OUTPUT,      	//!< CONTROLLER_OUTPUT
	LOCAL_FRAME,

	//GS to FlightControl in UAVAP
	TUNE_PID,               	//!< TUNE_PID
	TUNE_PITCH_CONSTRAINT,  	//!< TUNE_PITCH_CONSTRAINT
	TUNE_ROLL_CONSTRAINT,   	//!< TUNE_ROLL_CONSTRAINT
	TUNE_LOCAL_PLANNER,     	//!< TUNE_LOCAL_PLANNER
	REQUEST_DATA,           	//!< REQUEST_DATA
	ADVANCED_CONTROL,

	//GS to MissionControl
	OVERRIDE,       			//!< OVERRIDE
	SELECT_MANEUVER_SET,    	//!< SELECT_MANEUVER_SET
	SELECT_MISSION,         	//!< SELECT_MISSION

	//GS to FlightAnalysis
	SELECT_INSPECTING_METRICS 	//!< SELECT_INSPECTING_METRICS
};

/**
 * @brief Data request options.
 */
enum class DataRequest
{
	INVALID = 0,  //!< INVALID
	MISSION,      //!< MISSION
	TRAJECTORY,   //!< TRAJECTORY
	SAFETY_BOUNDS,   //!< SAFETY_BOUNDS
	LOCAL_FRAME,   //!< LOCAL_FRAME
	START_LOGGING,   //!< START_LOGGING
	STOP_LOGGING  //!< STOP_LOGGING
};

enum class Tuning
{
	INVALID, LOCAL_PLANNER, GLOBAL_PLANNER, CONTROLLER
};

ENUMMAP_INIT(Tuning, {{Tuning::LOCAL_PLANNER, "local_planner"}, {Tuning::GLOBAL_PLANNER,
		"global_planner"}, {Tuning::CONTROLLER, "controller"}});

#endif /* UAVAP_CORE_DATAPRESENTATION_CONTENT_H_ */
