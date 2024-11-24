// Copyright (c) Lim Young

#include "BTTask_SetBlackboardValue.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetBlackboardValue::UBTTask_SetBlackboardValue(): ValueType(), BoolValue(false), IntValue(0), FloatValue(0),
                                                          ObjectValue(nullptr),
                                                          EnumValue(nullptr)
{
	NodeName = "Set Blackboard Value";
}

void UBTTask_SetBlackboardValue::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
}

EBTNodeResult::Type UBTTask_SetBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	switch (ValueType)
	{
	case EValueType::Bool:
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), BoolValue);
		return EBTNodeResult::Succeeded;
		break;
	case EValueType::Int:
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(GetSelectedBlackboardKey(), IntValue);
		return EBTNodeResult::Succeeded;
		break;
	case EValueType::Float:
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), FloatValue);
		return EBTNodeResult::Succeeded;
		break;
	case EValueType::String:
		OwnerComp.GetBlackboardComponent()->SetValueAsString(GetSelectedBlackboardKey(), StringValue);
		return EBTNodeResult::Succeeded;
		break;
	case EValueType::Vector:
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), VectorValue);
		return EBTNodeResult::Succeeded;
		break;
	case EValueType::Rotator:
		OwnerComp.GetBlackboardComponent()->SetValueAsRotator(GetSelectedBlackboardKey(), RotatorValue);
		return EBTNodeResult::Succeeded;
		break;
	case EValueType::Object:
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), ObjectValue);
		return EBTNodeResult::Succeeded;
		break;
	case EValueType::Class:
		OwnerComp.GetBlackboardComponent()->SetValueAsClass(GetSelectedBlackboardKey(), ClassValue);
		return EBTNodeResult::Succeeded;
		break;
	case EValueType::Name:
		OwnerComp.GetBlackboardComponent()->SetValueAsName(GetSelectedBlackboardKey(), NameValue);
		return EBTNodeResult::Succeeded;
		break;
	case EValueType::Enum:
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(),
		                                                   EnumValue->GetIndexByName(NameValue));
		return EBTNodeResult::Succeeded;
		break;
	default:
		return EBTNodeResult::Failed;
		break;
	}
}