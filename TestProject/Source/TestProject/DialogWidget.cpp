// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogWidget.h"


void UDialogWidget::SetDialog(FString dialog)
{
	//메시지를 담아온다
	InputDialog = dialog;
	Length = 0;

	SetVisibility(ESlateVisibility::Visible);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UDialogWidget::PlayDialog, 0.2f, true, 0.0f);
}

void UDialogWidget::PlayDialog()
{

	//현재 출력된 메시지가 전부 출력되면
	 if (InputDialog.Len()+2 <= Length)
	{
		
		 if (TextPrintTime > 0.0f)
		 {
			 TextPrintTime -= 0.2f;
			
		 }
		 else {
			 SetVisibility(ESlateVisibility::Hidden);
			 //타이머 초기화로 
			 GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

		 }
		
	}
	 else 	if (InputDialog.Len() + 2 > Length)
	{
		for (int i = 0; i < Length; i++)
		{
			//Ouptdialog에 있는 문자열이 UI에 표시되므로 Inputdialog에서 한글자씩 받아옴
			OutputDialog = *InputDialog.Mid(0, i);
		}
		Length++;
	}
	
}
void UDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();

}
