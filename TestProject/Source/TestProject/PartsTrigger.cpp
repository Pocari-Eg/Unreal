// Fill out your copyright notice in the Description page of Project Settings.


#include "PartsTrigger.h"
#include "PartsObject.h"
// Sets default values
APartsTrigger::APartsTrigger()
{
	//초기 세팅
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
	//이 트리거가 첫번쨰 트리거이면 , 첫번째 오브젝트를 움직이기 시작
	if (IsStartTrigger) {
		UE_LOG(LogTemp, Error, TEXT("StartTrigger Hit"));
		if (StartObject != nullptr)
		{
			StartObject->ForwardMove(this);
			TriggerOff();
		}
	}
	else {
		//첫번째 트리거가 아니라면 오브젝트의 되돌아가는것을 막음
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