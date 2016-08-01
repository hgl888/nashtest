#include "StdAfxflash.h"
#include "avmplus.h"
using namespace avmplus;
#include "AS3VideoStatus.h"
namespace avmshell{
VideoStatusClass::VideoStatusClass(VTable* cvtable):ClassClosure(cvtable)
{
	createVanillaPrototype();
	//Add your construct code here...
};
ScriptObject* VideoStatusClass::createInstance(VTable *ivtable, ScriptObject* prototype)
{
	return new (core()->GetGC(), ivtable->getExtraSize()) VideoStatusObject(ivtable, prototype, 0);
	//AS3 'new' opt...Add your init code here...
}
VideoStatusObject::VideoStatusObject(VTable *vtable, ScriptObject* proto, int capacity): ScriptObject(vtable, proto, 0)
{
	//Add your construct code here...
}
//////////////////////////////////////////////////////////
//Native Method start...
}