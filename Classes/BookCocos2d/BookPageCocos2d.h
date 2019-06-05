#pragma once
// Book lib
#include <book/BookPage.h>
// Cocos2d lib
#include <cocos/2d/CCNode.h>
// Common
#include "Common/PtrCocos2d.h"




class BookPageCocos2d : public BookPage
{
	using ClassBase = BookPage;
	BookPageCocos2d() = delete;
public:
	virtual ~BookPageCocos2d() override = default;
	BookPageCocos2d(PtrCocos2d<cocos2d::Node>& root);

private:
	virtual std::unique_ptr<IManagerBookItem> createManager(const std::shared_ptr<ManagerActionsData>& data) override;

	PtrCocos2d<cocos2d::Node> m_root;
};
