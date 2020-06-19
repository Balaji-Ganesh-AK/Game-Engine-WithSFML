//#include "stdafx.h"
#include "../../../HeaderFiles/Engine/Input/EngineInput.h"
#include "HeaderFiles/Engine/Utility/Helper.h"
#include <vector>


namespace Engine
{
	namespace Input
	{
		std::map<unsigned, std::pair< bool, int>> _KeyListDown;
		std::vector<std::function<void(unsigned int, bool)>> KeyChangeCallbacks;

		void RegisterOnKeyChangeTest(std::function<void(unsigned int, bool)> i_OnKeyChange)
		{
			KeyChangeCallbacks.push_back(i_OnKeyChange);
		}

		void Init()
		{
			GLib::SetKeyStateChangeCallback([](unsigned int i_VKeyID, bool i_bDown)
				{
					for (auto k : KeyChangeCallbacks)
					{
						if (k)
							k(i_VKeyID, i_bDown);
					}
				}
			);
		}
		
	void CheckForInput(unsigned i_VKeyID, bool bWentDown)
	{
	
		if (i_VKeyID && bWentDown == true)
		{
			
			ActionMap(i_VKeyID);
			//Key down during the frame
			if(_KeyList.count(i_VKeyID))
			{
				std::map<unsigned, bool>::iterator it = _KeyList.find(i_VKeyID);
				if (it != _KeyList.end())
					it->second = true;
			
			}
			else
			{
				_KeyList.insert(std::pair<unsigned,bool> (i_VKeyID,true));
				
			}
			//Key down onces;
			if (_KeyListDown.count(i_VKeyID))
			{
				const std::map<unsigned, std::pair< bool, int>>::iterator it = _KeyListDown.find(i_VKeyID);
				if (it != _KeyListDown.end())
				{
					
					it->second.first = true;
					it->second.second = 1;
					
				}

			}
			else
			{
				_KeyListDown.insert(std::pair<unsigned, std::pair< bool, int>> (i_VKeyID,std::make_pair<bool,int>(true, 1)));
				//_KeyListDown.insert(std::make_pair(i_VKeyID, std::make_pair(true,1)));
				

			}
			
		}
		if (bWentDown == false)
		{

			ActionMap(0);
			std::map<unsigned, bool>::iterator it = _KeyList.find(i_VKeyID);
			if (it != _KeyList.end())
			{
				it->second = false;
				

			}
			if (_KeyListDown.count(i_VKeyID))
			{
				std::map<unsigned, std::pair< bool, int>>::iterator itt = _KeyListDown.find(i_VKeyID);
				if (itt != _KeyListDown.end())
				{

					itt->second.first = false;
					itt->second.second = 0;

				}

			}


		}
			
	
		
		
	}

	void ActionMap(unsigned i_VkeyID)
	{
		retrunValue = i_VkeyID;
		if(i_VkeyID == 81)
		{
			_IsQuit = true;
		}
	}

	bool GetKey(unsigned i_VkeyID)
	{
		if (_KeyList.count(i_VkeyID))
		{
			std::map<unsigned, bool>::iterator it = _KeyList.find(i_VkeyID);
			if (it != _KeyList.end())

				return it->second;
		
		}
		else
			return false;
	}

		bool GetKeyDown(unsigned i_VkeyID)
		{
			if (_KeyListDown.count(i_VkeyID))
			{
				std::map<unsigned, std::pair< bool, int>>::iterator it = _KeyListDown.find(i_VkeyID);
				if (it != _KeyListDown.end())
				{
					if (it->second.first == true)
					{
						if (it->second.second == 1)
						{
							it->second.second = -1;
							return true;
						}
						else
							return false;
					}
					else
					{
						return false;
					}

				}

			}
			else
				return false;
		}

		int KeyPressed()
	{
		return retrunValue;
	}

	bool QuitRequested()
	{
		return _IsQuit;
		
	}




	}
}
