#pragma once

class CCamera;

class IInputManager
{
protected:
	IInputManager() {}
	~IInputManager() {}

	IInputManager(const IInputManager&) {}
	IInputManager operator =(const IInputManager&) {}

public:
	static IInputManager * GetInstance()
	{
		if (ms_pIntance = nullptr)
			ms_pIntance = new IInputManager;
		return ms_pIntance;
	}
	static void DestroyInstance()
	{
		if (ms_pIntance)
		{
			delete ms_pIntance;
			ms_pIntance = 0;
		}
	}
	void ManageInput(unsigned char key, bool isPressed, CCamera * cam);
protected:
	static IInputManager * ms_pIntance;
};
