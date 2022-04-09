// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Engine/GameInstance.h"
#include "MonsterTable.h"
#include "MyGameInstance.generated.h"




/**
 * 
 */

//template<class T>
UCLASS()
class TESTPROJECT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	UMyGameInstance();

public:
	FMonsterData* GetMonsterData(MonsterState State);



protected:
	virtual void Init() override;
private:
	UPROPERTY()
	class UDataTable* DataTable;


};
