// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject.h"
#include "GameFramework/Actor.h"
#include <Engine/Classes/Components/CapsuleComponent.h>
#include <Engine/Classes/Components/BoxComponent.h> // 테스트

//
#include "curvePlatform.h"

//위젯 관련
#include "Components/WidgetComponent.h"
#include "DialogWidget.h"

#include "MyPawn.h" // 캐릭터 공격으로 바꿔야함 
#include "DestoryObject.generated.h"

UCLASS()
class TESTPROJECT_API ADestoryObject : public AActor
{
	GENERATED_BODY()
	
	
public:



	UPROPERTY(VisibleAnyWhere, Category = Mesh)
	UCapsuleComponent* Trigger; //콜리전 나중에 원하는 모양으로 수정
	UPROPERTY(VisibleAnyWhere, Category = Mesh)
	UStaticMeshComponent* Mesh; // 메쉬 

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = TYPE); //어택 타입 
	KEYWORD KeyWord;



#pragma region CurvePlatform
	//움직이는 플랫폼 관련
	//현재 ChildActor로 배정된 CurvePlatform 수
	UPROPERTY(VisibleAnyWhere, Category = PLATFORM);
    int32 Count;
	//childActor를 담아올 배열
	TArray<AActor*> ChildActors;
	//ChildActor를 Cast하여 담을 배열
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = PLATFORM);
	TArray<AcurvePlatform*> CurvePlatfomrs;

	//아래의값으로 Curveplatform의 세팅 설정
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = PLATFORM);
     float Speed;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = PLATFORM);
	 float Time;
#pragma endregion


public:	
	// Sets default values for this actor's properties
	ADestoryObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;

public:	
	//충돌 관련
	UFUNCTION()
	void OnAttackedOverlap(UPrimitiveComponent* OverlappedComp,AActor* OtherActor,
		UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);


	virtual void Tick(float DeltaTime) override;


	// Dialog Widget

	//텍스트 위젯관련
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* DialogWidget;
};
