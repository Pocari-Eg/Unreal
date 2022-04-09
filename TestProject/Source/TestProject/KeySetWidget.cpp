// Fill out your copyright notice in the Description page of Project Settings.


#include "KeySetWidget.h"
#include "GameFramework/InputSettings.h"

#include "Components/InputKeySelector.h"

#include "Kismet/KismetInputLibrary.h"
void UKeySetWidget::WidgetOn(UPauseWidget* widget)
{
	PauseWidget = widget;
	PauseWidget->RemoveFromViewport();
	this->AddToViewport();
	
	IsEmptyKey = false;
}

void UKeySetWidget::WidgetOff()
{
	PauseWidget->AddToViewport();
	this->RemoveFromViewport();
	
}

void UKeySetWidget::ChangeKey(const FName ActionName,  UPARAM(ref)FInputChord& InputKey)
{

	TArray< FInputActionKeyMapping> CurrentActionMapping = UInputSettings::GetInputSettings()->GetActionMappings();
	FName SameKeyName;

	for (int i = 0; i < CurrentActionMapping.Num(); i++)
	{
		FInputChord currentkey(CurrentActionMapping[i].Key, CurrentActionMapping[i].bShift, CurrentActionMapping[i].bCtrl, CurrentActionMapping[i].bAlt, CurrentActionMapping[i].bCmd);

		if (InputKey == currentkey)
		{		
			SameKeyName = CurrentActionMapping[i].ActionName;
			TArray<FInputActionKeyMapping> Refresh;
			UInputSettings::GetInputSettings()->GetActionMappingByName(SameKeyName, Refresh);
			UInputSettings::GetInputSettings()->RemoveActionMapping(Refresh[0], false);
			FInputActionKeyMapping Rfreshkey(SameKeyName, NONE, false, false, false, false);
			UInputSettings::GetInputSettings()->AddActionMapping(Rfreshkey, false);

			
		}
		else {
			
		}
	}
	

	TArray<FInputActionKeyMapping> OutMap;
	UInputSettings::GetInputSettings()->GetActionMappingByName(ActionName, OutMap);
	UInputSettings::GetInputSettings()->RemoveActionMapping(OutMap[0], false);
	FInputActionKeyMapping Newkey(ActionName, InputKey.Key, InputKey.bShift, InputKey.bCtrl, InputKey.bAlt, InputKey.bCmd);
	UInputSettings::GetInputSettings()->AddActionMapping(Newkey, true);
	

}


void UKeySetWidget::UpdateKeyName(UPARAM(ref)TArray<UInputKeySelector*>& InputKey)
{

	TArray<FInputActionKeyMapping> CurrentAction = UInputSettings::GetInputSettings()->GetActionMappings();

		CurrentAction.StableSort([](const FInputActionKeyMapping& A, const FInputActionKeyMapping& B) {
			return A.ActionName.GetStringLength() < B.ActionName.GetStringLength();
			});

		InputKey.StableSort([](const UInputKeySelector& A, const UInputKeySelector& B) {
			return A.GetName().Len() < B.GetName().Len();
			});


	IsEmptyKey = false;
	for (int i = 0; i < InputKey.Num(); i++)
	{
		
		FInputChord Update(CurrentAction[i].Key, CurrentAction[i].bShift, CurrentAction[i].bCtrl, CurrentAction[i].bAlt, CurrentAction[i].bCmd);

		if (Update.Key == NONE)
		{
			IsEmptyKey = true;
		}

		InputKey[i]->SetSelectedKey(Update);
	
	}

	
}





