#include "stdafx.h"
#include "BaseClass.h"

/************************************************************************************************************************/
/* Constructors implementation                                         													*/
/************************************************************************************************************************/
///Default constructor
aeBaseClass::aeBaseClass()
{
	m_nClassID = ClassId::BaseClass;
}
///Destructor
aeBaseClass::~aeBaseClass()
{
}

/************************************************************************************************************************/
/* Functions implementation                                            													*/
/************************************************************************************************************************/

ClassId aeBaseClass::GetClassID()
{
	return m_nClassID;
}

void aeBaseClass::SetParent(aeBaseClass* pNewParent) {
	m_pParent = pNewParent;
}

aeBaseClass* aeBaseClass::GetParent()
{
	return m_pParent;
}

