// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyUnrealPlugin.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "MyUnrealPluginLibrary/ExampleLibrary.h"

#define LOCTEXT_NAMESPACE "FMyUnrealPluginModule"

void FMyUnrealPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("MyUnrealPlugin")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/MyUnrealPluginLibrary/Win64/ExampleLibrary.dll"));
#elif PLATFORM_MAC
    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/MyUnrealPluginLibrary/Mac/Release/libExampleLibrary.dylib"));
#elif PLATFORM_LINUX
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/MyUnrealPluginLibrary/Linux/x86_64-unknown-linux-gnu/libExampleLibrary.so"));
#endif // PLATFORM_WINDOWS

	ExampleLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (ExampleLibraryHandle)
	{
		// Call the test function in the third party library that produces a segfault
		ExampleLibraryFunction();
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load example third party library"));
	}
}

void FMyUnrealPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(ExampleLibraryHandle);
	ExampleLibraryHandle = nullptr;
}

void FMyUnrealPluginModule::PluginCrash()
{
	ExampleLibraryCrash();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyUnrealPluginModule, MyUnrealPlugin)
