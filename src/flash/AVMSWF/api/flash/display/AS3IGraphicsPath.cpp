#include "StdAfxflash.h"
#include "avmplus.h"
using namespace avmplus;
#include "AS3IGraphicsPath.h"
namespace avmshell{
IGraphicsPathClass::IGraphicsPathClass(VTable* cvtable):ClassClosure(cvtable)
{
	createVanillaPrototype();
	//Add your construct code here...
};
ScriptObject* IGraphicsPathClass::createInstance(VTable *ivtable, ScriptObject* prototype)
{
	return new (core()->GetGC(), ivtable->getExtraSize()) IGraphicsPathObject(ivtable, prototype, 0);
	//AS3 'new' opt...Add your init code here...
}
IGraphicsPathObject::IGraphicsPathObject(VTable *vtable, ScriptObject* proto, int capacity): ScriptObject(vtable, proto, 0)
{
	//Add your construct code here...
}
//////////////////////////////////////////////////////////
//Native Method start...
}