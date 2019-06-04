#include <iostream>

#include <Components/LightComp.h>

void Components::LightComp::Serialize(XMLElement* p_compSegment) const noexcept
{
	std::cout << "[LIGHT_COMP] Function not implemented\n";
}

void Components::LightComp::Deserialize(XMLElement* p_compSegment) const noexcept
{
	XMLElement* compVariable = p_compSegment->FirstChildElement("position");
	if (compVariable != nullptr)
	{
		float x, y, z;
		compVariable->QueryFloatAttribute("x", &x);
		compVariable->QueryFloatAttribute("y", &y);
		compVariable->QueryFloatAttribute("z", &z);
		m_light->SetPos(x, y, z);
	}

	compVariable = p_compSegment->FirstChildElement("color");
	if (compVariable != nullptr)
	{
		float r, g, b;
		compVariable->QueryFloatAttribute("r", &r);
		compVariable->QueryFloatAttribute("g", &g);
		compVariable->QueryFloatAttribute("b", &b);
		m_light->SetColor(r, g, b);
	}

	compVariable = p_compSegment->FirstChildElement("intensity");
	if (compVariable != nullptr)
	{
		float intensity;
		compVariable->QueryFloatText(&intensity);
		m_light->SetIntensity(intensity);
	}

	compVariable = p_compSegment->FirstChildElement("isDirectional");
	if (compVariable != nullptr)
	{
		bool isDirectional;
		compVariable->QueryBoolText(&isDirectional);
		m_light->SetDirectional(isDirectional);
	}
}
