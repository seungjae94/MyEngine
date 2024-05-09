#pragma once

class EnginePath
{
public:
	EnginePath();
	EnginePath(std::string_view _Path);
	EnginePath(std::filesystem::path _PathObject);
	EnginePath(const EnginePath& _Other);
	~EnginePath();

	bool IsRootDirectory() const;
	bool IsDirectory() const;
	bool IsFile() const;
	std::string ToString() const;
	std::string GetFilename() const;

	std::list<EnginePath> GetChildren(const std::set<std::string>& _Extensions) const;
	std::list<EnginePath> GetChildrenRecursive(const std::set<std::string>& _Extensions) const;
	
	void MoveToParentDirectory();
	void MoveToChildDirectory(std::string_view _ChildDirectoryName);
	void MoveToAncestorsChildDirectory(std::string_view _TargetDirectoyName);
protected:


private:
	std::filesystem::path PathObject = std::filesystem::current_path();
};

