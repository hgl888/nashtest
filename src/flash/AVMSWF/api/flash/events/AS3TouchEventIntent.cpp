#include "StdAfxflash.h"
#include "avmplus.h"
using namespace avmplus;
#include "AS3TouchEventIntent.h"
namespace avmshell
{
	TouchEventIntentClass::TouchEventIntentClass(VTable* cvtable):ClassClosure(cvtable)//EventClass(cvtable)
	{
		createVanillaPrototype();
		//Add your construct code here...
	};
	ScriptObject* TouchEventIntentClass::createInstance(VTable *ivtable, ScriptObject* prototype)
	{
		return new (core()->GetGC(), ivtable->getExtraSize()) TouchEventIntentObject(ivtable, prototype, 0);
		//AS3 'new' opt...Add your init code here...
	}
	TouchEventIntentObject::TouchEventIntentObject(VTable *vtable, ScriptObject* proto, int capacity): ScriptObject(vtable, proto, 0)
	{
		//Add your construct code here...
	}
	//////////////////////////////////////////////////////////


}