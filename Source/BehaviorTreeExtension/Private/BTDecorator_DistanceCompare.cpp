// Copyright (c) Lim Young

#include "BTDecorator_DistanceCompare.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_DistanceCompare::UBTDecorator_DistanceCompare()
{
	NodeName = "Distance Compare";

	TargetValueKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_DistanceCompare, TargetValueKey));
	TargetValueKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_DistanceCompare, TargetValueKey),
	                               AActor::StaticClass());

	DistanceKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_DistanceCompare, DistanceKey));
}

void UBTDecorator_DistanceCompare::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (ensure(BBAsset))
	{
		TargetValueKey.ResolveSelectedKey(*BBAsset);
		DistanceKey.ResolveSelectedKey(*BBAsset);
	}
}

FString UBTDecorator_DistanceCompare::GetStaticDescription() const
{
	FString KeyDesc = TargetValueKey.IsSet() ? TargetValueKey.SelectedKeyName.ToString() : TEXT("Invalid");
	FString KeyDesc2 = DistanceKey.IsSet() ? DistanceKey.SelectedKeyName.ToString() : TEXT("Invalid");
	FString OperationDesc = CompareOperationEnum == ECompareOperation::Equal
		                        ? TEXT("==")
		                        : CompareOperationEnum == ECompareOperation::NotEqual
		                        ? TEXT("!=")
		                        : CompareOperationEnum == ECompareOperation::Less
		                        ? TEXT("<")
		                        : CompareOperationEnum == ECompareOperation::LessEqual
		                        ? TEXT("<=")
		                        : CompareOperationEnum == ECompareOperation::Greater
		                        ? TEXT(">")
		                        : CompareOperationEnum == ECompareOperation::GreaterEqual
		                        ? TEXT(">=")
		                        : TEXT("Invalid");
	FString Result = FString::Printf(TEXT("%s %s %s"), *KeyDesc, *OperationDesc, *KeyDesc2);
	return FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(), *Result);
}

bool UBTDecorator_DistanceCompare::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                              uint8* NodeMemory) const
{
	bool bResult = false;

	AActor* Pawn = Cast<AAIController>(OwnerComp.GetOwner())->GetPawn();
	if (!Pawn)
	{
		return bResult;
	}

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComponent)
	{
		return bResult;
	}

	FVector TargetLocation = FVector::ZeroVector;
	const AActor* TargetActor = nullptr;

	TargetLocation = BlackboardComponent->GetValueAsVector(TargetValueKey.SelectedKeyName);

	if (TargetLocation == FAISystem::InvalidLocation)
	{
		TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(TargetValueKey.SelectedKeyName));
		if (TargetActor)
		{
			TargetLocation = TargetActor->GetActorLocation();
		}
		else
		{
			return bResult;
		}
	}

	float DistanceValue = 0.0f;

	if (bUseBlackDistanceValue)
	{
		DistanceValue = BlackboardComponent->GetValueAsFloat(DistanceKey.SelectedKeyName);
	}
	else
	{
		DistanceValue = Distance;
	}

	switch (CompareOperationEnum)
	{
	case ECompareOperation::Equal:
		bResult = FVector::Distance(TargetLocation, Pawn->GetActorLocation()) ==
			DistanceValue;
		break;
	case ECompareOperation::NotEqual:
		bResult = FVector::Distance(TargetLocation, Pawn->GetActorLocation()) !=
			DistanceValue;
		break;
	case ECompareOperation::Less:
		bResult = FVector::Distance(TargetLocation, Pawn->GetActorLocation()) <
			DistanceValue;
		break;
	case ECompareOperation::LessEqual:
		bResult = FVector::Distance(TargetLocation, Pawn->GetActorLocation()) <=
			DistanceValue;
		break;
	case ECompareOperation::Greater:
		bResult = FVector::Distance(TargetLocation, Pawn->GetActorLocation()) >
			DistanceValue;
		break;
	case ECompareOperation::GreaterEqual:
		bResult = FVector::Distance(TargetLocation, Pawn->GetActorLocation()) >=
			DistanceValue;
		break;
	default:
		break;
	}

	UE_LOG(LogTemp, Warning, TEXT( "Distance = %f, CurrentDistance = %f" ), DistanceValue,
	       FVector::Distance(TargetLocation, OwnerComp.GetOwner()->GetActorLocation()));
	UE_LOG(LogTemp, Warning, TEXT( "UBTDecorator_DistanceCompare::CalculateRawConditionValue: bResult = %s" ),
	       bResult ? TEXT( "true" ) : TEXT( "false" ));
	return bResult;
}
