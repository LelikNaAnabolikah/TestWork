// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/Widget.h"
#include "NativeWidgetLibrary.generated.h"

class UScrollBox;

UENUM(BlueprintType)
enum class NavigationDpadDirection : uint8
{
	Left,
	Right,
	Up,
	Down,
	TabLeft,
	TabRight,
	Undefined,
	SaveTile,
	RemoveTile
};

UCLASS()
class TESTWORK_API UNativeWidgetLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

	UFUNCTION(BlueprintPure, Category = "Widget", meta = (WorldContext = "WorldContextObject"))
		static FVector2D CountJumpPosition(UObject* WorldContextObject, UWidget* widget);

	UFUNCTION(BlueprintPure, Category = "Widget", meta = (WorldContext = "WorldContextObject"))
		static FVector2D GetWidgetSize(UWidget* Widget, UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure, Category = "Widget", meta = (WorldContext = "WorldContextObject"))
		static bool IsBelow(FVector2D CursorPosition, FVector2D WidgetPosition, UWidget* Widget, UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Widget", meta = (WorldContext = "WorldContextObject"))
		static bool IsAbove(FVector2D CursorPosition, FVector2D WidgetPosition, UWidget* Widget, UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Widget", meta = (WorldContext = "WorldContextObject"))
		static bool IsOnRight(FVector2D CursorPosition, FVector2D WidgetPosition, UWidget* Widget, UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Widget", meta = (WorldContext = "WorldContextObject"))
		static bool IsOnLeft(FVector2D CursorPosition, FVector2D WidgetPosition, UWidget* Widget, UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Widget", meta = (WorldContext = "WorldContextObject"))
		static UWidget* FindWidgetAbove(
			TArray<UWidget*> Widgets,
			FVector2D MousePosition,
			UWidget* RootWidget,
			float SameDirectionMinDelta,
			float DirectionMultipler,
			UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, Category = "Widget", meta = (WorldContext = "WorldContextObject"))
		static UWidget* FindWidgetBelow(
			TArray<UWidget*> Widgets,
			FVector2D MousePosition,
			UWidget* RootWidget,
			float SameDirectionMinDelta,
			float DirectionMultipler,
			UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, Category = "Widget", meta = (WorldContext = "WorldContextObject"))
		static UWidget* FindWidgetOnLeft(
			TArray<UWidget*> Widgets,
			FVector2D MousePosition,
			UWidget* RootWidget,
			float SameDirectionMinDelta,
			float DirectionMultipler,
			UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, Category = "Widget", meta = (WorldContext = "WorldContextObject"))
		static UWidget* FindWidgetOnRight(
			TArray<UWidget*> Widgets,
			FVector2D MousePosition,
			UWidget* RootWidget,
			float SameDirectionMinDelta,
			float DirectionMultipler,
			UObject* WorldContextObject);

private:

	static bool IsBelow(FVector2D CursorPosition, FVector2D WidgetPosition, FVector2D WidgetSize);
	static bool IsAbove(FVector2D CursorPosition, FVector2D WidgetPosition, FVector2D WidgetSize);
	static bool IsOnRight(FVector2D CursorPosition, FVector2D WidgetPosition, FVector2D WidgetSize);
	static bool IsOnLeft(FVector2D CursorPosition, FVector2D WidgetPosition, FVector2D WidgetSize);
	

		
};
