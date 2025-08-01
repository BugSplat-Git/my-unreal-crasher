//  Copyright © BugSplat. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyUnrealCrasherGameInstance.generated.h"

UCLASS()
class MYUNREALCRASHER_API UMyUnrealCrasherGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
};
