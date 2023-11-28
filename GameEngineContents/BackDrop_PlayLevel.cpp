#include "PreCompile.h"
#include "BackDrop_PlayLevel.h"


#include "NormalProp.h"
#include "StaticEntity.h"

#include "LootedItem.h"



BackDrop_PlayLevel* BackDrop_PlayLevel::MainBackDrop = nullptr;
BackDrop_PlayLevel::BackDrop_PlayLevel() 
{
	MainBackDrop = this;
}

BackDrop_PlayLevel::~BackDrop_PlayLevel() 
{
}

void BackDrop_PlayLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
	BackDrop::LevelStart(_NextLevel);

	MainBackDrop = this;
}

void BackDrop_PlayLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	BackDrop::LevelEnd(_NextLevel);

	PixelVec.clear();
}


// 특정 위치에 픽셀데이터가 있는지 반환해줍니다.
bool BackDrop_PlayLevel::IsColorAtPosition(const float4& _Position, GameEngineColor _CheckColor)
{
	for (std::weak_ptr<NormalProp> Object : PixelVec)
	{
		if (true == Object.expired())
		{
			MsgBoxAssert("생성되지 않은 액터를 참조하려고 했습니다.");
			return false;
		}

		if (false == Object.lock()->GetPixelCheck())
		{
			continue;
		}

		if (_CheckColor == Object.lock()->GetColor(_Position))
		{
			return true;
		}
	}

	for (std::weak_ptr<StaticEntity> Entity : PixelStaticEntityVec)
	{
		if (true == Entity.expired())
		{
			MsgBoxAssert("생성되지 않은 액터를 참조하려고 했습니다.");
			return false;
		}

		if (false == Entity.lock()->GetPixelCheck())
		{
			continue;
		}

		if (_CheckColor == Entity.lock()->GetColor(_Position))
		{
			return true;
		}
	}

	return false;
}

// 깊이버퍼 계산

float BackDrop_PlayLevel::ReturnPlusDepth(const float _PositionY) const
{
	float4 BackGroundScale = m_BackScale;
	if (float4::ZERO == BackGroundScale)
	{
		BackGroundScale = GlobalValue::GetWindowScale();
	}

	float PlusDepth = _PositionY / BackGroundScale.Y * 100.0f;
	return PlusDepth;
}


// 아이템 생성 : 
// 아이템 이름
// 위치
// 개수
// 떨어질 거리
void BackDrop_PlayLevel::CreateItem(std::string_view _ItemName, const float4& _Position, const int _Stack /*= 1*/, const float _FallYPosition /*= 0.0f*/)
{
	std::shared_ptr<LootedItem> Item = GetLevel()->CreateActor<LootedItem>(EUPDATEORDER::Entity);

	Item->BackManager = this;

	float4 Position = _Position;
	Position.Z = DepthFunction::CalculateFixDepth(ERENDERDEPTH::RootedItem);
	Item->Transform.SetLocalPosition(Position);

	Item->SetStack(_Stack);

	if (0.0f != _FallYPosition)
	{
		Item->SetFallingTargetPosition(_FallYPosition);
	}

	Item->Init(_ItemName);
}

