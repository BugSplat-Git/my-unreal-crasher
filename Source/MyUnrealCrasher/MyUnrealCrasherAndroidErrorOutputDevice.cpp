// Copyright © BugSplat. All rights reserved.
#include "MyUnrealCrasherAndroidErrorOutputDevice.h"

#include "CoreMinimal.h"
#include "CoreGlobals.h"
#include "Misc/OutputDevice.h"
#include "Misc/OutputDeviceHelper.h"
#include "Misc/App.h"
#include "Misc/CoreDelegates.h"
#include "Misc/FeedbackContext.h"
#include "HAL/PlatformMisc.h"
#include "HAL/PlatformCrt.h"

#if PLATFORM_ANDROID
#include "Android/AndroidPlatform.h" // For LogAndroid

FOutputDeviceError* FMyUnrealCrasherAndroidErrorOutputDevice::GetErrorOutputDevice()
{
	static FMyUnrealCrasherAndroidErrorOutputDevice ErrorOutputDevice;
	return &ErrorOutputDevice;
}

void FMyUnrealCrasherAndroidErrorOutputDevice::Serialize( const TCHAR* Msg, ELogVerbosity::Type Verbosity, const class FName& Category )
{
	FPlatformMisc::LowLevelOutputDebugString(*FOutputDeviceHelper::FormatLogLine(Verbosity, Category, Msg, GPrintLogTimes));

	static int32 CallCount = 0;
	int32 NewCallCount = FPlatformAtomics::InterlockedIncrement(&CallCount);
	if(GIsCriticalError == 0 && NewCallCount == 1)
	{
		// First appError.
		GIsCriticalError = 1;

		FCString::Strncpy(GErrorExceptionDescription, Msg, UE_ARRAY_COUNT(GErrorExceptionDescription));
	}
	else
	{
		UE_LOG(LogAndroid, Error, TEXT("Error reentered: %s"), Msg);
	}

	if (GIsGuarded)
	{
		UE_DEBUG_BREAK();
	}
	else
	{
		HandleError();
		RequestExit(true, TEXT("MyUnrealCrasherAndroidErrorOutputDevice::Serialize.!GIsGuarded"));
	}
}

void FMyUnrealCrasherAndroidErrorOutputDevice::HandleError()
{
	static int32 CallCount = 0;
	int32 NewCallCount = FPlatformAtomics::InterlockedIncrement(&CallCount);

	if (NewCallCount != 1)
	{
		UE_LOG(LogAndroid, Error, TEXT("HandleError re-entered."));
		return;
	}
	
	GIsGuarded = 0;
	GIsRunning = 0;
	GIsCriticalError = 1;
	GLogConsole = NULL;
	GErrorHist[UE_ARRAY_COUNT(GErrorHist) - 1] = 0;

	// Dump the error and flush the log.
#if !NO_LOGGING
	FDebug::LogFormattedMessageWithCallstack(LogAndroid.GetCategoryName(), __FILE__, __LINE__, TEXT("=== Critical error: ==="), GErrorHist, ELogVerbosity::Error);
#endif
	
	GLog->Panic();

	FCoreDelegates::OnHandleSystemError.Broadcast();
	FCoreDelegates::OnShutdownAfterError.Broadcast();
}


void FMyUnrealCrasherAndroidErrorOutputDevice::RequestExit( bool Force, const TCHAR* CallSite)
{

#if PLATFORM_COMPILER_OPTIMIZATION_PG_PROFILING
	// Write the PGO profiling file on a clean shutdown.
	extern void PGO_WriteFile();
	if (!GIsCriticalError)
	{
		PGO_WriteFile();
		// exit now to avoid a possible second PGO write when AndroidMain exits.
		Force = true;
	}
#endif

	UE_LOG(LogAndroid, Log, TEXT("FMyUnrealCrasherAndroidErrorOutputDevice::RequestExit(%i, %s)"), Force,
		CallSite ? CallSite : TEXT("<NoCallSiteInfo>"));
	if (GLog)
	{
		GLog->Flush();
	}

	if (Force)
	{
		abort(); // Abort to trigger a crash report
	}
	else
	{
		RequestEngineExit(TEXT("Android RequestExitWithCrashReporting")); // Called regardless in our version to set up the crash context
	}
}
#endif
