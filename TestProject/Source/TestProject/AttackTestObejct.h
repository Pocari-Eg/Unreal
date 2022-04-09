// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Engine/Classes/Components/CapsuleComponent.h>
#include "AttackTestObejct.generated.h"

//UENUM(BluePrintType)
//enum class  KEYWORD :uint8
//{
//	e_Fire=0 UMETA(DisplayName="FIRE"),
//	e_Water  UMETA(DisplayName = "WATER")
//
//};
UCLASS()
class TESTPROJECT_API AAttackTestObejct : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttackTestObejct();

	UPROPERTY(VisibleAnyWhere, Category = Mesh)
	UCapsuleComponent* Trigger; //콜리전
	UPROPERTY(VisibleAnyWhere, Category = Mesh)
	UStaticMeshComponent* Mesh; // 메쉬 

	/*UPROPERTY(EditAnywhere, BluePrintReadWrite,Category=TYPE);	
	KEYWORD KeyWord;*/
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//이동
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	FVector CurrentVelocity;
};
