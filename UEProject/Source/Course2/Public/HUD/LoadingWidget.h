// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadingWidget.generated.h"
class UProgressBar;
/**
 * 
 */
UCLASS()
class COURSE2_API ULoadingWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void LoadingSetup();

	void AddPercent();
protected:
	// ¶¨Ê±Æ÷¾ä±ú
	FTimerHandle TimerHandle;

	virtual bool Initialize() override;
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> LoadingBar;

	float CurrentPercent;
};
