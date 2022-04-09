// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "PartsTrigger.generated.h"

class APartsObject;
UCLASS()
class TESTPROJECT_API APartsTrigger : public AActor
{
	GENERATED_BODY()

public:
	//트리거
	UPROPERTY(EditAnywhere, Category = Trigger)
	UBoxComponent* Trigger;

	//처음 움직일 오브젝트 저장
	UPROPERTY(EditAnywhere, Category = Object)
	APartsObject* StartObject;

	//마지막 움직일 오브젝트 저장
	UPROPERTY(EditAnywhere, Category = Object)
	APartsObject* EndObject;

	//이 트리거가 첫 이벤트인지 여부
	UPROPERTY(EditAnywhere, Category = Object)
	bool IsStartTrigger;

	
public:	
	// Sets default values for this actor's properties
	APartsTrigger();
	// 충돌 함수
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	//트리거 Off
	void TriggerOff();

	//트리거 on
	void TriggerOn();

};
