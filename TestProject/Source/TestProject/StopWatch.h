// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// 타이머 측정 클래스 입니다
// 플레이어의 조작으로 움직이며 P 키를 가지고 play pause가 가능하고
// O 키를 가지고 Reset이 가능 


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StopWatch.generated.h"
UENUM(BluePrintType)
enum class  WatchState :uint8 // 타이머의 상태를 나타내는 열거체
{
	e_Reset = 0 UMETA(DisplayName = "RESET"),
	e_Pause  UMETA(DisplayName = "PAUSE"),
	e_Play UMETA(DisplayName="PLAY")

};
UCLASS()
class TESTPROJECT_API AStopWatch : public AActor
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = TIMER)
	int Minutes; // 분
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = TIMER)
	int Seconds; // 초

	WatchState CurrentState; // 현재 타이머의 상태
protected:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = UI)
	TSubclassOf<class UTimerWidget> TimerWidgetClass;   //타이머 위젯 클래스 
private:

	FTimerHandle TimerHandle; // TimerHandle;

	UPROPERTY()
	class UTimerWidget* TimerWidget; //타이머 위젯
public:	
	// Sets default values for this actor's properties
	AStopWatch();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateTimerWidget(); //타이머 위젯 생성
	void WatchControl();  // 타이머 조작
	void WatchReset(); // 타이머 리셋
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void WatchPlay();  // 타이머 재생 


};
