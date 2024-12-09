// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Course2PlayerController.generated.h"

class UInputMappingContext;
class USettlementWidget;
class UBattleWidget;
/**
 *
 */
UCLASS()
class COURSE2_API ACourse2PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<USettlementWidget> SettlementWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBattleWidget> BattleWidgetClass;

	void ShowSettlementWidget(int32 FinalScore);

	void ShowBattleWidget(float Percent, int32 Number);

	void HideSettlementWidget();

	void ChangeCrossHairColor();

	void ChangeBloodBar(float Percent);

	void ChangeNumberOfBullets(int32 Number);

protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	// End Actor interface
private:
	UPROPERTY()
	TObjectPtr<USettlementWidget> SettlementWidget;

	UPROPERTY()
	TObjectPtr<UBattleWidget> BattleWidget;
};
