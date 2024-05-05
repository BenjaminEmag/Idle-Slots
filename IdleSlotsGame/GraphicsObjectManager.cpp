#include "GraphicsObjectManager.h"
#include "GraphicsObject.h"

GraphicsObjectManager::~GraphicsObjectManager()
{
	cleanup();
	mIsInit = false;
}

void GraphicsObjectManager::cleanup()
{
	if (!mIsInit)
		return;
	for (auto& i : mObjMap)
	{
		GraphicsObject* pObj = i.second;
		delete pObj;
		pObj = nullptr;
	}
	mObjMap.clear();
}

bool GraphicsObjectManager::init()
{
	if (mIsInit)
		cleanup();
	mIsInit = true;
	return true;
}

GraphicsObject* GraphicsObjectManager::createAndManageGraphics(const ObjKey& key, const std::string& filePath)
{
	GraphicsObject* pObj = nullptr;
	auto i = mObjMap.find(key);
	if (i == mObjMap.end())
	{
		pObj = new GraphicsObject(filePath);
		mObjMap[key] = pObj;
	}
	return pObj;
}

void GraphicsObjectManager::deleteBuffer(const ObjKey& key)
{
	auto i = mObjMap.find(key);
	if (i != mObjMap.end())
	{
		delete i->second;
		mObjMap.erase(i);
	}
}

void GraphicsObjectManager::deleteBuffer(GraphicsObject* pObj)
{
	for (auto i : mObjMap)
	{
		if (pObj == i.second)
		{
			delete pObj;
			mObjMap.erase(i.first);
			return;
		}
	}
}

GraphicsObject* GraphicsObjectManager::getObject(const ObjKey& key) const
{
	auto i = mObjMap.find(key);
	if (i != mObjMap.end())
		return i->second;
	else return nullptr;
}
