// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.generated.h"

class UButton;
class UEditableTextBox;
/**
 * 
 */
UCLASS()
class COURSE2_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void LoginSetup();

protected:
	virtual bool Initialize() override;

	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> LoginButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ExitButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> Id;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> Password;

	UFUNCTION()
	void LoginButtonClicked();

	UFUNCTION()
	void ExitButtonClicked();
};
