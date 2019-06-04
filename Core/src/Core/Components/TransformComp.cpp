#include <iostream>

#include <Components/TransformComp.h>

void Components::TransformComp::Serialize(XMLElement* p_compSegment) const noexcept
{
	std::cout << "[TRANSFORM_COMP] Function not implemented\n";
}

void Components::TransformComp::Deserialize(XMLElement* p_compSegment) const noexcept
{
	XMLElement* compVariable = p_compSegment->FirstChildElement("position");
	if (compVariable != nullptr)
	{
		float x, y, z;
		compVariable->QueryFloatAttribute("x", &x);
		compVariable->QueryFloatAttribute("y", &y);
		compVariable->QueryFloatAttribute("z", &z);
		glm::vec3 pos{ x,y,z };
		m_transform->Translate(pos);
	}
}
