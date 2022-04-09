// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "DialogWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UDialogWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	//출력할 메시지 세팅
	void SetDialog(FString dialog);
	//전송된 메시지를 담는 변수
	FString InputDialog;

	//현재까지 출력된 메시지의 길이
	int32 Length;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = Time)
	int32 TextPrintTime;
	//메시지 재생
	void PlayDialog();
	FTimerHandle TimerHandle; // TimerHandle;

	//출력용 변수
	UPROPERTY(BlueprintReadOnly)
	FString OutputDialog;
	
};
