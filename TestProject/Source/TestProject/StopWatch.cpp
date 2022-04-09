// Fill out your copyright notice in the Description page of Project Settings.


#include "StopWatch.h"
#include "TimerWidget.h"
// Sets default values
AStopWatch::AStopWatch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	static ConstructorHelpers::FClassFinder<UTimerWidget>UI_TIMERWIDGET_C(TEXT("/Game/UI/BP_TimerWidget.BP_TimerWidget_C"));
	if (UI_TIMERWIDGET_C.Succeeded())
	{
		TimerWidgetClass = UI_TIMERWIDGET_C.Class;
	}

}

// Called when the game starts or when spawned
void AStopWatch::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStopWatch::WatchPlay() // 타이머 재생 
{
	if (Seconds != 59)
	{
		Seconds += 1;
	}
	else {
		Minutes += 1;
		Seconds = 0;
	}
	TimerWidget->TimerMinutes = Minutes;
	TimerWidget->TimerSeconds = Seconds;
}

void AStopWatch::WatchReset() // 타이머 리셋 
{
	CurrentState = WatchState::e_Reset;
	TimerWidget->CurrentState = CurrentState;
	Minutes = 0;
	Seconds = 0;
	TimerWidget->TimerMinutes = Minutes;
	TimerWidget->TimerSeconds = Seconds;
}

void AStopWatch::WatchControl() // 타이머 조작 
{
	switch (CurrentState)
	{
	case WatchState::e_Reset:
		CurrentState = WatchState::e_Play;
		TimerWidget->CurrentState = CurrentState;

		GetWorldTimerManager().SetTimer(TimerHandle, this, &AStopWatch::WatchPlay, 1.0f, true, 0.0f);	
		break;
	case WatchState::e_Play:
		CurrentState = WatchState::e_Pause;
		TimerWidget->CurrentState = CurrentState;
		GetWorldTimerManager().ClearTimer(TimerHandle);
		break;
	case WatchState::e_Pause:
		CurrentState = WatchState::e_Play;
		TimerWidget->CurrentState = CurrentState;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AStopWatch::WatchPlay, 1.0f, true, 0.0f);
		break;
	default:
		break;
	}

}



// Called every frame
void AStopWatch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStopWatch::CreateTimerWidget()
{
	TimerWidget = CreateWidget<UTimerWidget>(GetGameInstance(), TimerWidgetClass);
	TimerWidget->AddToViewport();

	WatchReset();
}

