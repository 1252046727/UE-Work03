// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SettlementWidget.h"
#include "Components/Button.h"
#include <Course2/Course2PlayerController.h>
#include <Kismet/GameplayStatics.h>
#include "Components/TextBlock.h"

void USettlementWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (RestartButton != nullptr)
	{
		RestartButton->OnClicked.AddDynamic(this, &USettlementWidget::OnRestartClicked);
	}
	if (ExitButton != nullptr)
	{
		ExitButton->OnClicked.AddDynamic(this, &USettlementWidget::OnExitClicked);
	}

	UpdateScoreText(0);  // 初始化显示分数
}

void USettlementWidget::UpdateScoreText(int32 NewScore)
{
	if (ScoreText != nullptr)
	{
		// 将分数转换为文本并设置到 TextBlock
		FText ScoreTextValue = FText::AsNumber(NewScore);
		ScoreText->SetText(ScoreTextValue);
	}
}

void USettlementWidget::OnRestartClicked()
{
	ACourse2PlayerController* Course2PlayerController = Cast<ACourse2PlayerController>(GetOwningPlayer());
	if (Course2PlayerController != nullptr)
	{
		Course2PlayerController->HideSettlementWidget();
	}
	UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
}

void USettlementWidget::OnExitClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
