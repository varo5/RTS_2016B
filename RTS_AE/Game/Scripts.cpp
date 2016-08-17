#include "stdafx.h"
#include "Scripts.h"


aeScript::aeScript() : aeAddOn()
{
	m_nAddOnID = AddOnId::Scripts;
}

aeScript::~aeScript()
{
}

ScriptId aeScript::GetScriptId()
{
	return m_nScriptID;
}
