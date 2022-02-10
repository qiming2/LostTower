#include "Camera.h"
#include "Input/KeyListener.h"
#include "Util/Common.h"

Camera::Camera()
{
    direction = glm::vec3(0.0f, 0.0f, -1.0f);
    projection = glm::ortho(-960.0f, 960.0f, -540.0f, 540.0f, -1000.0f, 1000.0f);
    position = glm::vec3(0.0f, 0.0f, 1.0f);
    view = glm::lookAt(position, position + direction, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::mat4(1.0f);
}

Camera* Camera::getInstance() {
    static Camera* instance = new Camera();
    return instance;
}

void Camera::update(float dt) {
    //model = glm::mat4(1.0f);
    //
    //position = model * glm::vec4(position, 1.0f);
    //view = glm::lookAt(position, position + direction, glm::vec3(0.0f, 1.0f, 0.0f));
}

Camera::~Camera()
{
}

glm::mat4 Camera::getOrthoProjectionMatrix()
{
    return projection;
}

glm::mat4 Camera::getView()
{
    return view;
}
