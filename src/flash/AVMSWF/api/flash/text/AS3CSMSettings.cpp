#include "StdAfxflash.h"
#include "avmplus.h"
using namespace avmplus;
#include "AS3CSMSettings.h"
namespace avmshell{
CSMSettingsClass::CSMSettingsClass(VTable* cvtable):ClassClosure(cvtable)
{
	createVanillaPrototype();
	//prototype = new (core()->GetGC(), cvtable->getExtraSize())CSMSettingsObject(cvtable, toplevel()->objectClass->prototype, 0);
	//Add your construct code here...
};
ScriptObject* CSMSettingsClass::createInstance(VTable *ivtable, ScriptObject* prototype)
{
	return new (core()->GetGC(), ivtable->getExtraSize()) CSMSettingsObject(ivtable, prototype, 0);
	//AS3 'new' opt...Add your init code here...
}
CSMSettingsObject::CSMSettingsObject(VTable *vtable, ScriptObject* proto, int capacity): ScriptObject(vtable, proto, 0)
{
	//Add your construct code here...
}

}