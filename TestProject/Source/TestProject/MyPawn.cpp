// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include"PauseWidget.h"


#include <FMODAudioComponent.h>
// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


    // Set this pawn to be controlled by the lowest-numbered player
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    // Create a dummy root component we can attach things to.
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // Create a camera and a visible object
    OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
    OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
    // Attach our camera and visible object to our root component. Offset and rotate the camera.
    OurCamera->SetupAttachment(RootComponent);
    OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
    OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
    OurVisibleComponent->SetupAttachment(RootComponent);

    Trigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TRIGGER"));
    Trigger->SetupAttachment(RootComponent);

    Trigger->SetCollisionProfileName(TEXT("AttackTest"));
  
  
    
    //widget
    static ConstructorHelpers::FClassFinder<UPauseWidget>PAUSEWIDGET(TEXT("/Game/UI/BP_PauseWidget.BP_PauseWidget_C"));
    if (PAUSEWIDGET.Succeeded())
    {
        PauseWidgetClass = PAUSEWIDGET.Class;
    }

    
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
    //StopWatch = GetWorld()->SpawnActor<AStopWatch>(FVector::ZeroVector, FRotator::ZeroRotator);
   // StopWatch->CreateTimerWidget();

    PauseWidget = CreateWidget<UPauseWidget>(GetWorld(), PauseWidgetClass);
 

  /* 
    WalkSound = new MyClass(WalkEvent, GetWorld());
    BgmSound = new MyClass(BgmEvent, GetWorld());
    BgmSound->SoundPlay2D();
    WalkSound->SetVolume(2.0f);
    WalkSound->SetParameter("Surface", 2.0f);
    BgmSound->SetVolume(0.4f);*/
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!CurrentVelocity.IsZero())
    {
        FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
        SetActorLocation(NewLocation);
    }
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    // Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
    InputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
    InputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);

    InputComponent->BindAction("WatchControl", IE_Pressed, this, &AMyPawn::WatchContorl);
    InputComponent->BindAction("WatchReset", IE_Pressed, this, &AMyPawn::WatchReset);

    InputComponent->BindAction("CursorOn", IE_Pressed, this, &AMyPawn::MouseCursorOnOff);
}

void AMyPawn::Move_XAxis(float AxisValue)
{
    
    CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 200.0f;
    

}

void AMyPawn::Move_YAxis(float AxisValue)
{
    CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 200.0f;

    
 
}

void AMyPawn::WatchContorl()
{
   // WalkSound->SoundPlay3D(GetActorTransform());
   //StopWatch->WatchControl();
   
  
}

void AMyPawn::WatchReset()
{
   
   /* WalkSound->SetVolume(2.0f);
    BgmSound->SetParameter("Intensity",2.0f);

    WalkSound->SetParameter("Surface", 0.0f);*/
    

    //if (StopWatch->CurrentState == WatchState::e_Pause) { // 타이머가 pause 상태일때만 Reset 할수 있도록 
    //    StopWatch->WatchReset();
    //}
    //else {

    //}
}

void AMyPawn::MouseCursorOnOff()
{
    bool IsShow = GetWorld()->GetFirstPlayerController()->bShowMouseCursor;
    if (!IsShow) {

        PauseWidget->WidgetOn();

    }
}




