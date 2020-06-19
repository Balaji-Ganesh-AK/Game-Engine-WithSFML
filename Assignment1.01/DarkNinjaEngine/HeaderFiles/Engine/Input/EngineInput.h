#pragma once

#include "../GLib/GLib.h"

#include <functional>
#include <map>


namespace Engine
{
	namespace Input
	{
	void RegisterOnKeyChangeTest(std::function<void(unsigned int, bool)> i_OnKeyChange);
	void Init();
	void CheckForInput(unsigned int i_VKeyID, bool bWentDown);
	void ActionMap(unsigned int i_VkeyID);
	bool GetKey(unsigned int i_VkeyID);
	bool GetKeyDown(unsigned int i_VkeyID);
	
	int KeyPressed();
	static int retrunValue;
	static bool _IsQuit = false;
	bool QuitRequested();

	}
	static std::map<unsigned, bool> _KeyList;
	
}
