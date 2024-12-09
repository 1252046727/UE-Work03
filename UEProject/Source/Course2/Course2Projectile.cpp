// Copyright Epic Games, Inc. All Rights Reserved.

#include "Course2Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Course2/Public/Game/Course2GameStateBase.h"
#include "Course2/Public/Block/BlockActor.h"
#include "Course2/Course2PlayerController.h"

ACourse2Projectile::ACourse2Projectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ACourse2Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
	bDamage = false;
}

void ACourse2Projectile::BeginPlay()
{
	Super::BeginPlay(); 
	// 获取当前的 GameState
	AGameStateBase* GameStateBase = GetWorld()->GetGameState();

	if (GameStateBase !=nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("ok!"));
		// 将 GameState 转换为自定义的 AMyGameState 类型
		Course2GameStateBase = Cast<ACourse2GameStateBase>(GameStateBase);

		if (Course2GameStateBase !=nullptr)
		{
			// 访问 amygamestate 中的 X 和 Y 参数
			X = Course2GameStateBase->X;
			Y = Course2GameStateBase->Y;

			Course2GameStateBase->Bullets -= 1;
			Course2GameStateBase->Course2PlayerController->ChangeNumberOfBullets(Course2GameStateBase->Bullets);
		}
	}
}

void ACourse2Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		// 检查击中的物体是否是 ABlockActor 类型
		BlockActor = Cast<ABlockActor>(OtherActor);
		if (BlockActor!=nullptr)
		{
			if (Course2GameStateBase != nullptr)
			{
				Course2GameStateBase->Course2PlayerController->ChangeCrossHairColor();
				if (BlockActor->bImportance)
				{
					Course2GameStateBase->Score += 2 * X;
				}
				else
				{
					Course2GameStateBase->Score += X;
				}
				UE_LOG(LogTemp, Warning, TEXT("Score : %d"), Course2GameStateBase->Score);
			}
			if (BlockActor->bFlag)
			{
				//已经被击中过 直接销毁
				BlockActor->Destroy();
			}

			// 获取当前的缩放比例
			FVector CurrentScale = BlockActor->GetActorScale3D();
			// 设定新的缩放比例，Y轴乘以倍数
			FVector NewScale = FVector(CurrentScale.X * Y, CurrentScale.Y * Y, CurrentScale.Z * Y);
			// 设置新的缩放比例
			BlockActor->SetActorScale3D(NewScale);

			//已经被击中
			BlockActor->bFlag = true;
		}
		Destroy();
	}
	else
	{
		if (Course2GameStateBase != nullptr && bDamage == false)
		{
			bDamage = true;
			Course2GameStateBase->Hp -= Course2GameStateBase->Damage;
			float Percent = Course2GameStateBase->Hp / 100.0;
			Course2GameStateBase->Course2PlayerController->ChangeBloodBar(Percent);
			if (Course2GameStateBase->Hp <= 0)
			{
				Course2GameStateBase->EndGame();
			}
		}
	}
}