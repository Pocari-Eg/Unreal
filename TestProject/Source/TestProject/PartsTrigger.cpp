// Fill out your copyright notice in the Description page of Project Settings.


#include "PartsTrigger.h"
#include "PartsObject.h"
// Sets default values
APartsTrigger::APartsTrigger()
{
	//�ʱ� ����
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	RootComponent = Trigger;

	Trigger->SetCollisionProfileName(TEXT("Trigger"));
}



// Called when the game starts or when spawned
void APartsTrigger::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &APartsTrigger::OnBeginOverlap);

}



void APartsTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//�� Ʈ���Ű� ù���� Ʈ�����̸� , ù��° ������Ʈ�� �����̱� ����
	if (IsStartTrigger) {
		UE_LOG(LogTemp, Error, TEXT("StartTrigger Hit"));
		if (StartObject != nullptr)
		{
			StartObject->ForwardMove(this);
			TriggerOff();
		}
	}
	else {
		//ù��° Ʈ���Ű� �ƴ϶�� ������Ʈ�� �ǵ��ư��°��� ����
		UE_LOG(LogTemp, Error, TEXT("EndTrigger Hit"));
		if (EndObject != nullptr)
		{
			EndObject->IsEndTriggerOn = true;
			TriggerOff();
		}
	}
}

void APartsTrigger::TriggerOff()
{
	Trigger->SetGenerateOverlapEvents(false);
}

void APartsTrigger::TriggerOn()
{
	Trigger->SetGenerateOverlapEvents(true);
}