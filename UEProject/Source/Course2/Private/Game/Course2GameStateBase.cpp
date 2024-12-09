// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Course2GameStateBase.h"
#include "Course2/Public/Block/BlockActor.h"
#include <Kismet/GameplayStatics.h>
#include "TimerManager.h"
#include "Course2/Course2PlayerController.h"

void ACourse2GameStateBase::BeginPlay()
{
	Super::BeginPlay();

    //初始化得分
    Score = 0;
    //初始化生命值
    Hp = 100;
    // 设置生成方块的最大范围，假设地图尺寸范围
    float MinX = 160.f; // 最小X坐标
    float MaxX = 2880.f;  // 最大X坐标
    float MinY = 135.f; // 最小Y坐标
    float MaxY = 3345.f;  // 最大Y坐标
    float MinZ = 300.f;   // 最小Z坐标（确保不在地下生成）
    float MaxZ = 310.f;   // 最大Z坐标（生成高度）

    // 在随机位置生成方块
    if (BlockActorClass)  // 确保你的方块类是有效的
    {
        TArray<ABlockActor*> GeneratedBlocks;  // 用于存储生成的方块实例

        for (int i = 1;i <= 10;i++) 
        {
            // 生成随机位置
            FVector RandomLocation = FVector(
                FMath::RandRange(MinX, MaxX),  // X坐标
                FMath::RandRange(MinY, MaxY),  // Y坐标
                FMath::RandRange(MinZ, MaxZ)   // Z坐标
            );

            // 生成方块
            NewBlock = GetWorld()->SpawnActor<ABlockActor>(
                BlockActorClass,       
                RandomLocation,        
                FRotator::ZeroRotator  
            );

            if (NewBlock!=nullptr)
            {
                GeneratedBlocks.Add(NewBlock);  // 将生成的方块添加到数组
            }
        }

        TArray<int32> SelectedIndices;
        while (SelectedIndices.Num() < N)
        {
            int RandomIndex = FMath::RandRange(0, GeneratedBlocks.Num() - 1);

            // 确保不重复选择
            if (!SelectedIndices.Contains(RandomIndex))
            {
                //UE_LOG(LogTemp, Warning, TEXT("Importance :%d %d"), SelectedIndices.Num(), N);
                SelectedIndices.Add(RandomIndex);
                GeneratedBlocks[RandomIndex]->bImportance = true;
                //更改材质
                GeneratedBlocks[RandomIndex]->SetBlockMaterial(ImportantMaterial);
            }
        }

        // 设置计时器，在 10 秒后调用 EndGame 函数
        GetWorldTimerManager().SetTimer(GameEndTimerHandle, this, &ACourse2GameStateBase::EndGame, T, false);
    }

    // 获取第一个玩家控制器
    Course2PlayerController = Cast<ACourse2PlayerController>(GetWorld()->GetFirstPlayerController());
    
    //生成战斗面板
    if (Course2PlayerController != nullptr)
    {
        Course2PlayerController->ShowBattleWidget(1.0f, Bullets);
    }
}

// 游戏结束函数
void ACourse2GameStateBase::EndGame()
{
    // 清除定时器，防止 10 秒后再次触发
    GetWorld()->GetTimerManager().ClearTimer(GameEndTimerHandle);

    // 打印得分
    //UE_LOG(LogTemp, Warning, TEXT("Game Over! Final Score: %d"), Score);
    if (Course2PlayerController != nullptr)
    {
        Course2PlayerController->ShowSettlementWidget(Score);
    } 
}