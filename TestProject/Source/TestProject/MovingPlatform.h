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
	//����ƽ �޽�
	UPROPERTY(VisibleAnyWhere, Category = Mesh)
	UStaticMeshComponent* Mesh;
	
	//������ ����Ʈ
	UPROPERTY(EditAnywhere,BluePrintReadWrite ,Category = Move)
	TArray<FVector> PlatformPoint;

private:
	// �÷����� ���� ������ ���������� ���� �ð�
	UPROPERTY(EditAnywhere, Category = Move)
	float DelayTime;
	//����Ʈ�� �������� ���ʾȿ� �Ͼ�� �Ұ�����
	UPROPERTY(EditAnywhere, Category = Move)
	float MoveTime;



	//������ Point�� index
	int32 PointIndex;
	//Move
	//�÷����� �������� � ��ȣ�ۿ��� �Ұ�����
	FLatentActionInfo info;
	//������ ���� ��ȯ
	bool IsFoward;

	//���� ���۽� �ٷ� �����̰�
	UPROPERTY(EditAnywhere, Category = Move)
	bool IsMoveStarting;


	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	//������ �̵���Ű�� �Լ�
	UFUNCTION(BlueprintCallable)
	void MovePlatform();

private:
	//���������� �����̴� �Լ�
	void MoveFoward();
	//���������� �����̴� �Լ�
	void MoveBackWard();
};
