// Fill out your copyright notice in the Description page of Project Settings.


#include "Block/BlockActor.h"
#include "Components/BoxComponent.h"
// Sets default values
ABlockActor::ABlockActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 创建一个盒子碰撞体组件
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	// 将其设置为根组件
	RootComponent = BoxComponent;
	// 设置碰撞体的碰撞响应，默认情况下与所有对象发生阻挡
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);  // 启用碰撞
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Block);  // 阻挡所有碰撞
	BoxComponent->SetSimulatePhysics(true); //模拟物理

	// 创建静态网格组件（用作方块的可视部分）
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	//是否已经被击中过
	bFlag = false;
	//是否是重要目标
	bImportance = false;
}

// Called when the game starts or when spawned
void ABlockActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlockActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

