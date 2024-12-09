// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleWidget.generated.h"

class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class COURSE2_API UBattleWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void BattleSetup(float Percent, int32 Number);

	void ChangeCrossHairColor();

	void ChangeBloodBar(float Percent);

	void ChangeNumberOfBullets(int32 Number);

	void RestoreCrossHairColor();
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CrossHair;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> NumberOfBullets;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> BloodBar;

	// 保存原来的颜色
	FSlateColor OriginalColor;

	// 用于定时恢复颜色
	FTimerHandle TimerHandle;
};
