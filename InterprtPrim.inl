/******************************************************************************

	File: InterprtPrim.Inl

	Description:

	Private inlines for the interpreter's primitive routine bodules

******************************************************************************/

#include "STProcess.h"	// In order to be able to set primitive failure code

#define primitiveSuccess() TRUE

inline void ST::Process::SetPrimitiveFailureCode(SMALLINTEGER code)
{
	m_primitiveFailureCode = integerObjectOf(code);
}

inline void ST::Process::SetPrimitiveFailureData(Oop failureData)
{
	ObjectMemory::countDown(m_primitiveFailureData);
	ObjectMemory::countUp(failureData);
	m_primitiveFailureData = failureData;
}

inline void ST::Process::SetPrimitiveFailureData(OTE* failureData)
{
	ObjectMemory::countDown(m_primitiveFailureData);
	failureData->countUp();
	m_primitiveFailureData = reinterpret_cast<Oop>(failureData);
}

inline void ST::Process::SetPrimitiveFailureData(SMALLINTEGER failureData)
{
	ObjectMemory::countDown(m_primitiveFailureData);
	m_primitiveFailureData = integerObjectOf(failureData);
}

inline BOOL Interpreter::primitiveFailure(int failureCode)
{
	m_registers.activeProcess()->SetPrimitiveFailureCode(failureCode);
	return FALSE;
}

inline BOOL Interpreter::primitiveFailureWith(int failureCode, Oop failureData)
{
	Process* proc = m_registers.activeProcess();
	proc->SetPrimitiveFailureCode(failureCode);
	proc->SetPrimitiveFailureData(failureData);
	return FALSE;
}

inline BOOL Interpreter::primitiveFailureWith(int failureCode, OTE* oteFailure)
{
	ASSERT(!ObjectMemoryIsIntegerObject(oteFailure));
	Process* proc = m_registers.activeProcess();
	proc->SetPrimitiveFailureCode(failureCode);
	proc->SetPrimitiveFailureData(oteFailure);
	return FALSE;
}

// Just to avoid any confusion with Oop overload, give this one a different name
inline BOOL Interpreter::primitiveFailureWithInt(int failureCode, SMALLINTEGER failureData)
{
	Process* proc = m_registers.activeProcess();
	proc->SetPrimitiveFailureCode(failureCode);
	proc->SetPrimitiveFailureData(failureData);
	return FALSE;
}


