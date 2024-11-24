// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_DistanceCompare.generated.h"

UENUM(BlueprintType)
enum class ECompareOperation : uint8
{
	Equal UMETA(DisplayName = "=="),
	NotEqual UMETA(DisplayName = "!="),
	Less UMETA(DisplayName = "<"),
	LessEqual UMETA(DisplayName = "<="),
	Greater UMETA(DisplayName = ">"),
	GreaterEqual UMETA(DisplayName = ">="),
};

/**
 * 
 */
UCLASS()
class BEHAVIORTREEEXTENSION_API UBTDecorator_DistanceCompare : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDecorator_DistanceCompare();

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	
	virtual FString GetStaticDescription() const override;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, Category = "DistanceCompare")
	FBlackboardKeySelector TargetValueKey;

	// UE比较运算符枚举
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DistanceCompare")
	ECompareOperation CompareOperationEnum = ECompareOperation::LessEqual;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DistanceCompare")
	bool bUseBlackDistanceValue = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DistanceCompare",
		meta = (EditCondition = "!bUseBlackDistanceValue", EditConditionHides = "false"))
	float Distance = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DistanceCompare",
		meta = (EditCondition = "bUseBlackDistanceValue", EditConditionHides = "false"))
	FBlackboardKeySelector DistanceKey;
};
