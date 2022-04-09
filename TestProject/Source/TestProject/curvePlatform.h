// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h" 
#include "curvePlatform.generated.h"

UCLASS()
class TESTPROJECT_API AcurvePlatform : public AActor
{
	GENERATED_BODY()
	
public:
	//��ü�� ���ʿ� �ѹ��� �̵� ��ų ���ΰ�
	UPROPERTY(EditAnywhere,Category=Platform)
	float Time;
	//��ü�� �ѹ� �̵��Ҷ� �󸶳� �̵��Ұ��ΰ�.
	UPROPERTY(EditAnywhere, Category = Platform)
	float Speed;
private:

	//�޽�
	UStaticMeshComponent* Mesh;
	//��� Spline
	USplineComponent* Track;
	
	//��ο� �� % ���� ������
	float Percent;

	//������ ������Ʈ�� ��ó�� �ִ��� 
	bool IsActorClose;
	// Timer
	FTimerHandle TimerHandle;
public:	
	// Sets default values for this actor's properties
	AcurvePlatform();
	
	//��ü �̵� 
	void MovePlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//��ü �ָ� ������ �̵�
	void MoveToFar();
	//�ָ��ִ� ��ü�� �ٽ� ���ڸ���
	void MoveToClose();

};
