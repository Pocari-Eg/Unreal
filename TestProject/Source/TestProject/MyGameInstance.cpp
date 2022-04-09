// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance(){


	FString MonsterDataPath = "/Game/GameData/MonsterScript.MonsterScript";
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MonsterTable(*MonsterDataPath);

	if (DT_MonsterTable.Succeeded())
	{
		DataTable = DT_MonsterTable.Object;
	}

}

FMonsterData* UMyGameInstance::GetMonsterData(MonsterState State)
{
	return DataTable->FindRow<FMonsterData>(*FString::FromInt((int32)State),TEXT(""));
}


void UMyGameInstance::Init()
{
	Super::Init();

	/*FMonsterData *Data = GetMonsterData(2);
	UE_LOG(LogTemp, Error, TEXT("Code : %d Monster Name : %s, MonterLevel %d"), Data->Code ,*Data->Name, Data->Level);*/

}


