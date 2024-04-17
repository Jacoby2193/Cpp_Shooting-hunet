// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class CPP_SHOOTING_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Button_Quit;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Button_Restart;

	UFUNCTION()
	void OnClickQuit();
	
	UFUNCTION()
	void OnClickRestart();
};
