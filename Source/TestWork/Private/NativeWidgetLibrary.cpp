// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeWidgetLibrary.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"



bool IsWidgetPositionValid(FVector2D pos)
{
	return pos.X > 0 && pos.Y > 0;
}

UWidget* UNativeWidgetLibrary::FindWidgetAbove(
	TArray<UWidget*> Widgets,
	FVector2D MousePosition,
	UWidget* RootWidget,
	float SameDirectionMinDelta,
	float DirectionMultipler,
	UObject* WorldContextObject)
{
	UWidget* FoundWidget = nullptr;
	float MinDistance = 100000;
	for (UWidget* curr : Widgets)
	{
		

		FVector2D WidgetPosition = CountJumpPosition(WorldContextObject, curr);
		if (!IsWidgetPositionValid(WidgetPosition)) continue;
		
		FVector2D WidgetSize = GetWidgetSize(curr, WorldContextObject);
		if (!IsAbove(MousePosition, WidgetPosition, WidgetSize)) continue;

		FVector2D diff = WidgetPosition - MousePosition;
		if (FGenericPlatformMath::Abs(diff.Y) < SameDirectionMinDelta) continue;

		float currDist = FVector2D(diff.X, diff.Y * DirectionMultipler).Size();
		if (currDist < MinDistance)
		{
			FoundWidget = curr;
			MinDistance = currDist;
		}

	}
	return FoundWidget;
}
UWidget* UNativeWidgetLibrary::FindWidgetBelow(
	TArray<UWidget*> Widgets,
	FVector2D MousePosition,
	UWidget* RootWidget,
	float SameDirectionMinDelta,
	float DirectionMultipler,
	UObject* WorldContextObject)
{
	UWidget* FoundWidget = nullptr;
	float MinDistance = 100000;
	for (UWidget* curr : Widgets)
	{
		

		FVector2D WidgetPosition = CountJumpPosition(WorldContextObject, curr);
		if (!IsWidgetPositionValid(WidgetPosition)) continue;
		
		FVector2D WidgetSize = GetWidgetSize(curr, WorldContextObject);
		if (!IsBelow(MousePosition, WidgetPosition, WidgetSize)) continue;

		FVector2D diff = WidgetPosition - MousePosition;
		if (FGenericPlatformMath::Abs(diff.Y) < SameDirectionMinDelta) continue;

		float currDist = FVector2D(diff.X, diff.Y * DirectionMultipler).Size();
		if (currDist < MinDistance)
		{
			FoundWidget = curr;
			MinDistance = currDist;
		}

	}
	return FoundWidget;
}
UWidget* UNativeWidgetLibrary::FindWidgetOnLeft(
	TArray<UWidget*> Widgets,
	FVector2D MousePosition,
	UWidget* RootWidget,
	float SameDirectionMinDelta,
	float DirectionMultipler,
	UObject* WorldContextObject)
{
	UWidget* FoundWidget = nullptr;
	float MinDistance = 100000;
	for (UWidget* curr : Widgets)
	{
		

		FVector2D WidgetPosition = CountJumpPosition(WorldContextObject, curr);
		if (!IsWidgetPositionValid(WidgetPosition)) continue;
		
		FVector2D WidgetSize = GetWidgetSize(curr, WorldContextObject);
		if (!IsOnLeft(MousePosition, WidgetPosition, WidgetSize)) continue;

		FVector2D diff = WidgetPosition - MousePosition;
		if (FGenericPlatformMath::Abs(diff.X) < SameDirectionMinDelta) continue;

		float currDist = FVector2D(diff.X * DirectionMultipler, diff.Y).Size();
		if (currDist < MinDistance)
		{
			FoundWidget = curr;
			MinDistance = currDist;
		}

	}
	return FoundWidget;
}
UWidget* UNativeWidgetLibrary::FindWidgetOnRight(
	TArray<UWidget*> Widgets,
	FVector2D MousePosition,
	UWidget* RootWidget,
	float SameDirectionMinDelta,
	float DirectionMultipler,
	UObject* WorldContextObject)
{
	UWidget* FoundWidget = nullptr;
	float MinDistance = 100000;
	for (UWidget* curr : Widgets)
	{
		

		FVector2D WidgetPosition = CountJumpPosition(WorldContextObject, curr);
		if (!IsWidgetPositionValid(WidgetPosition)) continue;
		
		FVector2D WidgetSize = GetWidgetSize(curr, WorldContextObject);
		if (!IsOnRight(MousePosition, WidgetPosition, WidgetSize)) continue;

		FVector2D diff = WidgetPosition - MousePosition;
		if (FGenericPlatformMath::Abs(diff.X) < SameDirectionMinDelta) continue;

		float currDist = FVector2D(diff.X * DirectionMultipler, diff.Y).Size();
		if (currDist < MinDistance)
		{
			FoundWidget = curr;
			MinDistance = currDist;
		}

	}
	return FoundWidget;
}

