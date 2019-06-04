#include <iostream>

#include <Components/TransformComp.h>

void Components::TransformComp::Update()
{
	if (m_gameObject.GetComponent<LightComp>() != nullptr)
	{
		m_gameObject.GetComponent<LightComp>()->GetLight()->SetPos(m_gameObject.GetComponent<Components::TransformComp>()->GetTransform()->GetPosition());
	}

	if (m_parent != nullptr)
	{
		SetChildMatrix(m_parent->m_transform->m_transMat);
	}
	//else if (m_gameObject.GetName() == "OrangeLight")
	//		std::cout << "ble\n";
}

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
