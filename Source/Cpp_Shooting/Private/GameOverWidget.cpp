// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"
#include <Components/Button.h>
#include <Kismet/KismetSystemLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>

void UGameOverWidget::NativeConstruct()
{
	// 버튼 연결
	Button_Quit->OnClicked.AddDynamic(this, &UGameOverWidget::OnClickQuit);
	Button_Restart->OnClicked.AddDynamic(this, &UGameOverWidget::OnClickRestart);
}

void UGameOverWidget::OnClickQuit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void UGameOverWidget::OnClickRestart()
{
	FString levelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	UGameplayStatics::OpenLevel(GetWorld(), FName(*levelName));
}
