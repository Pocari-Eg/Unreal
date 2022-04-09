// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include <Kismet/KismetSystemLibrary.h>
// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//스태틱 메쉬 초기화
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;
	
	//static ConstructorHelpers::FObjectFinder<UStaticMesh>ST_MESH(TEXT("path"));
	//if (ST_MESH.Succeeded())
	//{
	//	Mesh->SetStaticMesh(ST_MESH.Object);
	//}

	//포인트 정보 초기화
	PointIndex = 0;
	IsFoward = true;

	//MoveComponentTo 함수가 호출되어 역할 완료휴 MovePlatform 함수가 재실행 될수 있도록
	info.CallbackTarget = this;
	info.UUID = GetUniqueID();
	info.ExecutionFunction = "MovePlatform";
	info.Linkage = 0;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	//현재 초기 위치를 맨 처음위치로 설정
	PlatformPoint.Insert(GetActorLocation(), 0);

	if (IsMoveStarting) MovePlatform();
}
//IsFoward가 true이면 정방향 false이면 역방향 이동 
void AMovingPlatform::MovePlatform()
{		
	IsFoward == true ? MoveFoward() : MoveBackWard();
}

void AMovingPlatform::MoveFoward()
{
	//Point 배열에 따라 0부터 순서대로 이동
	PointIndex++;
	if (PointIndex < PlatformPoint.Num()) {
		//해당 Location 까지 움직인다. 끝나면 info 구조체에 ㅅ저장되어있는 함수가 실행
		UKismetSystemLibrary::MoveComponentTo(RootComponent, PlatformPoint[PointIndex],
			GetActorRotation(), false, false, MoveTime, false, EMoveComponentAction::Move, info);
	}
	else {
		//최종 목적지 까지 도달했으므로 역방향이 될수있도록
		IsFoward = false;
		PointIndex = PlatformPoint.Num() - 1;
		UKismetSystemLibrary::MoveComponentTo(RootComponent, GetActorLocation(),
			GetActorRotation(), false, false, DelayTime, false, EMoveComponentAction::Move, info);
	}

}

void AMovingPlatform::MoveBackWard()
{
	//Point 배열에 따라 마지막부터 역순서대로 이동

	PointIndex--;
	if (PointIndex >= 0)
	{		
		UKismetSystemLibrary::MoveComponentTo(RootComponent, PlatformPoint[PointIndex],
			GetActorRotation(), false, false, MoveTime, false, EMoveComponentAction::Move, info);
	}
	else {
		//첫 목적지 까지 도달했으므로 순방향이 될수있도록
		IsFoward = true;
		PointIndex = 0;
		UKismetSystemLibrary::MoveComponentTo(RootComponent, GetActorLocation(),
			GetActorRotation(), false, false, DelayTime, false, EMoveComponentAction::Move, info);
	}
}

