// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ViewWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTWORK_API UViewWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
		//UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "Input")
		FReply NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
};
