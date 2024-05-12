#pragma once

template <typename ResourceType>
class EngineResource
{
public:
	// constructor destructor
	EngineResource() {};
	virtual ~EngineResource() {};

	// delete Function
	EngineResource(const EngineResource& _Other) = delete;
	EngineResource(EngineResource&& _Other) noexcept = delete;
	EngineResource& operator=(const EngineResource& _Other) = delete;
	EngineResource& operator=(EngineResource&& _Other) noexcept = delete;

	static ResourceType* Find(std::string_view _Name)
	{
		if (false == Resources.contains(_Name.data()))
		{
			return nullptr;
		}

		return Resources[_Name.data()].get();
	}

protected:
	static ResourceType* CreateEngineResource(std::string_view _Name)
	{
		std::shared_ptr<ResourceType> NewObject = std::make_shared<ResourceType>();

		if (true == Resources.contains(_Name.data()))
		{
			MessageBoxAssert("이미 생성한 리소스를 다시 생성하려고 했습니다.");
			return nullptr;
		}

		Resources[_Name.data()] = NewObject;
		return NewObject.get();
	}

	static ResourceType* CreateEngineResource()
	{
		std::shared_ptr<ResourceType> NewObject = std::make_shared<ResourceType>();

		UnnamedResources.push_back(NewObject);
		return NewObject.get();
	}
private:
	static std::map<std::string, std::shared_ptr<ResourceType>> Resources;
	static std::list<std::shared_ptr<ResourceType>> UnnamedResources;
};

template<typename ResourceType>
std::map<std::string, std::shared_ptr<ResourceType>> EngineResource<ResourceType>::Resources;

template<typename ResourceType>
std::list<std::shared_ptr<ResourceType>> EngineResource<ResourceType>::UnnamedResources;