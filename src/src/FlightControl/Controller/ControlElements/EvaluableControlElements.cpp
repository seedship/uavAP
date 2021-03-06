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
 * EvaluableControlElement.cpp
 *
 *  Created on: Jun 19, 2017
 *      Author: uav
 */

#include "uavAP/Core/PropertyMapper/PropertyMapper.h"
#include "uavAP/FlightControl/Controller/ControlElements/EvaluableControlElements.h"
#include "uavAP/FlightControl/Controller/PIDController/PIDHandling.h"

namespace Control
{

Filter::Filter(Element in, double alpha) :
		in_(in), init_(true), smoothData_(0), alpha_(alpha)
{
}

void
Filter::evaluate()
{
	if (init_)
	{
		init_ = false;
		smoothData_ = in_->getValue();
		return;
	}

	smoothData_ = alpha_ * in_->getValue() + (1 - alpha_) * smoothData_;
}

double
Filter::getValue()
{
	return smoothData_;
}

void
Filter::setAlpha(double alpha)
{
	alpha_ = alpha;
}

Output::Output(Element in, double* out) :
		in_(in), out_(out), override_(false), overrideOut_(0)
{
}

void
Output::overrideOutput(double newOutput)
{
	override_ = true;
	overrideOut_ = newOutput;
}

void
Output::disableOverride()
{
	override_ = false;
}

void
Output::evaluate()
{
	*out_ = override_ ? overrideOut_ : in_->getValue();
}

double
Output::getValue()
{
	return in_->getValue();
}

PID::PID(Element target, Element current, const Parameters& params, Duration* timeDiff) :
		target_(target), current_(current), params_(params), timeDiff_(timeDiff), targetValue_(0), currentError_(
				0), integrator_(0), lastError_(0), output_(0), override_(false), overrideTarget_(0)
{

}

PID::PID(Element target, Element current, Element derivative, const Parameters& params,
		Duration* timeDiff) :
		target_(target), current_(current), derivative_(derivative), params_(params), timeDiff_(
				timeDiff), targetValue_(0), currentError_(0), integrator_(0), lastError_(0), output_(
				0), override_(false), overrideTarget_(0)
{

}

void
PID::setControlParameters(const Parameters& g)
{
	params_ = g;
	integrator_ = 0;
}

void
PID::overrideTarget(double newTarget)
{
	override_ = true;
	overrideTarget_ = newTarget;
}

void
PID::disableOverride()
{
	override_ = false;
}

void
PID::evaluate()
{
	if (!current_ || !target_)
		return;

	output_ = 0.0;
	targetValue_ = override_ ? overrideTarget_ : target_->getValue();
	currentError_ = targetValue_ - current_->getValue();
	addProportionalControl();
	addIntegralControl();
	addDifferentialControl();
	addFeedForwardControl();
	lastError_ = currentError_;
}

double
PID::getValue()
{
	return std::isnan(output_) ? 0 : output_;
}

void
PID::addProportionalControl()
{
	output_ += params_.kp * currentError_;
}

void
PID::addIntegralControl()
{
	if (params_.ki == 0. || !timeDiff_)
		return;

	integrator_ += currentError_ * timeDiff_->total_microseconds() * MUSEC_TO_SEC;

	if (integrator_ > 0)
		integrator_ = std::min(integrator_, params_.imax);
	else
		integrator_ = std::max(integrator_, -params_.imax);

	output_ += params_.ki * integrator_;
}

void
PID::addDifferentialControl()
{
	if (params_.kd == 0.)
		return;

	if (derivative_)
	{
		//Take the negative derivative value to counter acceleration towards the target
		output_ -= params_.kd * derivative_->getValue();
	}
	else if (!isnanf(lastError_) && timeDiff_ && timeDiff_->total_microseconds() > 0.)
	{
		double derivative = (currentError_ - lastError_)
				/ (timeDiff_->total_microseconds() * MUSEC_TO_SEC);
		output_ += params_.kd * derivative;
	}
}

PIDStatus
PID::getStatus()
{
	PIDStatus status;
	status.target = targetValue_;
	status.value = current_->getValue();
	return status;
}

void
PID::addFeedForwardControl()
{
	if (params_.ff != 0)
	{
		output_ += params_.ff * targetValue_;
	}
}

}
