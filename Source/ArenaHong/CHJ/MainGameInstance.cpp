// Fill out your copyright notice in the Description page of Project Settings.


#include "../CHJ/MainGameInstance.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "ArenaHong/ArenaHong.h"

void UMainGameInstance::Init()
{
	Super::Init();

	// 온라인 서브시스템 가져온다
	if(IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		SessionInterface = Subsystem->GetSessionInterface();
	}

	SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMainGameInstance::CreateSessionComplete);

	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, [&]()
	{
		CreateSession(MySessionName, 10);
	}, 3.f, false);
}

void UMainGameInstance::CreateSession(FString roomName, int32 playerCount)
{
	FOnlineSessionSettings settings;

	// 1. 전용서버를 사용하는가?
	settings.bIsDedicated = false;

	// 2. 랜선(Lan)으로 매치하는가?
	FName subsysName = IOnlineSubsystem::Get()->GetSubsystemName();
	settings.bIsLANMatch = subsysName == "NULL";

	// 3. 매칭이 공개(true)혹은 비공개(false, 초대를 통해서 매칭)
	settings.bShouldAdvertise = true;

	// 4. 유저의 상태 정보(온라인/자리비움/등등) 사용 여부
	settings.bUsesPresence = true;
	
	// 5. 중간에 난입 가능한가?
	settings.bAllowJoinViaPresence = true;
	settings.bAllowJoinInProgress = true;

	// 6. 최대 인원수
	settings.NumPublicConnections = playerCount;

	// 7. 커스텀 정보
	
	settings.Set(FName("ROOM_NAME") , roomName , EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	settings.Set(FName("HOST_NAME") , MySessionName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	FUniqueNetIdPtr UniqueId = GetWorld()->GetFirstLocalPlayerFromController()->GetUniqueNetIdForPlatformUser().GetUniqueNetId();

	SessionInterface->CreateSession(*UniqueId, FName(MySessionName), settings);
}

void UMainGameInstance::CreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if(bWasSuccessful)
	{
		PRINTLOG(TEXT("CreateSessionComplete success"));
		
	}
	else
	{
		PRINTLOG(TEXT("CreateSessionComplete failed"));
	}
}
