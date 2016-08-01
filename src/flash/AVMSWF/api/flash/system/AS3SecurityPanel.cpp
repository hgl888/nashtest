#include "StdAfxflash.h"
#include "avmplus.h"
using namespace avmplus;
#include "AS3SecurityPanel.h"
namespace avmshell{
SecurityPanelClass::SecurityPanelClass(VTable* cvtable):ClassClosure(cvtable)
{
	createVanillaPrototype();
	//prototype = new (core()->GetGC(), cvtable->getExtraSize())SecurityPanelObject(cvtable, toplevel()->objectClass->prototype, 0);
	//Add your construct code here...
};
ScriptObject* SecurityPanelClass::createInstance(VTable *ivtable, ScriptObject* prototype)
{
	return new (core()->GetGC(), ivtable->getExtraSize()) SecurityPanelObject(ivtable, prototype, 0);
	//AS3 'new' opt...Add your init code here...
}
SecurityPanelObject::SecurityPanelObject(VTable *vtable, ScriptObject* proto, int capacity): ScriptObject(vtable, proto, 0)
{
	//Add your construct code here...
}
//////////////////////////////////////////////////////////
//Native Method start...
}