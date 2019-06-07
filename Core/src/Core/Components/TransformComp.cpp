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
		SetChildMatrix(m_parent->m_transform->GetTransMat());
	}
}

void Components::TransformComp::Serialize(XMLElement* p_compSegment, XMLDocument& p_xmlDoc) const noexcept
{
        XMLElement* newVariable;
    if (m_transform->GetPosition() != glm::vec3(0))
    {
        newVariable = p_xmlDoc.NewElement("position");
        newVariable->SetAttribute("x", m_transform->GetRawPosition().x);
        newVariable->SetAttribute("y", m_transform->GetRawPosition().y);
        newVariable->SetAttribute("z", m_transform->GetRawPosition().z);
        p_compSegment->InsertEndChild(newVariable);
    }
    if (m_transform->GetRotation() != glm::vec3(0))
    {
        newVariable = p_xmlDoc.NewElement("rotation");
        newVariable->SetAttribute("x", m_transform->GetRotation().x);
        newVariable->SetAttribute("y", m_transform->GetRotation().y);
        newVariable->SetAttribute("z", m_transform->GetRotation().z);
        p_compSegment->InsertEndChild(newVariable);
    }

    if (m_transform->GetScale() != glm::vec3(1))
    {
        newVariable = p_xmlDoc.NewElement("scale");
        newVariable->SetAttribute("x", m_transform->GetScale().x);
        newVariable->SetAttribute("y", m_transform->GetScale().y);
        newVariable->SetAttribute("z", m_transform->GetScale().z);
        p_compSegment->InsertEndChild(newVariable);
    }

}

void Components::TransformComp::Deserialize(XMLElement* p_compSegment) const noexcept
{
    
    XMLElement* compVariable = p_compSegment->FirstChildElement("scale");
	if (compVariable != nullptr)
	{
        glm::vec3 scale;
		compVariable->QueryFloatAttribute("x", &scale.x);
		compVariable->QueryFloatAttribute("y", &scale.y);
		compVariable->QueryFloatAttribute("z", &scale.z);
		m_transform->Scale(scale);
	}
	
	compVariable = p_compSegment->FirstChildElement("position");
    if (compVariable != nullptr)
	{
        glm::vec3 pos;
		compVariable->QueryFloatAttribute("x", &pos.x);
		compVariable->QueryFloatAttribute("y", &pos.y);
		compVariable->QueryFloatAttribute("z", &pos.z);
		m_transform->Translate(pos);
	}
    
    compVariable = p_compSegment->FirstChildElement("rotation");
	if (compVariable != nullptr)
	{
        glm::vec3 rot;
		compVariable->QueryFloatAttribute("x", &rot.x);
		compVariable->QueryFloatAttribute("y", &rot.y);
		compVariable->QueryFloatAttribute("z", &rot.z);
		m_transform->Rotate(rot);
	}

}
