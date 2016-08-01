#include "StdAfxflash.h"
#include "avmplus.h"
using namespace avmplus;
#include "AS3StackFrame.h"
namespace avmshell{
StackFrameClass::StackFrameClass(VTable* cvtable):ClassClosure(cvtable)
{
	createVanillaPrototype();
	//Add your construct code here...
};
ScriptObject* StackFrameClass::createInstance(VTable *ivtable, ScriptObject* prototype)
{
	return new (core()->GetGC(), ivtable->getExtraSize()) StackFrameObject(ivtable, prototype, 0);
	//AS3 'new' opt...Add your init code here...
}
StackFrameObject::StackFrameObject(VTable *vtable, ScriptObject* proto, int capacity): ScriptObject(vtable, proto, 0)
{
	//Add your construct code here...
}
//////////////////////////////////////////////////////////
//Native Method start...
//AvmBox StackFrameObject::AS3_toString(AvmMethodEnv, uint32_t, AvmBox* argv)
//{
//	//Add your act code here...
//	return kAvmThunkUndefined;//Modify this please!
//}

}