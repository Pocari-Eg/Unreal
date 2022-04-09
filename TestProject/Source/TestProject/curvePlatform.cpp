// Fill out your copyright notice in the Description page of Project Settings.


#include "curvePlatform.h"

// Sets default values
AcurvePlatform::AcurvePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//���� ����
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
	//ó�� ������ ����� ���·� ����
	IsActorClose = true;
}



// Called when the game starts or when spawned
void AcurvePlatform::BeginPlay()
{
	Super::BeginPlay();
	
	//MovePlatform();
}

//�̵����� �Լ� 
#pragma region PlatfomrMove
void AcurvePlatform::MovePlatform()
{
	//������ MoveToFar�� Time�� ���� ���� , �ָ������� MoveToClose�� Time�� ���� ���� 
	IsActorClose == true ? GetWorldTimerManager().SetTimer(TimerHandle, this, &AcurvePlatform::MoveToFar, Time, true, 0.0f) :
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AcurvePlatform::MoveToClose, Time, true, 0.0f);
}


void AcurvePlatform::MoveToFar()
{
	//��ο� 100% �������� ��������
	if (Percent < 1.0f) {
		// ���ǵ常ŭ �ۼ�Ʈ �߰� 
		Percent += Speed;
		//��ο� ���̿��� Percent��ŭ ������ �Ÿ��� ����
		float Distance = FMath::Lerp(0.0f, Track->GetSplineLength(), Percent);

		// ��ο� �� Distance��ŭ �̵��� ��ǥ�� ȸ���� �޾ƿ�.
		FVector NewLocation = Track->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);
	     FRotator NewRotation = Track->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);
		 
		//�� ��ǥ�� ȸ�� ����
		 Mesh->SetRelativeLocationAndRotation(NewLocation, NewRotation);
	}
	else {
		//�ʴ� ���� ����
		GetWorldTimerManager().ClearTimer(TimerHandle);
		//������ ���������Ƿ� percent�� 1.0���� ����
		Percent=1.0f;
		// ���� ��ü�� �ָ� �ִ�.
		IsActorClose = false;
	}
}

void AcurvePlatform::MoveToClose()
{
	//MoveToFar �� ���´� ���� 1.0 -> 0.0f ���� �̵�.
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




