// Fill out your copyright notice in the Description page of Project Settings.


#include "curvePlatform.h"

// Sets default values
AcurvePlatform::AcurvePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//기초 세팅
	Track = CreateDefaultSubobject<USplineComponent>(TEXT("TRACK"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Track;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>ST_MESH(TEXT("/Engine/VREditor/BasicMeshes/SM_Cube_01.SM_Cube_01"));
	if (ST_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(ST_MESH.Object);
	}

	
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);

	Percent = 0.0f;
	Time = 0.0f;
	//처음 시작은 가까운 상태로 시작
	IsActorClose = true;
}



// Called when the game starts or when spawned
void AcurvePlatform::BeginPlay()
{
	Super::BeginPlay();
	
	//MovePlatform();
}

//이동관련 함수 
#pragma region PlatfomrMove
void AcurvePlatform::MovePlatform()
{
	//가까우면 MoveToFar를 Time초 마다 실행 , 멀리있으면 MoveToClose를 Time초 마다 실행 
	IsActorClose == true ? GetWorldTimerManager().SetTimer(TimerHandle, this, &AcurvePlatform::MoveToFar, Time, true, 0.0f) :
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AcurvePlatform::MoveToClose, Time, true, 0.0f);
}


void AcurvePlatform::MoveToFar()
{
	//경로에 100% 도달하지 못했으면
	if (Percent < 1.0f) {
		// 스피드만큼 퍼센트 추가 
		Percent += Speed;
		//경로에 길이에서 Percent만큼 움직인 거리를 측정
		float Distance = FMath::Lerp(0.0f, Track->GetSplineLength(), Percent);

		// 경로에 서 Distance만큼 이동한 좌표와 회전을 받아옴.
		FVector NewLocation = Track->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);
	     FRotator NewRotation = Track->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);
		 
		//새 좌표와 회전 적용
		 Mesh->SetRelativeLocationAndRotation(NewLocation, NewRotation);
	}
	else {
		//초당 실행 종료
		GetWorldTimerManager().ClearTimer(TimerHandle);
		//최종에 도달했으므로 percent를 1.0으로 세팅
		Percent=1.0f;
		// 이제 물체가 멀리 있다.
		IsActorClose = false;
	}
}

void AcurvePlatform::MoveToClose()
{
	//MoveToFar 와 형태는 같고 1.0 -> 0.0f 으로 이동.
	if (Percent > 0.0f) {
		Percent -= Speed;
		float Distance = FMath::Lerp(0.0f, Track->GetSplineLength(), Percent);

		FVector NewLocation = Track->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);
		FRotator NewRotation = Track->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);


		Mesh->SetRelativeLocationAndRotation(NewLocation, NewRotation);
	}
	else {
		GetWorldTimerManager().ClearTimer(TimerHandle);
		Percent = 0.0f;
		IsActorClose = true;
	}
}
#pragma endregion




