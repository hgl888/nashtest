#include "StdAfxflash.h"
#include "avmplus.h"
using namespace avmplus;
#include "AS3LocationChangeEvent.h"
namespace avmshell{
LocationChangeEventClass::LocationChangeEventClass(VTable* cvtable):ClassClosure(cvtable)//EventClass(cvtable)
{
	createVanillaPrototype();
	//Add your construct code here...
};
ScriptObject* LocationChangeEventClass::createInstance(VTable *ivtable, ScriptObject* prototype)
{
	return new (core()->GetGC(), ivtable->getExtraSize()) LocationChangeEventObject(ivtable, prototype, 0);
	//AS3 'new' opt...Add your init code here...
}
LocationChangeEventObject::LocationChangeEventObject(VTable *vtable, ScriptObject* proto, int capacity): EventObject(vtable, proto, 0)
{
	//Add your construct code here...
}
//////////////////////////////////////////////////////////
//Native Method start...
Stringp LocationChangeEventObject::AS3_location_get()
{
	return NULL;
}
void LocationChangeEventObject::AS3_location_set(Stringp pLocation)
{

}

void LocationChangeEventObject::AS3_constructor(Stringp pType, bool bubbles, bool cancelable, Stringp location)
{

}
EventObject* LocationChangeEventObject::AS3_clone()
{
	return NULL;
}
Stringp LocationChangeEventObject::AS3_toString()
{
	return NULL;
}

}