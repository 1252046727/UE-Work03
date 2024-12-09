// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BattleWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UBattleWidget::BattleSetup(float Percent,int32 Number)
{
	AddToViewport();
    ChangeBloodBar(Percent);
    ChangeNumberOfBullets(Number);
    // ����ԭ������ɫ
    if (CrossHair)
    {
        OriginalColor = CrossHair->GetColorAndOpacity();
    }
}

void UBattleWidget::ChangeCrossHairColor()
{
    if (CrossHair)
    {
        // ����������ɫΪ��ɫ
        CrossHair->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f)));

        // ���ö�ʱ����0.2���ָ�ԭɫ
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
        // �����ı�
        NumberOfBullets->SetText(FText::FromString(BulletString));
    }
}

void UBattleWidget::RestoreCrossHairColor()
{
    if (CrossHair)
    {
        // �ָ�ԭ������ɫ
        CrossHair->SetColorAndOpacity(OriginalColor);
    }
}
