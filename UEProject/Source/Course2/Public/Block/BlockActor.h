// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
UCLASS()
class COURSE2_API ABlockActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlockActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//是否已经被击中过
	UPROPERTY()
	bool bFlag;

	//是否是重要目标
	UPROPERTY()
	bool bImportance;

	//设置材质
	FORCEINLINE void SetBlockMaterial(UMaterialInterface* NewMaterial){ StaticMeshComponent->SetMaterial(0, NewMaterial);}
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Block", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Block", meta = (AllowPrivateAccess="true"))
	TObjectPtr<UBoxComponent> BoxComponent;

};
