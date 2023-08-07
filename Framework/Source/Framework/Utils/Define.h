#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCustom, Log, All);

#define CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define LOG_CALLINFO(Verbosity) UE_LOG(LogCustom, Verbosity, TEXT("%s"), *CALLINFO)
#define LOG(Format, ...) UE_LOG(LogCustom, Display, TEXT("%s %s"), *CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define LOG_WARNING(Format, ...) UE_LOG(LogCustom, Warning, TEXT("%s %s"), *CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define LOG_ERROR(Format, ...) UE_LOG(LogCustom, Error, TEXT("%s %s"), *CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define	LOG_SCREEN(Format, ...) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(Format, ##__VA_ARGS__))
#define	LOG_SCREEN_COLOR(Color ,Format, ...) GEngine->AddOnScreenDebugMessage(-1, 5.f, Color, FString::Printf(Format, ##__VA_ARGS__))
