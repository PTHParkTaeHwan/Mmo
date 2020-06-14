// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Net/UnrealNetwork.h"

DECLARE_LOG_CATEGORY_EXTERN(TestMmo, Log, All);
#define TLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__)+TEXT(")"))
#define TLOG_S(Verbosty) UE_LOG(TestMmo, Verbosity, TEXT("%s"), *TLOG_CALLINFO)
#define TLOG(Verbosity, Format, ...) UE_LOG(TestMmo, Verbosity, TEXT("%s%s"), *TLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define ABCHECK(Expr, ...) { if(!(Expr)) { TLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__; }}