FVector2D UNativeWidgetLibrary::CountJumpPosition(UObject* WorldContextObject, UWidget* widget)
{
	if (!IsValid(widget))
		return FVector2D(0, 0);
	FVector2D PixelPosition;
	FVector2D ViewportPosition;
	FGeometry Geometry = widget->GetCachedGeometry();
	USlateBlueprintLibrary::LocalToViewport(WorldContextObject, Geometry, FVector2D(0, 0), PixelPosition, ViewportPosition);
	FVector2D localSize = USlateBlueprintLibrary::GetLocalSize(Geometry);
	float scale = UWidgetLayoutLibrary::GetViewportScale(WorldContextObject);

	return PixelPosition + (localSize * 0.5 * scale);
}

FVector2D UNativeWidgetLibrary::GetWidgetSize(UWidget* Widget, UObject* WorldContextObject)
{
	if (!IsValid(Widget))
		return FVector2D(0, 0);
	FGeometry Geometry = Widget->GetCachedGeometry();
	FVector2D localSize = USlateBlueprintLibrary::GetLocalSize(Geometry);
	return USlateBlueprintLibrary::LocalToAbsolute(Geometry, localSize) - USlateBlueprintLibrary::LocalToAbsolute(Geometry, FVector2D(0, 0));

}

bool UNativeWidgetLibrary::IsBelow(FVector2D CursorPosition, FVector2D WidgetPosition, UWidget* Widget, UObject* WorldContextObject)
{
	return IsBelow(CursorPosition, WidgetPosition, GetWidgetSize(Widget, WorldContextObject));
}
bool UNativeWidgetLibrary::IsBelow(FVector2D CursorPosition, FVector2D WidgetPosition, FVector2D WidgetSize)
{
	return WidgetPosition.Y - WidgetSize.Y / 2 > CursorPosition.Y;
}
bool UNativeWidgetLibrary::IsAbove(FVector2D CursorPosition, FVector2D WidgetPosition, UWidget* Widget, UObject* WorldContextObject)
{
	return IsAbove(CursorPosition, WidgetPosition, GetWidgetSize(Widget, WorldContextObject));
}
bool UNativeWidgetLibrary::IsAbove(FVector2D CursorPosition, FVector2D WidgetPosition, FVector2D WidgetSize)
{
	return WidgetPosition.Y + WidgetSize.Y / 2 < CursorPosition.Y;
}
bool UNativeWidgetLibrary::IsOnRight(FVector2D CursorPosition, FVector2D WidgetPosition, UWidget* Widget, UObject* WorldContextObject)
{
	return IsOnRight(CursorPosition, WidgetPosition, GetWidgetSize(Widget, WorldContextObject));
}
bool UNativeWidgetLibrary::IsOnRight(FVector2D CursorPosition, FVector2D WidgetPosition, FVector2D WidgetSize)
{
	return CursorPosition.X < WidgetPosition.X - WidgetSize.X / 2;
}
bool UNativeWidgetLibrary::IsOnLeft(FVector2D CursorPosition, FVector2D WidgetPosition, UWidget* Widget, UObject* WorldContextObject)
{
	return IsOnLeft(CursorPosition, WidgetPosition, GetWidgetSize(Widget, WorldContextObject));
}
bool UNativeWidgetLibrary::IsOnLeft(FVector2D CursorPosition, FVector2D WidgetPosition, FVector2D WidgetSize)
{
	return WidgetPosition.X + WidgetSize.X / 2 < CursorPosition.X;
}