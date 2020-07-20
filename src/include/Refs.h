#pragma once
#include <BType.h>
#include <BObject.h>
class BObject;
class BType;

/*/ General abstract reference.
	RefType: Type of the reference. /*/
template<typename RefType>
class Ref
{
	RefType *Ref; public:
	RefType *operator->() const noexcept { return Ref; }
	virtual bool ShouldDestroy() const noexcept = 0;
};

/*/ A Weak reference to objects.
	Object you reference from will
	be destroyed if no strong references hold it. /*/
class WeakRef : Ref<BObject>
{
	virtual bool ShouldDestroy() const noexcept override
		{ return true; }
};

/*/ A Strong reference to objects. 
	Object wont't be destroyed.   /*/
class StrongRef : Ref<BObject>
{
	virtual bool ShouldDestroy() const noexcept override
		{ return false; }
};


/*/ A Weak reference to objects. 
	Weak so that an object can be deleted by GC. /*/
class TypeRef : public Ref<BType>
{
	virtual bool ShouldDestroy() const noexcept override
		{ return true; }
};
