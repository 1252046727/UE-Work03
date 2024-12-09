// Fill out your copyright notice in the Description page of Project Settings.


#include "Block/BlockActor.h"
#include "Components/BoxComponent.h"
// Sets default values
ABlockActor::ABlockActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ����һ��������ײ�����
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	// ��������Ϊ�����
	RootComponent = BoxComponent;
	// ������ײ�����ײ��Ӧ��Ĭ������������ж������赲
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);  // ������ײ
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Block);  // �赲������ײ
	BoxComponent->SetSimulatePhysics(true); //ģ������

	// ������̬�����������������Ŀ��Ӳ��֣�
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	//�Ƿ��Ѿ������й�
	bFlag = false;
	//�Ƿ�����ҪĿ��
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

