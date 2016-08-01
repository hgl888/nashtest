#include "StdAfxflash.h"
#include "avmplus.h"
using namespace avmplus;
#include "AS3FontType.h"
namespace avmshell{
FontTypeClass::FontTypeClass(VTable* cvtable):ClassClosure(cvtable)
{
	createVanillaPrototype();
	//prototype = new (core()->GetGC(), cvtable->getExtraSize())FontTypeObject(cvtable, toplevel()->objectClass->prototype, 0);
	//Add your construct code here...
};
ScriptObject* FontTypeClass::createInstance(VTable *ivtable, ScriptObject* prototype)
{
	return new (core()->GetGC(), ivtable->getExtraSize()) FontTypeObject(ivtable, prototype, 0);
	//AS3 'new' opt...Add your init code here...
}
FontTypeObject::FontTypeObject(VTable *vtable, ScriptObject* proto, int capacity): ScriptObject(vtable, proto, 0)
{
	//Add your construct code here...
}
//////////////////////////////////////////////////////////
//Native Method start...
}