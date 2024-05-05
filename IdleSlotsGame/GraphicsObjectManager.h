#pragma once
#include <string>
#include <unordered_map>
class GraphicsObject;

typedef std::string ObjKey;
class GraphicsObjectManager
{
private:
	std::unordered_map<ObjKey, GraphicsObject*> mObjMap;
	bool mIsInit = false;
public:
	GraphicsObjectManager() {};
	~GraphicsObjectManager();
	void cleanup();
	bool init();
	GraphicsObject* createAndManageGraphics(const ObjKey& key, const std::string& filePath);
	void deleteBuffer(const ObjKey& key);
	void deleteBuffer(GraphicsObject* pObj);
	GraphicsObject* getObject(const ObjKey& key) const;
};