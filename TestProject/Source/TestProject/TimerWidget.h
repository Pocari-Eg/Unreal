// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StopWatch.h"
#include "TimerWidget.generated.h"


/**
 * 
 */
UCLASS()
class TESTPROJECT_API UTimerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BluePrintReadOnly)
	int32 TimerMinutes;
	UPROPERTY(BluePrintReadOnly)
	int32 TimerSeconds;

	UPROPERTY(BluePrintReadOnly)
	WatchState CurrentState;
	
};
