#include <Components/MaterialComp.h>

void Components::MaterialComp::Deserialize(XMLElement* p_compSegment) const noexcept
{
	XMLElement* compVariable = p_compSegment->FirstChildElement("color");
	if (compVariable != nullptr)
	{
		float r{ 1 }, g{ 1 }, b{ 1 };
		compVariable->QueryFloatAttribute("r", &r);
		compVariable->QueryFloatAttribute("g", &g);
		compVariable->QueryFloatAttribute("b", &b);
		m_material->SetColor(r, g, b);
	}

	compVariable = p_compSegment->FirstChildElement("shininess");
	if (compVariable != nullptr)
	{
		float shininess;
		compVariable->QueryFloatText(&shininess);
		m_material->SetShininess(shininess);
	}
}

void Components::MaterialComp::Serialize(XMLElement* p_compSegment) const noexcept
{
	std::cout << "[MATERIAL_COMP] Function not implemented\n";
}

