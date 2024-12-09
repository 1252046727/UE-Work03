// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/LoadingWidget.h"
#include "Components/ProgressBar.h"
#include <Kismet/GameplayStatics.h>

void ULoadingWidget::LoadingSetup()
{
	AddToViewport();
	CurrentPercent = 0.f;
	// 设置定时器每隔一段时间调用 AddPercent 函数
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ULoadingWidget::AddPercent, 1.0f, true);
}

void ULoadingWidget::AddPercent()
{
	// 生成一个随机数，范围在 0.1 到 0.2 之间
	float RandomIncrement = FMath::RandRange(0.05f, 0.2f);
	CurrentPercent += RandomIncrement;
	if (CurrentPercent > 1.0f)
	{
		CurrentPercent = 1.0f;
	}
	// 更新进度条
	if (LoadingBar)
	{
		LoadingBar->SetPercent(CurrentPercent);

	}
	// 当进度达到 100% 时停止定时器
	if (CurrentPercent >= 1.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		UGameplayStatics::OpenLevel(this, FName(TEXT("/Game/FirstPerson/Maps/FirstPersonMap")));
	}
}

bool ULoadingWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	return true;
}
