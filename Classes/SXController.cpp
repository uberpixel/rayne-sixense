//
//  SXController.cpp
//  rayne-sixense
//
//  Copyright 2014 by Überpixel. All rights reserved.
//  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
//  documentation files (the "Software"), to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
//  and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
//  PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
//  FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#include "SXController.h"

namespace RN
{
	namespace sixense
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
}
