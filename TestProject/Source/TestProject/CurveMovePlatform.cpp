// Fill out your copyright notice in the Description page of Project Settings.


#include "CurveMovePlatform.h"

// Sets default values for this component's properties
UCurveMovePlatform::UCurveMovePlatform()
{

	PrimaryComponentTick.bCanEverTick = false;
	Track = CreateDefaultSubobject<USplineComponent>(TEXT("TRACK"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>ST_MESH(TEXT("/Engine/VREditor/BasicMeshes/SM_Cube_01.SM_Cube_01"));
	if (ST_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(ST_MESH.Object);
	}


	Mesh->SetupAttachment(Track);
	Mesh->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);

	Percent = 0.0f;
}


// Called when the game starts
void UCurveMovePlatform::BeginPlay()
{
	Super::BeginPlay();

	
}

void UCurveMovePlatform::MoveToFar()
{
	if (Percent < 1.0f) {
		Percent += Speed;
		float Distance = FMath::Lerp(0.0f, Track->GetSplineLength(), Percent);

		FVector NewLocation = Track->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
		FRotator NewRotation = Track->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);


		Mesh->SetRelativeLocationAndRotation(NewLocation, NewRotation);
	}
	else {
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		Percent = 1.0f;
	}
}

void UCurveMovePlatform::MoveToClose()
{
	if (Percent > 0.0f) {
		Percent -= Speed;
		float Distance = FMath::Lerp(0.0f, Track->GetSplineLength(), Percent);

		FVector NewLocation = Track->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
		FRotator NewRotation = Track->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);


		Mesh->SetRelativeLocationAndRotation(NewLocation, NewRotation);
	}
	else {
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		Percent = 0.0f;
	}
}




