#pragma once
#include<unordered_map>
#include<string>

enum class TagType {
	Player,
	Enemy,
	Needle,
	Goal,
	None,
};

class Tag {
public:
	static std::string GetString(TagType type_) {
		static const std::unordered_map<TagType, std::string> typeMap{
			{TagType ::Player,"Player"},
			{TagType ::Enemy,"Enemy"},
			{TagType::Needle,"Needle"},
			{TagType::Goal,"Goal"},
			{TagType ::None,"None"},
		};

		return typeMap.at(type_);
	}
};