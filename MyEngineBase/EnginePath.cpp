#include "PreCompile.h"
#include "EnginePath.h"
#include "EngineDebug.h"

EnginePath::EnginePath()
{
	GetChildrenPathObjects();
}

EnginePath::~EnginePath()
{
}

bool EnginePath::IsDirectory() const
{
	return std::filesystem::is_directory(PathObject);
}

bool EnginePath::IsFile() const
{
	return !IsDirectory();
}

std::list<std::string> EnginePath::GetChildrenAbsolutePaths(std::list<std::string> _Extensions) const
{
	return std::list<std::string>();
}

std::list<std::string> EnginePath::GetChildrenAbsolutePathsRecursive(std::list<std::string> _Extensions) const
{
	return std::list<std::string>();
}

void EnginePath::MoveToParentDirectory()
{
	PathObject = PathObject.parent_path();
}

void EnginePath::MoveToChildDirectory(std::string_view _ChildDirectoryName)
{
}

void EnginePath::MoveToAncestorHaving(std::string_view _TargetDirectoyName)
{
}

std::list<std::filesystem::path> EnginePath::GetChildrenPathObjects(std::list<std::string> _Extensions /*= {}*/) const
{
	if (false == IsDirectory())
	{
		MessageBoxAssert("���͸��� �ƴ� ��ο��� �ڽ� ��� ������Ʈ�� �������� �߽��ϴ�.");
		return {};
	}

	bool AllExtensionFindMode = _Extensions.empty();

	std::list<std::filesystem::path> PathObjects;
	std::filesystem::directory_iterator Iter(PathObject);

	for (std::filesystem::directory_entry Entry : Iter)
	{
		if (true == Entry.is_directory())
		{
			continue;
		}

		std::string Ext = Entry.path().extension().string();

		if (true == AllExtensionFindMode)
		{

		}
	}


	return std::list<std::filesystem::path>();
}
