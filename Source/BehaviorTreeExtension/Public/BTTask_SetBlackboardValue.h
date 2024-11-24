// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetBlackboardValue.generated.h"

UENUM(BlueprintType)
enum class EValueType : uint8
{
	Bool,
	Int,
	Float,
	String,
	Vector,
	Rotator,
	Object,
	Class,
	Name,
	Enum
};

UCLASS()
class BEHAVIORTREEEXTENSION_API UBTTask_SetBlackboardValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	//可编辑实例
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	EValueType ValueType;

	UPROPERTY(EditAnywhere, Category = "Blackboard",
		meta = (EditCondition = "ValueType == ValueType::Bool", EditConditionHides = "false"))
	bool BoolValue;

	UPROPERTY(EditAnywhere, Category = "Blackboard",
		meta = (EditCondition = "ValueType == ValueType::Int", EditConditionHides = "false"))
	int32 IntValue;

	UPROPERTY(EditAnywhere, Category = "Blackboard",
		meta = (EditCondition = "ValueType == ValueType::Float", EditConditionHides = "false"))
	float FloatValue;

	UPROPERTY(EditAnywhere, Category = "Blackboard",
		meta = (EditCondition = "ValueType == ValueType::String", EditConditionHides = "false"))
	FString StringValue;

	UPROPERTY(EditAnywhere, Category = "Blackboard",
		meta = (EditCondition = "ValueType == ValueType::Vector", EditConditionHides = "false"))
	FVector VectorValue;

	UPROPERTY(EditAnywhere, Category = "Blackboard",
		meta = (EditCondition = "ValueType == ValueType::Rotator", EditConditionHides = "false"))
	FRotator RotatorValue;

	UPROPERTY(EditAnywhere, Category = "Blackboard",
		meta = (EditCondition = "ValueType == ValueType::Object", EditConditionHides = "false"))
	UObject* ObjectValue;

	UPROPERTY(EditAnywhere, Category = "Blackboard",
		meta = (EditCondition = "ValueType == ValueType::Class", EditConditionHides = "false"))
	TSubclassOf<UObject> ClassValue;

	UPROPERTY(EditAnywhere, Category = "Blackboard",
		meta = (EditCondition = "ValueType == ValueType::Name", EditConditionHides = "false"))
	FName NameValue;

	UPROPERTY(EditAnywhere, Category = "Blackboard",
		meta = (EditCondition = "ValueType == ValueType::Enum", EditConditionHides = "false"))
	UEnum* EnumValue;

public:
	UBTTask_SetBlackboardValue();

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
