//
//  SXSystem.cpp
//  rayne-sixense
//
//  Created by Nils Daumann on 06.12.14.
//  Copyright (c) 2014 Uberpixel. All rights reserved.
//

#include "SXSystem.h"
#include "SXController.h"

namespace SX
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
