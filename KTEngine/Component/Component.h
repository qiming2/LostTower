#pragma once
#include <vector>
#include <string>


class GameObject;
enum class ComponentType {
	// All new component types should go here
	None = 0,
	Collider2D,
	SpriteRenderer,
	Animator,
};

#define COMPONENT_TYPE(_type) \
	public: \
	static ComponentType getStaticType();\
	virtual ComponentType getCompType() const	override; \
	virtual std::string getCompName() const override;

#define IMP_COMPONENT_TYPE(_type) \
	ComponentType _type::getStaticType() {return ComponentType::##_type;}\
	ComponentType _type::getCompType() const {return getStaticType();}\
	std::string _type::getCompName() const {return #_type;}
class Component					 
{
public:
	Component();
	virtual ComponentType getCompType() const = 0;
	virtual std::string getCompName() const = 0;
	// Need to be deleted
	GameObject* gameObject;
};

