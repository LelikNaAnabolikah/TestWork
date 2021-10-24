// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewWidget.h"

FReply UViewWidget::NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{

	UE_LOG(LogTemp, Warning, TEXT("Hello :)"));
	FReply Reply = FReply::Handled();

	return Reply;
}