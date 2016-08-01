#include "StdAfxflash.h"
#include "avmplus.h"
using namespace avmplus;

#include "AS3NativeWindowRenderMode.h"

namespace avmshell
{
	NativeWindowRenderModeClass::NativeWindowRenderModeClass(VTable* cvtable):ClassClosure(cvtable)
	{
		createVanillaPrototype();
		//prototype = new (core()->GetGC(), cvtable->getExtraSize())TextFieldAutoSizeObject(cvtable, toplevel()->objectClass->prototype, 0);
		//Add your construct code here...
	};
	ScriptObject* NativeWindowRenderModeClass::createInstance(VTable* ivtable, ScriptObject* prototype)
	{
		return new (core()->GetGC(), ivtable->getExtraSize()) NativeWindowRenderModeObject(ivtable, prototype, 0);
		//AS3 'new' opt...Add your init code here...
	}
	NativeWindowRenderModeObject::NativeWindowRenderModeObject(VTable* vtable, ScriptObject* proto, int capacity):ScriptObject(vtable,proto,0)
	{
		//Add your construct code here...
	}
}