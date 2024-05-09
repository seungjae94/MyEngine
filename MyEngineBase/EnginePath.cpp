#include "PreCompile.h"
#include "EnginePath.h"
#include "EngineDebug.h"

EnginePath::EnginePath()
{
}

EnginePath::EnginePath(std::string_view _Path)
	: PathObject(_Path)
{
}

EnginePath::EnginePath(std::filesystem::path _PathObject)
	: PathObject(_PathObject)
{
}

EnginePath::EnginePath(const EnginePath& _Other)
	: PathObject(_Other.PathObject)
{
}

EnginePath::~EnginePath()
{
}


bool EnginePath::IsRootDirectory() const
{
	return PathObject == PathObject.root_path();
}

bool EnginePath::IsDirectory() const
{
	return std::filesystem::is_directory(PathObject);
}

bool EnginePath::IsFile() const
{
	return !IsDirectory();
}

std::string EnginePath::ToString() const
{
	return PathObject.string();
}

std::string EnginePath::GetFilename() const
{
	return PathObject.filename().string();
}

void EnginePath::MoveToParentDirectory()
{
	PathObject = PathObject.parent_path();
}

void EnginePath::MoveToChildDirectory(std::string_view _ChildDirectoryName)
{
	PathObject = PathObject.append(_ChildDirectoryName);
}

void EnginePath::MoveToAncestorsChildDirectory(std::string_view _TargetDirectoyName)
{
	while (true)
	{
		std::filesystem::directory_iterator Iter{ PathObject };
		
		for (const std::filesystem::directory_entry& Entry : Iter)
		{
			if (true == Entry.is_directory() && Entry.path().filename() == _TargetDirectoyName)
			{
				MoveToChildDirectory(_TargetDirectoyName);
				return;
			}
		}

		if (true == IsRootDirectory())
		{
			MessageBoxAssert(std::string("��Ʈ ���͸����� Ž�������� ") + _TargetDirectoyName.data() + "�� ã�� �� �����ϴ�.");
		}

		MoveToParentDirectory();
	}
}

std::list<EnginePath> EnginePath::GetChildren(const std::set<std::string>& _Extensions) const
{
	if (false == IsDirectory())
	{
		MessageBoxAssert("���͸��� �ƴ� ��ο��� �ڽ� ��θ� �������� �߽��ϴ�.");
		return {};
	}

	std::list<EnginePath> Children;
	std::filesystem::directory_iterator Iter{ PathObject };

	for (std::filesystem::directory_entry Entry : Iter)
	{
		std::string FileName = Entry.path().filename().string();
		if (true == Entry.is_directory())
		{
			continue;
		}

		std::string Ext = Entry.path().extension().string();

		if (true == _Extensions.contains(Ext))
		{
			Children.push_back(Entry.path());
		}
	}

	return Children;
}

std::list<EnginePath> EnginePath::GetChildrenRecursive(const std::set<std::string>& _Extensions) const
{
	if (false == IsDirectory())
	{
		MessageBoxAssert("���͸��� �ƴ� ��ο��� �ڽ� ��θ� �������� �߽��ϴ�.");
		return {};
	}

	std::list<EnginePath> Children;
	std::filesystem::directory_iterator Iter(PathObject);

	for (std::filesystem::directory_entry Entry : Iter)
	{
		if (true == Entry.is_directory())
		{
			EnginePath ChildDirectory = Entry.path();
			std::list<EnginePath>&& NewChildren = ChildDirectory.GetChildrenRecursive(_Extensions);
			Children.insert(Children.end(), NewChildren.begin(), NewChildren.end());
			continue;
		}

		std::string Ext = Entry.path().extension().string();

		if (true == _Extensions.contains(Ext))
		{
			Children.push_back(Entry.path());
		}
	}

	return Children;
}
