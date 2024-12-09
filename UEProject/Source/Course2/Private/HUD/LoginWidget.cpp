// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/LoginWidget.h"
#include "Components/Button.h"
#include"Components/EditableTextBox.h"
#include <Kismet/GameplayStatics.h>

void ULoginWidget::LoginSetup()
{
	AddToViewport();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			//����ģʽ ֻ��עUI
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}

}

bool ULoginWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (LoginButton)
	{
		LoginButton->OnClicked.AddDynamic(this, &ThisClass::LoginButtonClicked);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &ThisClass::ExitButtonClicked);
	}
	return true;
}

void ULoginWidget::NativeDestruct()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(false);
		}
	}
	Super::NativeDestruct();
}

void ULoginWidget::LoginButtonClicked()
{
	FString IdText = Id->GetText().ToString();         // ��ȡ Id �ı��������
	FString PasswordText = Password->GetText().ToString(); // ��ȡ Password �ı��������

	// �ж�
	if (IdText.Equals(TEXT("hjz")) && PasswordText.Equals(TEXT("123456")))
	{
		UGameplayStatics::OpenLevel(this, FName(TEXT("/Game/_Game/Maps/LoadingMap")));
	}
	else {
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				5.f,
				FColor::Red,
				FString(TEXT("Login failed, the Id and Password are incorrect!"))
			);
		}
	}
}

void ULoginWidget::ExitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
