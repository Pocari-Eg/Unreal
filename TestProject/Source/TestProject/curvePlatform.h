// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h" 
#include "curvePlatform.generated.h"

UCLASS()
class TESTPROJECT_API AcurvePlatform : public AActor
{
	GENERATED_BODY()
	
public:
	//물체를 몇초에 한번씩 이동 시킬 것인가
	UPROPERTY(EditAnywhere,Category=Platform)
	float Time;
	//물체가 한번 이동할때 얼마나 이동할것인가.
	UPROPERTY(EditAnywhere, Category = Platform)
	float Speed;
private:

	//메쉬
	UStaticMeshComponent* Mesh;
	//경로 Spline
	USplineComponent* Track;
	
	//경로에 몇 % 까지 갔는지
	float Percent;

	//움직일 오브젝트가 근처에 있는지 
	bool IsActorClose;
	// Timer
	FTimerHandle TimerHandle;
public:	
	// Sets default values for this actor's properties
	AcurvePlatform();
	
	//물체 이동 
	void MovePlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//물체 멀리 보내는 이동
	void MoveToFar();
	//멀리있는 물체를 다시 제자리로
	void MoveToClose();

};
