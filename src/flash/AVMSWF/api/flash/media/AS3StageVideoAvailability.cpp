#include "StdAfxflash.h"
#include "avmplus.h"
using namespace avmplus;
#include "AS3StageVideoAvailability.h"
namespace avmshell{
StageVideoAvailabilityClass::StageVideoAvailabilityClass(VTable* cvtable):ClassClosure(cvtable)
{
	createVanillaPrototype();
	//Add your construct code here...
};
ScriptObject* StageVideoAvailabilityClass::createInstance(VTable *ivtable, ScriptObject* prototype)
{
	return new (core()->GetGC(), ivtable->getExtraSize()) StageVideoAvailabilityObject(ivtable, prototype, 0);
	//AS3 'new' opt...Add your init code here...
}
StageVideoAvailabilityObject::StageVideoAvailabilityObject(VTable *vtable, ScriptObject* proto, int capacity): ScriptObject(vtable, proto, 0)
{
	//Add your construct code here...
}
//////////////////////////////////////////////////////////
//Native Method start...
}