// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Ÿ�̸� ���� Ŭ���� �Դϴ�
// �÷��̾��� �������� �����̸� P Ű�� ������ play pause�� �����ϰ�
// O Ű�� ������ Reset�� ���� 


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StopWatch.generated.h"
UENUM(BluePrintType)
enum class  WatchState :uint8 // Ÿ�̸��� ���¸� ��Ÿ���� ����ü
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
	int Minutes; // ��
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = TIMER)
	int Seconds; // ��

	WatchState CurrentState; // ���� Ÿ�̸��� ����
protected:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = UI)
	TSubclassOf<class UTimerWidget> TimerWidgetClass;   //Ÿ�̸� ���� Ŭ���� 
private:

	FTimerHandle TimerHandle; // TimerHandle;

	UPROPERTY()
	class UTimerWidget* TimerWidget; //Ÿ�̸� ����
public:	
	// Sets default values for this actor's properties
	AStopWatch();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateTimerWidget(); //Ÿ�̸� ���� ����
	void WatchControl();  // Ÿ�̸� ����
	void WatchReset(); // Ÿ�̸� ����
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void WatchPlay();  // Ÿ�̸� ��� 


};
