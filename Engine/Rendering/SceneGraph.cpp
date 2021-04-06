#include "SceneGraph.h"

unique_ptr<SceneGraph> SceneGraph::sceneGraphInstance = nullptr;
unordered_map<GLuint, vector<Model*>> SceneGraph::sceneModels = unordered_map<GLuint, vector<Model*>>();
map<string, GameObject*> SceneGraph::sceneGameObjects = map<string, GameObject*>();

SceneGraph::SceneGraph()
{
}

SceneGraph::~SceneGraph()
{
	OnDestroy();
}

SceneGraph* SceneGraph::GetInstance()
{
	if (sceneGraphInstance.get() == nullptr) {
		sceneGraphInstance.reset(new SceneGraph);
	}
	return sceneGraphInstance.get();
}

void SceneGraph::OnDestroy()
{
	if (sceneGameObjects.size() > 0) {
		for (auto go : sceneGameObjects) {
			delete go.second; // second = the 2nd stored value
			go.second = nullptr;
		}
		sceneGameObjects.clear();
	}

	if (sceneModels.size() > 0) {
		for (auto entry : sceneModels) {
			if (entry.second.size() > 0) {
				for (auto m : entry.second) {
					delete m;
					m = nullptr;
				}
				entry.second.clear();
			}
		}
		sceneModels.clear();
	}
}

void SceneGraph::AddModel(Model* model_)
{
	GLuint shader = model_->GetShaderProgram();
	if (sceneModels.find(shader) == sceneModels.end()) { // check if shader program ID (key) already exists inside the map
		sceneModels.insert(pair<GLuint, vector<Model*>>(shader, vector<Model*>()));
		sceneModels[shader].reserve(10);
	}
	sceneModels[shader].push_back(model_);
}

void SceneGraph::AddGameObject(GameObject* go_, string tag_)
{
	if (tag_ == "") { // tag is emty
		string newTag = "GameObject" + to_string(sceneGameObjects.size() + 1);
		go_->SetTag(newTag); // set default tag
		sceneGameObjects[newTag] = go_; // add to map
	}
	else if (sceneGameObjects.find(tag_) == sceneGameObjects.end()) { // tag is not emty and it doesn't exist (as a key) inside the map
		go_->SetTag(tag_);
		sceneGameObjects[tag_] = go_;
	}
	else { // tag is not emty and it exists (as a key) inside the map
		Debug::Error("Trying to add a GameObject with a tag " + tag_ + " that already exists", "SceneGraph.cpp", __LINE__);
		string newTag = "GameObject" + to_string(sceneGameObjects.size() + 1);
		go_->SetTag(newTag);
		sceneGameObjects[newTag] = go_;
	}
}

GameObject* SceneGraph::GetGameObject(string tag_)
{
	if (sceneGameObjects.find(tag_) != sceneGameObjects.end()) { // check if gameobject exist in scenegraph
		return sceneGameObjects[tag_];
	}
	return nullptr;
}

void SceneGraph::Update(const float deltaTime_)
{
	for (auto go : sceneGameObjects) {
		go.second->Update(deltaTime_);
	}
}

void SceneGraph::Render(Camera* camera_)
{
	// render models not gameobjects
	for (auto entry : sceneModels) {
		glUseProgram(entry.first);
		for (auto m : entry.second) {
			m->Render(camera_);
		}
	}
}