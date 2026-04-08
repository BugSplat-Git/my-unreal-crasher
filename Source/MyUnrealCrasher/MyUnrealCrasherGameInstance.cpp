//  Copyright © BugSplat. All rights reserved.
#include "MyUnrealCrasherGameInstance.h"
#include "MyUnrealCrasherAndroidErrorOutputDevice.h"
#include "BugSplatAttributes.h"

#if PLATFORM_ANDROID
#include <android/log.h>
#endif

void UMyUnrealCrasherGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Log, TEXT("MyUnrealCrasherGameInstance::Init - Setting custom error output device"));

#if PLATFORM_ANDROID
	GError = FMyUnrealCrasherAndroidErrorOutputDevice::GetErrorOutputDevice();
	UBugSplatAttributes::SetAttribute(TEXT("Custom Attribute"), TEXT("attribute set after initialization"));
#endif
}
