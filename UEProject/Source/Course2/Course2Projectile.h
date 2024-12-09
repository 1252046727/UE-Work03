// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Course2Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class ACourse2GameStateBase;
class ABlockActor;

UCLASS(config=Game)
class ACourse2Projectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

protected:
	// ÖØÐ´ BeginPlay
	virtual void BeginPlay() override;

public:
	ACourse2Projectile();

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
	UPROPERTY()
	int32 X;

	UPROPERTY()
	float Y;

	UPROPERTY()
	bool bDamage;

	UPROPERTY()
	TObjectPtr<ACourse2GameStateBase> Course2GameStateBase;
	UPROPERTY()
	TObjectPtr<ABlockActor> BlockActor;

};

