// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARENAHONG_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	IOnlineSessionPtr SessionInterface;

	void CreateSession(FString roomName, int32 playerCount);

	UFUNCTION()
	void CreateSessionComplete(FName SessionName, bool bWasSuccessful);

	FString MySessionName = TEXT("MySession");
};
