#include "StdAfxflash.h"
#include "avmplus.h"
using namespace avmplus;
#include "AIR.h"
namespace avmshell{
AccessibilityImplementationClass::AccessibilityImplementationClass(VTable* cvtable):ClassClosure(cvtable)
{
	createVanillaPrototype();
	//prototype = new (core()->GetGC(), cvtable->getExtraSize())AccessibilityObject(cvtable, toplevel()->objectClass->prototype, 0);
	//Add your construct code here...
};
ScriptObject* AccessibilityImplementationClass::createInstance(VTable *ivtable, ScriptObject* prototype)
{
	return new (core()->GetGC(), ivtable->getExtraSize()) AccessibilityImplementationObject(ivtable, prototype, 0);
	//AS3 'new' opt...Add your init code here...
}
AccessibilityImplementationObject::AccessibilityImplementationObject(VTable *vtable, ScriptObject* proto, int capacity): ScriptObject(vtable, proto, 0)
{
	//Add your construct code here...
}
//////////////////////////////////////////////////////////
//Native Method start...


}