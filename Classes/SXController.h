//
//  SXController.h
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

#ifndef __rayne_sixense__SXController__
#define __rayne_sixense__SXController__

#include "SXSystem.h"

namespace RN
{
	namespace sixense
	{
		class Controller
		{
		public:
			friend System;
			
			Controller(int base, int id);
			~Controller();
			
			const RN::Quaternion &GetRotation() const;
			const RN::Vector3 &GetPosition() const;
			
			int GetID() const;
			int GetBase() const;
			bool GetButtonJustPressed(uint16 button);
			bool GetTriggerJustPressed();
			bool GetTriggerJustReleased();
			
		private:
			void Update(sixenseControllerData &controllerData);
			
			sixenseControllerData _controllerData;
			
			int _id;
			int _base;
			bool _enabled;
			bool _alive;
			RN::Quaternion _rotation;
			RN::Vector3 _position;
		};
	}
}

#endif /* defined(__rayne_sixense__SXController__) */
