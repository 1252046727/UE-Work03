// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BattleWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UBattleWidget::BattleSetup(float Percent,int32 Number)
{
	AddToViewport();
    ChangeBloodBar(Percent);
    ChangeNumberOfBullets(Number);
    // 保存原来的颜色
    if (CrossHair)
    {
        OriginalColor = CrossHair->GetColorAndOpacity();
    }
}

void UBattleWidget::ChangeCrossHairColor()
{
    if (CrossHair)
    {
        // 设置字体颜色为红色
        CrossHair->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f)));

        // 设置定时器，0.2秒后恢复原色
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBattleWidget::RestoreCrossHairColor, 0.2f, false);
    }
}

void UBattleWidget::ChangeBloodBar(float Percent)
{
    if (BloodBar)
    {
        BloodBar->SetPercent(Percent);
    }
}

void UBattleWidget::ChangeNumberOfBullets(int32 Number)
{
    if (NumberOfBullets)
    {
        FString BulletString = FString::Printf(TEXT("%d"), Number);
        // 设置文本
        NumberOfBullets->SetText(FText::FromString(BulletString));
    }
}

void UBattleWidget::RestoreCrossHairColor()
{
    if (CrossHair)
    {
        // 恢复原来的颜色
        CrossHair->SetColorAndOpacity(OriginalColor);
    }
}
