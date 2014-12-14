//
//  SXSystem.cpp
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

#include "SXSystem.h"
#include "SXController.h"

namespace RN
{
	namespace sixense
	{
		RNDefineSingleton(System)
		
		System::System()
		{
			// Init sixense
			if(sixenseInit() == SIXENSE_FAILURE)
				return;
			
			sixenseSetActiveBase(0);
			sixenseSetBaseColor(0, 0, 0);
			
			sixenseUtils::getTheControllerManager()->setGameType(sixenseUtils::ControllerManager::ONE_PLAYER_TWO_CONTROLLER);
			sixenseUtils::getTheControllerManager()->registerSetupCallback([](sixenseUtils::ControllerManager::setup_step step){
				 if(sixenseUtils::getTheControllerManager()->isMenuVisible())
				 {
					
					// Turn on the flag that tells the graphics system to draw the instruction screen instead of the controller information. The game
					// should be paused at this time.
					//			controller_manager_screen_visible = true;
					
					// Ask the controller manager what the next instruction string should be.
					RNDebug(sixenseUtils::getTheControllerManager()->getStepString());
					
					// We could also load the supplied controllermanager textures using the filename: sixenseUtils::getTheControllerManager()->getTextureFileName();
					
				 }
			 });
		}
		
		System::~System()
		{
			sixenseExit();
		}
		
		void System::Update()
		{
			sixenseAllControllerData acd;
			
			// Go through each of the connected systems
			for(int base = 0; base < sixenseGetMaxBases(); base++)
			{
				sixenseSetActiveBase(base);
				
				// Get the latest controller data
				sixenseGetAllNewestData(&acd);
				
				if(base == 0)
				{
					sixenseUtils::getTheControllerManager()->update(&acd);
				}
				
				// For each possible controller
				for(int cont = 0; cont < sixenseGetMaxControllers(); cont++)
				{
					Controller *controller = GetController(base, cont);
					if(!controller)
					{
						controller = new Controller(base, cont);
						_controllers.push_back(controller);
					}
					controller->_alive = true;
					controller->Update(acd.controllers[cont]);
				}
			}
			
			int i = 0;
			for(Controller *controller : _controllers)
			{
				if(controller->_alive)
				{
					controller->_alive = false;
				}
				else
				{
					_controllers.erase(_controllers.begin() + i);
					delete controller;
				}
				
				i += 1;
			}
		}
		
		Controller *System::GetController(int base, int id) const
		{
			for(Controller *controller : _controllers)
			{
				if(controller->GetBase() == base && controller->GetID() == id)
				{
					return controller;
				}
			}
			
			return nullptr;
		}
	}
}
