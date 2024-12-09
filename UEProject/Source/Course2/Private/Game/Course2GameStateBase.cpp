// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Course2GameStateBase.h"
#include "Course2/Public/Block/BlockActor.h"
#include <Kismet/GameplayStatics.h>
#include "TimerManager.h"
#include "Course2/Course2PlayerController.h"

void ACourse2GameStateBase::BeginPlay()
{
	Super::BeginPlay();

    //��ʼ���÷�
    Score = 0;
    //��ʼ������ֵ
    Hp = 100;
    // �������ɷ�������Χ�������ͼ�ߴ緶Χ
    float MinX = 160.f; // ��СX����
    float MaxX = 2880.f;  // ���X����
    float MinY = 135.f; // ��СY����
    float MaxY = 3345.f;  // ���Y����
    float MinZ = 300.f;   // ��СZ���꣨ȷ�����ڵ������ɣ�
    float MaxZ = 310.f;   // ���Z���꣨���ɸ߶ȣ�

    // �����λ�����ɷ���
    if (BlockActorClass)  // ȷ����ķ���������Ч��
    {
        TArray<ABlockActor*> GeneratedBlocks;  // ���ڴ洢���ɵķ���ʵ��

        for (int i = 1;i <= 10;i++) 
        {
            // �������λ��
            FVector RandomLocation = FVector(
                FMath::RandRange(MinX, MaxX),  // X����
                FMath::RandRange(MinY, MaxY),  // Y����
                FMath::RandRange(MinZ, MaxZ)   // Z����
            );

            // ���ɷ���
            NewBlock = GetWorld()->SpawnActor<ABlockActor>(
                BlockActorClass,       
                RandomLocation,        
                FRotator::ZeroRotator  
            );

            if (NewBlock!=nullptr)
            {
                GeneratedBlocks.Add(NewBlock);  // �����ɵķ�����ӵ�����
            }
        }

        TArray<int32> SelectedIndices;
        while (SelectedIndices.Num() < N)
        {
            int RandomIndex = FMath::RandRange(0, GeneratedBlocks.Num() - 1);

            // ȷ�����ظ�ѡ��
            if (!SelectedIndices.Contains(RandomIndex))
            {
                //UE_LOG(LogTemp, Warning, TEXT("Importance :%d %d"), SelectedIndices.Num(), N);
                SelectedIndices.Add(RandomIndex);
                GeneratedBlocks[RandomIndex]->bImportance = true;
                //���Ĳ���
                GeneratedBlocks[RandomIndex]->SetBlockMaterial(ImportantMaterial);
            }
        }

        // ���ü�ʱ������ 10 ������ EndGame ����
        GetWorldTimerManager().SetTimer(GameEndTimerHandle, this, &ACourse2GameStateBase::EndGame, T, false);
    }

    // ��ȡ��һ����ҿ�����
    Course2PlayerController = Cast<ACourse2PlayerController>(GetWorld()->GetFirstPlayerController());
    
    //����ս�����
    if (Course2PlayerController != nullptr)
    {
        Course2PlayerController->ShowBattleWidget(1.0f, Bullets);
    }
}

// ��Ϸ��������
void ACourse2GameStateBase::EndGame()
{
    // �����ʱ������ֹ 10 ����ٴδ���
    GetWorld()->GetTimerManager().ClearTimer(GameEndTimerHandle);

    // ��ӡ�÷�
    //UE_LOG(LogTemp, Warning, TEXT("Game Over! Final Score: %d"), Score);
    if (Course2PlayerController != nullptr)
    {
        Course2PlayerController->ShowSettlementWidget(Score);
    } 
}