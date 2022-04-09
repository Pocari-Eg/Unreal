// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject.h"
#include "GameFramework/Actor.h"
#include <Engine/Classes/Components/CapsuleComponent.h>
#include <Engine/Classes/Components/BoxComponent.h> // �׽�Ʈ

//
#include "curvePlatform.h"

//���� ����
#include "Components/WidgetComponent.h"
#include "DialogWidget.h"

#include "MyPawn.h" // ĳ���� �������� �ٲ���� 
#include "DestoryObject.generated.h"

UCLASS()
class TESTPROJECT_API ADestoryObject : public AActor
{
	GENERATED_BODY()
	
	
public:



	UPROPERTY(VisibleAnyWhere, Category = Mesh)
	UCapsuleComponent* Trigger; //�ݸ��� ���߿� ���ϴ� ������� ����
	UPROPERTY(VisibleAnyWhere, Category = Mesh)
	UStaticMeshComponent* Mesh; // �޽� 

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = TYPE); //���� Ÿ�� 
	KEYWORD KeyWord;



#pragma region CurvePlatform
	//�����̴� �÷��� ����
	//���� ChildActor�� ������ CurvePlatform ��
	UPROPERTY(VisibleAnyWhere, Category = PLATFORM);
    int32 Count;
	//childActor�� ��ƿ� �迭
	TArray<AActor*> ChildActors;
	//ChildActor�� Cast�Ͽ� ���� �迭
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = PLATFORM);
	TArray<AcurvePlatform*> CurvePlatfomrs;

	//�Ʒ��ǰ����� Curveplatform�� ���� ����
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
	//�浹 ����
	UFUNCTION()
	void OnAttackedOverlap(UPrimitiveComponent* OverlappedComp,AActor* OtherActor,
		UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);


	virtual void Tick(float DeltaTime) override;


	// Dialog Widget

	//�ؽ�Ʈ ��������
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* DialogWidget;
};
