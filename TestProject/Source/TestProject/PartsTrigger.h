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
	//Ʈ����
	UPROPERTY(EditAnywhere, Category = Trigger)
	UBoxComponent* Trigger;

	//ó�� ������ ������Ʈ ����
	UPROPERTY(EditAnywhere, Category = Object)
	APartsObject* StartObject;

	//������ ������ ������Ʈ ����
	UPROPERTY(EditAnywhere, Category = Object)
	APartsObject* EndObject;

	//�� Ʈ���Ű� ù �̺�Ʈ���� ����
	UPROPERTY(EditAnywhere, Category = Object)
	bool IsStartTrigger;

	
public:	
	// Sets default values for this actor's properties
	APartsTrigger();
	// �浹 �Լ�
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	//Ʈ���� Off
	void TriggerOff();

	//Ʈ���� on
	void TriggerOn();

};
