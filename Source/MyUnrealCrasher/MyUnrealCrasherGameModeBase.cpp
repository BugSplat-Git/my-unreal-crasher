// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyUnrealCrasherGameModeBase.h"
#include "GenericPlatform/GenericPlatformCrashContext.h"

AMyUnrealCrasherGameModeBase::AMyUnrealCrasherGameModeBase()
{
	// Your BugSplat initialization code here
	UE_LOG(LogTemp, Log, TEXT("MyUnrealCrasherGameModeBase is initializing!"));

	// BugSplat Key field - used to display different flavors of the support response page at crash time
	FGenericCrashContext::SetGameData(TEXT("BugSplatApplicationKey"), TEXT("en-US"));

	// BugSplat Notes field - used for arbitrary extra crash context
	FGenericCrashContext::SetGameData(TEXT("BugSplatNotes"), TEXT("Development Build"));

	// GameData values will be parsed as Attributes by BugSplat
	FGenericCrashContext::SetGameData(TEXT("CurrentWorld"), TEXT("Alpha Centari"));
	FGenericCrashContext::SetGameData(TEXT("GamePads"), TEXT("1"));
	FGenericCrashContext::SetGameData(TEXT("IsExternalQABuild"), TEXT("true"));
}