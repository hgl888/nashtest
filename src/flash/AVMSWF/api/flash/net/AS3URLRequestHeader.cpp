#include "StdAfxflash.h"
#include "avmplus.h"
using namespace avmplus;
#include "AS3URLRequestHeader.h"
namespace avmshell{
URLRequestHeaderClass::URLRequestHeaderClass(VTable* cvtable):ClassClosure(cvtable)
{
	createVanillaPrototype();
	//prototype = new (core()->GetGC(), cvtable->getExtraSize())URLRequestHeaderObject(cvtable, toplevel()->objectClass->prototype, 0);
	//Add your construct code here...
};
ScriptObject* URLRequestHeaderClass::createInstance(VTable *ivtable, ScriptObject* prototype)
{
	return new (core()->GetGC(), ivtable->getExtraSize()) URLRequestHeaderObject(ivtable, prototype, 0);
	//AS3 'new' opt...Add your init code here...
}
URLRequestHeaderObject::URLRequestHeaderObject(VTable *vtable, ScriptObject* proto, int capacity): ScriptObject(vtable, proto, 0)
{
	//Add your construct code here...
}
//////////////////////////////////////////////////////////
//Native Method start...
/*AvmBox URLRequestHeaderObject::AS3_name_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox URLRequestHeaderObject::AS3_name_set(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox URLRequestHeaderObject::AS3_value_get(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

AvmBox URLRequestHeaderObject::AS3_value_set(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}

//AS3 contructor function..
AvmBox URLRequestHeaderObject::AS3_constructor(AvmMethodEnv, uint32_t, AvmBox* argv)
{
	//Add your act code here...
	return kAvmThunkUndefined;//Modify this please!
}*/

}