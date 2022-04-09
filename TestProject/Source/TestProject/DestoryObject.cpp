// Fill out your copyright notice in the Description page of Project Settings.


#include "DestoryObject.h"
#include <Engine/Classes/Kismet/KismetMathLibrary.h>
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"
// Sets default values
ADestoryObject::ADestoryObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TRIGGER"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	//자식 플랫폼
	
	
	RootComponent = Trigger;
	Mesh->SetupAttachment(RootComponent);

	

	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_MESH(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (SM_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(SM_MESH.Object);
	}

	Trigger->SetCollisionProfileName(TEXT("DestroyObject"));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	

#pragma region DialogWidget
	//Dialog관련
	DialogWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DIALOGWIDGET"));
	DialogWidget->SetupAttachment(Mesh);
	DialogWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));
	DialogWidget->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	DialogWidget->SetWidgetSpace(EWidgetSpace::World);

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_DIALOGWIDGET(TEXT("/Game/UI/BP_DialogWidget.BP_DialogWidget_C"));

	if (UI_DIALOGWIDGET.Succeeded()) {

		DialogWidget->SetWidgetClass(UI_DIALOGWIDGET.Class);
		DialogWidget->SetDrawSize(FVector2D(200.0f, 50.0f));

	}
	
#pragma endregion
	//자식 플랫폼

	
	
}

// Called when the game starts or when spawned
void ADestoryObject::BeginPlay()
{
	Super::BeginPlay();	
	
	auto Dialog = Cast<UDialogWidget>(DialogWidget->GetUserWidgetObject());
	Dialog->SetVisibility(ESlateVisibility::Hidden);
	if (nullptr != Dialog)
	{
		auto instance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		Dialog->SetDialog(instance->GetMonsterData(MonsterState::Detected)->Script);
	}

	//Child Actor를 가져오고, Cast 시켜 저장
	GetAllChildActors(ChildActors, true);
	Count = ChildActors.Num();

	if (Count != 0) {
		for (int i = 0; i < Count; i++)
		{
			CurvePlatfomrs.Add(Cast<AcurvePlatform>(ChildActors[i]));
			CurvePlatfomrs[i]->Speed = Speed;
			CurvePlatfomrs[i]->Time = Time;
		}
	}
}

void ADestoryObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//충돌 델리게이트
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ADestoryObject::OnAttackedOverlap);
}
void ADestoryObject::OnAttackedOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	

	auto Attack = Cast<AMyPawn>(OtherActor);  // 부딫힌 오브젝트를 해당 캐릭터로 캐스팅 
	

	//키워드에 따라 다른 동작으로 변경
	UE_LOG(LogTemp, Error, TEXT("HIT"));
	switch (Attack->KeyWord)
	{
	//키워드가 같은 키워드이면 무시, 다른 키워드이면 공격키워드로 변경하고 행동 실행
	case KEYWORD::e_Fire:

		if (this->KeyWord != KEYWORD::e_Fire) {
			this->KeyWord = KEYWORD::e_Fire;
			for (int i = 0; i < Count; i++)
			{
				CurvePlatfomrs[i]->MovePlatform();
			}
		}
		else {

		}
	
		break;
	case KEYWORD::e_Water:

		if (this->KeyWord != KEYWORD::e_Water) {
			this->KeyWord = KEYWORD::e_Water;
			for (int i = 0; i < Count; i++)
			{
				CurvePlatfomrs[i]->MovePlatform();
			}
		}
		else {

		}
		break;
	default:
		break;
	}

	


}

void ADestoryObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//플레이어의 카메라 좌표와 현재 위젯의 좌표를 통해 위젯이 카메라를 바라보도록 
	FRotator CameraRot = UKismetMathLibrary::FindLookAtRotation(DialogWidget->GetComponentTransform().GetLocation(),UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation());

	// Yaw 값만 변환하여 위젯이 카메라를 따라옴
	DialogWidget->SetWorldRotation(FRotator(0.0f, CameraRot.Yaw, 0.0f));

}


// Called every frame

