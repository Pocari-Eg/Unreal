// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackTestObejct.h"
#include <Engine/Classes/Camera/CameraComponent.h>
// Sets default values
AAttackTestObejct::AAttackTestObejct()
{

	AutoPossessPlayer = EAutoReceiveInput::Player0;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Trigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TRIGGER"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(RootComponent);


	
	// ī�޶�� ���̴� ������Ʈ�� ����ϴ�
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));

	// ��Ʈ ������Ʈ�� ī�޶�� ���̴� ������Ʈ�� ���Դϴ�. ī�޶� �̰� �� ȸ����ŵ�ϴ�.
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-25.0f, 0.0f, 0.0f));



	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_MESH(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (SM_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(SM_MESH.Object);
	}

	Trigger->SetCollisionProfileName(TEXT("AttackTest"));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void AAttackTestObejct::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAttackTestObejct::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveX", this, &AAttackTestObejct::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &AAttackTestObejct::Move_YAxis);
}

// Called every frame
void AAttackTestObejct::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}


}
void AAttackTestObejct::Move_XAxis(float AxisValue)
{
	// �ʴ� 100 ������ �� �Ǵ� �ڷ� �����Դϴ�

	
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AAttackTestObejct::Move_YAxis(float AxisValue)
{

	// �ʴ� 100 ������ ������ �Ǵ� �������� �����Դϴ�
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}
