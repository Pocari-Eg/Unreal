// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class TESTPROJECT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()

	
public:
	//스태틱 메쉬
	UPROPERTY(VisibleAnyWhere, Category = Mesh)
	UStaticMeshComponent* Mesh;
	
	//움직일 포인트
	UPROPERTY(EditAnywhere,BluePrintReadWrite ,Category = Move)
	TArray<FVector> PlatformPoint;

private:
	// 플랫폼이 최종 종점에 도착했을때 멈출 시간
	UPROPERTY(EditAnywhere, Category = Move)
	float DelayTime;
	//포인트간 움직임이 몇초안에 일어나야 할것인지
	UPROPERTY(EditAnywhere, Category = Move)
	float MoveTime;



	//움직일 Point의 index
	int32 PointIndex;
	//Move
	//플랫폼의 움직임후 어떤 상호작용을 할것인지
	FLatentActionInfo info;
	//움직임 방향 전환
	bool IsFoward;

	//게임 시작시 바로 움직이게
	UPROPERTY(EditAnywhere, Category = Move)
	bool IsMoveStarting;


	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	//발판을 이동시키는 함수
	UFUNCTION(BlueprintCallable)
	void MovePlatform();

private:
	//정방향으로 움직이는 함수
	void MoveFoward();
	//역방향으로 움직이는 함수
	void MoveBackWard();
};
