#include "StdAfxflash.h"
#include "avmplus.h"
using namespace avmplus;
#include "AS3NetGroupSendResult.h"
namespace avmshell{
NetGroupSendResultClass::NetGroupSendResultClass(VTable* cvtable):ClassClosure(cvtable)
{
	createVanillaPrototype();
	//Add your construct code here...
};
ScriptObject* NetGroupSendResultClass::createInstance(VTable *ivtable, ScriptObject* prototype)
{
	return new (core()->GetGC(), ivtable->getExtraSize()) NetGroupSendResultObject(ivtable, prototype, 0);
	//AS3 'new' opt...Add your init code here...
}
NetGroupSendResultObject::NetGroupSendResultObject(VTable *vtable, ScriptObject* proto, int capacity): ScriptObject(vtable, proto, 0)
{
	//Add your construct code here...
}
//////////////////////////////////////////////////////////
//Native Method start...
}