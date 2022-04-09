// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include <Kismet/KismetSystemLibrary.h>
// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//����ƽ �޽� �ʱ�ȭ
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;
	
	//static ConstructorHelpers::FObjectFinder<UStaticMesh>ST_MESH(TEXT("path"));
	//if (ST_MESH.Succeeded())
	//{
	//	Mesh->SetStaticMesh(ST_MESH.Object);
	//}

	//����Ʈ ���� �ʱ�ȭ
	PointIndex = 0;
	IsFoward = true;

	//MoveComponentTo �Լ��� ȣ��Ǿ� ���� �Ϸ��� MovePlatform �Լ��� ����� �ɼ� �ֵ���
	info.CallbackTarget = this;
	info.UUID = GetUniqueID();
	info.ExecutionFunction = "MovePlatform";
	info.Linkage = 0;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	//���� �ʱ� ��ġ�� �� ó����ġ�� ����
	PlatformPoint.Insert(GetActorLocation(), 0);

	if (IsMoveStarting) MovePlatform();
}
//IsFoward�� true�̸� ������ false�̸� ������ �̵� 
void AMovingPlatform::MovePlatform()
{		
	IsFoward == true ? MoveFoward() : MoveBackWard();
}

void AMovingPlatform::MoveFoward()
{
	//Point �迭�� ���� 0���� ������� �̵�
	PointIndex++;
	if (PointIndex < PlatformPoint.Num()) {
		//�ش� Location ���� �����δ�. ������ info ����ü�� ������Ǿ��ִ� �Լ��� ����
		UKismetSystemLibrary::MoveComponentTo(RootComponent, PlatformPoint[PointIndex],
			GetActorRotation(), false, false, MoveTime, false, EMoveComponentAction::Move, info);
	}
	else {
		//���� ������ ���� ���������Ƿ� �������� �ɼ��ֵ���
		IsFoward = false;
		PointIndex = PlatformPoint.Num() - 1;
		UKismetSystemLibrary::MoveComponentTo(RootComponent, GetActorLocation(),
			GetActorRotation(), false, false, DelayTime, false, EMoveComponentAction::Move, info);
	}

}

void AMovingPlatform::MoveBackWard()
{
	//Point �迭�� ���� ���������� ��������� �̵�

	PointIndex--;
	if (PointIndex >= 0)
	{		
		UKismetSystemLibrary::MoveComponentTo(RootComponent, PlatformPoint[PointIndex],
			GetActorRotation(), false, false, MoveTime, false, EMoveComponentAction::Move, info);
	}
	else {
		//ù ������ ���� ���������Ƿ� �������� �ɼ��ֵ���
		IsFoward = true;
		PointIndex = 0;
		UKismetSystemLibrary::MoveComponentTo(RootComponent, GetActorLocation(),
			GetActorRotation(), false, false, DelayTime, false, EMoveComponentAction::Move, info);
	}
}

