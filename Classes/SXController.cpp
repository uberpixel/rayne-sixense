//
//  SXController.cpp
//  rayne-sixense
//
//  Created by Nils Daumann on 06.12.14.
//  Copyright (c) 2014 Uberpixel. All rights reserved.
//

#include "SXController.h"

namespace SX
{
	Controller::Controller(int base, int id)
		: _base(base), _id(id), _enabled(false), _alive(false)
	{
		
	}
	
	Controller::~Controller()
	{
		
	}
	
	void Controller::Update(sixenseControllerData &controllerData)
	{
		if(sixenseIsControllerEnabled(_id))
		{
			_enabled = true;
			_controllerData = controllerData;
			
			_rotation = RN::Quaternion(controllerData.rot_quat[0], controllerData.rot_quat[1], controllerData.rot_quat[2], controllerData.rot_quat[3]);
			
			_position.x = controllerData.pos[0]/1000.0f;
			_position.y = controllerData.pos[1]/1000.0f;
			_position.z = controllerData.pos[2]/1000.0f;
		}
		else
		{
			_enabled = false;
		}
	}
	
	bool Controller::GetButtonJustPressed(uint16 button)
	{
		sixenseUtils::ButtonStates buttonstates;
		buttonstates.update(&_controllerData);
		return buttonstates.buttonJustPressed(button);
	}
	
	bool Controller::GetTriggerJustPressed()
	{
		sixenseUtils::ButtonStates buttonstates;
		buttonstates.update(&_controllerData);
		return buttonstates.triggerJustPressed();
	}
	
	bool Controller::GetTriggerJustReleased()
	{
		sixenseUtils::ButtonStates buttonstates;
		buttonstates.update(&_controllerData);
		return buttonstates.triggerJustPressed();
	}
	
	const RN::Quaternion &Controller::GetRotation() const
	{
		return _rotation;
	}
	
	const RN::Vector3 &Controller::GetPosition() const
	{
		return _position;
	}
	
	int Controller::GetID() const
	{
		return _id;
	}
	
	int Controller::GetBase() const
	{
		return _base;
	}
}
