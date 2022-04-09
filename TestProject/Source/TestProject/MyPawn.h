// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject.h"
#include "GameFramework/Pawn.h"
#include "StopWatch.h"
#include <Engine/Classes/Components/CapsuleComponent.h>
#include <Engine/Classes/Camera/CameraComponent.h>
#include <FMODBlueprintStatics.h>

//ui


#include "MyClass.h"

#include "MyPawn.generated.h"


UCLASS()
class TESTPROJECT_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnyWhere, Category = Mesh)
	UCapsuleComponent* Trigger; //콜리전

    UPROPERTY(EditAnywhere)
    USceneComponent* OurVisibleComponent;
	UPROPERTY(EditAnywhere)
	UCameraComponent* OurCamera;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = TYPE)
	KEYWORD KeyWord;

    // Input functions
    void Move_XAxis(float AxisValue);
    void Move_YAxis(float AxisValue);

    // Input variables
    FVector CurrentVelocity;
	

	UPROPERTY(EditAnywhere, Category = "FMOD")
	class UFMODEvent* BgmEvent;
	UPROPERTY(EditAnywhere, Category = "FMOD")
	class UFMODEvent* WalkEvent;




	MyClass* WalkSound;
	MyClass* BgmSound;
	// StopWatch 타이머 조작 관련 변수 함수 
	//AStopWatch* StopWatch;
	void WatchContorl();
	void WatchReset();



	//위젯


	TSubclassOf<class UPauseWidget> PauseWidgetClass;
	 
	class UPauseWidget* PauseWidget;
	//마우스 커서 
	void MouseCursorOnOff();

};
// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

