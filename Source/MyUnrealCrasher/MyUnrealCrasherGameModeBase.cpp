// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyUnrealCrasherGameModeBase.h"
#include "BugSplatAttributes.h"

AMyUnrealCrasherGameModeBase::AMyUnrealCrasherGameModeBase()
{
	// Your BugSplat initialization code here
	UE_LOG(LogTemp, Log, TEXT("MyUnrealCrasherGameModeBase is initializing!"));

	// BugSplat Key field - used to display different flavors of the support response page at crash time
	UBugSplatAttributes::SetAttribute(TEXT("BugSplatApplicationKey"), TEXT("en-US"));

	// BugSplat Notes field - used for arbitrary extra crash context
	UBugSplatAttributes::SetAttribute(TEXT("BugSplatNotes"), TEXT("Development Build"));

	// Custom attributes will be included in crash reports on all platforms
	UBugSplatAttributes::SetAttribute(TEXT("CurrentWorld"), TEXT("Alpha Centari"));
	UBugSplatAttributes::SetAttribute(TEXT("GamePads"), TEXT("1"));
	UBugSplatAttributes::SetAttribute(TEXT("IsExternalQABuild"), TEXT("true"));
}