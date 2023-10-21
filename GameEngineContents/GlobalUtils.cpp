#include "PreCompile.h"
#include "GlobalUtils.h"

GlobalUtils::GlobalUtils() 
{
}

GlobalUtils::~GlobalUtils() 
{
}

// 경로의 모든 파일을 로드합니다.
void GlobalUtils::LoadAllFileInPath(std::string_view _Path)
{
	GameEngineDirectory Dir;
	std::string ParentString = GetParentString(_Path);
	Dir.MoveParentToExistsChild(ParentString);
	Dir.MoveChild(_Path);

	std::vector<GameEngineFile> Files = Dir.GetAllFile();

	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile& File = Files[i];
		GameEngineTexture::Load(File.GetStringPath());
	}
}

// 모든 경로의 파일을 로드합니다.
void GlobalUtils::LoadAllDirFile(std::string_view _Path)
{
	GameEngineDirectory Dir;
	std::string ParentString = GetParentString(_Path);
	Dir.MoveParentToExistsChild(ParentString);
	Dir.MoveChild(_Path);


	//std::vector<GameEngineFile> Files = Dir.GetAllFile();
	
	std::vector<GameEngineDirectory> Directory = Dir.GetAllDirectory();
	
	for (size_t DirectoryCount = 0; DirectoryCount < Directory.size(); DirectoryCount++)
	{
		std::vector<GameEngineFile> Files = Directory[DirectoryCount].GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
	}
}


void GlobalUtils::ReleaseAllTextureInPath(std::string_view _Path)
{
	GameEngineDirectory Dir;
	std::string ParentString = GetParentString(_Path);
	Dir.MoveParentToExistsChild(ParentString);
	Dir.MoveChild(_Path);

	std::vector<GameEngineFile> Files = Dir.GetAllFile();

	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile& File = Files[i];
		std::string FileName = File.GetFileName();
		GameEngineTexture::Release(File.GetFileName());
	}
}

std::vector<GameEngineFile> GlobalUtils::GetAllFileInPath(std::string_view _Path)
{
	GameEngineDirectory Dir;
	std::string ParentString = GetParentString(_Path);
	Dir.MoveParentToExistsChild(ParentString);
	Dir.MoveChild(_Path);
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	return Files;
}

std::vector<GameEngineDirectory> GlobalUtils::GetAllDirInPath(std::string_view _Path)
{
	GameEngineDirectory Dir;
	std::string ParentString = GetParentString(_Path);
	Dir.MoveParentToExistsChild(ParentString);
	Dir.MoveChild(_Path);
	std::vector<GameEngineDirectory> Dirs = Dir.GetAllDirectory();
	return Dirs;
}


std::string GlobalUtils::GetParentString(std::string_view _ChildPath)
{
	int CountBeforeBackSlash = 0;

	std::string ChildPath = _ChildPath.data();

	while (true)
	{
		if ('\\' == ChildPath[CountBeforeBackSlash])
		{
			break;
		}

		++CountBeforeBackSlash;
	}

	
	ChildPath.resize(CountBeforeBackSlash);

	return ChildPath;
}

float GlobalUtils::CalculateDepth(const float _Value)
{
	return _Value;
}

float4 GlobalUtils::CalculateActorPivot(const float4& _Scale, ERENDERPIVOTPOS _Pivot)
{
	float4 HScale = _Scale;
	HScale = HScale.Half();
	float4 ReturnValue = float4::ZERO;

	switch (_Pivot)
	{
	case ERENDERPIVOTPOS::Center:
		ReturnValue = float4::ZERO;
		break;
	case ERENDERPIVOTPOS::LeftTop:
		HScale.Y *= -1.0f;
		ReturnValue = HScale;
		break;
	case ERENDERPIVOTPOS::RightBottom:
		HScale.X *= -1.0f;
		ReturnValue = HScale;
		break;
	default:
		break;
	}

	return ReturnValue;
}