#ifndef SCENEGRAPH
#define SCENEGRAPH

#include <memory>
#include <unordered_map>
#include <map>
#include <vector>
#include "3D/GameObject.h"

class SceneGraph
{
public:
	SceneGraph(const SceneGraph&) = delete;
	SceneGraph(SceneGraph&&) = delete;
	SceneGraph& operator=(const SceneGraph&) = delete;
	SceneGraph& operator=(SceneGraph&&) = delete;

	// Return ref to this scenegraph
	static SceneGraph* GetInstance();

	void OnDestroy();
	void AddModel(Model* model_);
	void AddGameObject(GameObject* go_, string tag_ = "");
	GameObject* GetGameObject(string tag_);

	void Update(const float deltaTime_);
	void Render(Camera* camera_);

private:
	SceneGraph();
	~SceneGraph();

	static unique_ptr<SceneGraph> sceneGraphInstance;
	friend default_delete<SceneGraph>;

	static unordered_map<GLuint, vector<Model*>> sceneModels; // hold Model(s) for each program ID
	static map<string, GameObject*> sceneGameObjects; // hold GameObject_ptr(s) for each tag
};

#endif // !SCENEGRAPH



