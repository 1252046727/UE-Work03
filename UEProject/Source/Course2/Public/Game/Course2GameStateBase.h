// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Course2GameStateBase.generated.h"

class ABlockActor;
class ACourse2PlayerController;
/**
 * 
 */
UCLASS()
class COURSE2_API ACourse2GameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	//积分
	UPROPERTY(EditAnywhere)
	int32 X;
	//缩放倍数
	UPROPERTY(EditAnywhere)
	float Y;
	//重要目标数量
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "10"))
	int32 N;
	//得分
	UPROPERTY()
	int32 Score;
	//游戏时间(秒)
	UPROPERTY(EditAnywhere)
	float T;
	// 重要方块的材质
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials")
	TObjectPtr<UMaterialInterface> ImportantMaterial;

	UPROPERTY()
	TObjectPtr<ABlockActor> NewBlock;
	//Block
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABlockActor> BlockActorClass;
	//Hp
	UPROPERTY()
	int32 Hp;
	//子弹数
	UPROPERTY(EditAnywhere)
	int32 Bullets;
	//未击中目标伤害
	UPROPERTY(EditAnywhere)
	int32 Damage;

	TObjectPtr<ACourse2PlayerController> Course2PlayerController;

	void EndGame();
protected:
	virtual void BeginPlay() override;

private:
	// 计时器句柄
	FTimerHandle GameEndTimerHandle;
};
