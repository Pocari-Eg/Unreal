// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SplineComponent.h" 

#include "CurveMovePlatform.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTPROJECT_API UCurveMovePlatform : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnyWhere, Category = Mesh)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = INFO)
	USplineComponent* Track;
	UPROPERTY(EditAnywhere, Category = INFO)
	float Speed;

private:
	UPROPERTY(EditAnywhere, Category = INFO, Meta = (AllowPrivateAccess = true))
	float Percent;

	FTimerHandle TimerHandle;

public:
	// Sets default values for this actor's properties
	UCurveMovePlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void MoveToFar();
	void MoveToClose();



		
};
