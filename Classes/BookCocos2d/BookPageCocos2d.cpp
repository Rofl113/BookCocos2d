#include "BookPageCocos2d.h"
#include "book/IManagerBookItem.h"



BookPageCocos2d::BookPageCocos2d(PtrCocos2d<cocos2d::Node>& root)
	: ClassBase()
	, m_root(root)
{

}

std::unique_ptr<IManagerBookItem> BookPageCocos2d::createManager(const std::shared_ptr<ManagerActionsData>& data)
{
	return ClassBase::createManager(data);
}
