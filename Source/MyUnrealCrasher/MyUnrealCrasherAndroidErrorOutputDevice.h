//  Copyright © BugSplat. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "Misc/OutputDeviceError.h"

#if PLATFORM_ANDROID
class FMyUnrealCrasherAndroidErrorOutputDevice : public FOutputDeviceError
{
public:
	virtual ~FMyUnrealCrasherAndroidErrorOutputDevice() {}
	
	virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category) override;
	virtual void HandleError() override;
	
	static FOutputDeviceError* GetErrorOutputDevice();
	
private:
	void RequestExit(bool Force, const TCHAR* CallSite);
};
#endif
