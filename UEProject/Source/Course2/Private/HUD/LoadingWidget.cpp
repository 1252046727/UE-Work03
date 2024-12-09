// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/LoadingWidget.h"
#include "Components/ProgressBar.h"
#include <Kismet/GameplayStatics.h>

void ULoadingWidget::LoadingSetup()
{
	AddToViewport();
	CurrentPercent = 0.f;
	// ���ö�ʱ��ÿ��һ��ʱ����� AddPercent ����
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ULoadingWidget::AddPercent, 1.0f, true);
}

void ULoadingWidget::AddPercent()
{
	// ����һ�����������Χ�� 0.1 �� 0.2 ֮��
	float RandomIncrement = FMath::RandRange(0.05f, 0.2f);
	CurrentPercent += RandomIncrement;
	if (CurrentPercent > 1.0f)
	{
		CurrentPercent = 1.0f;
	}
	// ���½�����
	if (LoadingBar)
	{
		LoadingBar->SetPercent(CurrentPercent);

	}
	// �����ȴﵽ 100% ʱֹͣ��ʱ��
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
