// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

static void MYUNREALPLUGIN_API Crash();

class FMyUnrealPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static void MYUNREALPLUGIN_API PluginCrash();

private:
	/** Handle to the test dll we will load */
	void*	ExampleLibraryHandle;
};
