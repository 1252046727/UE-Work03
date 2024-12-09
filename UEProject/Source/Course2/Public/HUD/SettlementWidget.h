// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettlementWidget.generated.h"

class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class COURSE2_API USettlementWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> RestartButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ExitButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;

	// 更新显示分数
	void UpdateScoreText(int32 NewScore);
protected:
	UFUNCTION()
	void OnRestartClicked();
	UFUNCTION()
	void OnExitClicked();
};
