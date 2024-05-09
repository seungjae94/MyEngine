#pragma once

class EnginePath
{
public:
	EnginePath();
	~EnginePath();

	EnginePath(const EnginePath& _Other) = delete;
	EnginePath(EnginePath&& _Other) noexcept = delete;
	EnginePath& operator=(const EnginePath& _Other) = delete;
	EnginePath& operator=(EnginePath&& _Other) noexcept = delete;

	bool IsDirectory() const;
	bool IsFile() const;
	std::list<std::string> GetChildrenAbsolutePaths(std::list<std::string> _Extensions) const;
	std::list<std::string> GetChildrenAbsolutePathsRecursive(std::list<std::string> _Extensions) const;
	void MoveToParentDirectory();
	void MoveToChildDirectory(std::string_view _ChildDirectoryName);
	void MoveToAncestorHaving(std::string_view _TargetDirectoyName);
protected:


private:
	std::filesystem::path PathObject = std::filesystem::current_path();

	std::list<std::filesystem::path> GetChildrenPathObjects(std::list<std::string> _Extensions = {}) const;
	std::list<std::filesystem::path> GetChildrenPathObjectsRecursive(std::list<std::string> _Extensions) const;
};

