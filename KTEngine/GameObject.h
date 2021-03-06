#pragma once
#include <string>
#include "Transform.h"
#include "IMGUI/imgui.h"
#include "Window.h"
#include "Component.h"
#include "Collider2D.h"

class GameObject
{
public:
	GameObject();
	GameObject(const std::string& in_tag);
	~GameObject();

	Transform transform;
	std::string tag;
	

	template <typename T>
	Ref<T> getComponentByType()
	{
		for (Ref<Component> cmp : comps) {
			if (cmp->getCompType() == T::getStaticType()) {
				// Not sure if this would cause performance issue or not
				return std::dynamic_pointer_cast<T>(cmp);
			}
		}
		return nullptr;
	}
	virtual void addComponent(Ref<Component> comp);
	virtual void update(float dt);
	virtual void imgui();
	virtual void onTriggerEnter(Collider2D*);
	virtual void onTrigger(Collider2D*);
	virtual void onTriggerExit(Collider2D*);
private:
	std::vector<Ref<Component>> comps;
};

