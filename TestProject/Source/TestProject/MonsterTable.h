// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MonsterTable.generated.h"

UENUM(BluePrintType)
enum class  MonsterState :uint8
{
	Detected = 0,
	Find,
	Hit

};
/**
 * 
 */
UCLASS()
class TESTPROJECT_API UMonsterTable : public UDataTable
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FMonsterData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DATA);
	FString State;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DATA);
	FString Script;


};