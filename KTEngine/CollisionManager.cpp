#include "CollisionManager.h"
#include "CollisionDetectionAlgo.h"
#include "GameObject.h"

CollisionManager* CollisionManager::getInstance()
{
    static CollisionManager* _instance = new CollisionManager();
    return _instance;
}

void CollisionManager::addCollider2D(Ref<Collider2D> collider)
{
    m_colliders.push_back(collider);
}

void CollisionManager::update(float dt)
{
    // Collision detection and resolution
    
    // First pass process transforms
    static std::vector<Collider2D*> transform_pass;
    for (size_t i = 0; i < transform_pass.size(); ++i) {
        delete transform_pass[i];
    }
    transform_pass.clear();
    transform_pass.reserve(m_colliders.size());
    Collider2D* cur = nullptr;
    Ref<Collider2D> curP = nullptr;
    glm::mat4 model(1.0f);
    // Assume transforms are all uniform
    for (size_t i = 0; i < m_colliders.size(); ++i) {
        curP = m_colliders[i];
        curP->gameObject->transform.fillModelMatrix(model);
        switch (curP->m_type) {
        case ColliderType::Circle:
        {
            CircleCollider* cur_cir = new CircleCollider();
            *cur_cir = *(CircleCollider*)curP.get();
            cur_cir->origin = glm::vec3(model * glm::vec4(cur_cir->origin, 1.0f));

            // take x value of the transform and scale radius with that
            cur_cir->radius *= fabs(curP->gameObject->transform.scale[0]);
            cur = cur_cir;
            break; 
        }
        case ColliderType::Polygon:
        {
            PolygonCollider* cur_poly = new PolygonCollider();
            *cur_poly = *(PolygonCollider*)curP.get();
            for (glm::vec3& point : cur_poly->points) {
                point = glm::vec3(model * glm::vec4(point, 1.0f));
            }
            cur = cur_poly;
            break;
        }
        default:
            ekp("UNKNOWN COLLIDER2D TYPE: ", curP->m_type);
        }
        cur->gameObject = curP->gameObject;
        transform_pass.push_back(cur);
    }

    // Basically just iterate through all 
    // colliders for now since there aren't many
    collider_resolution solver;
    for (size_t i = 0; i < transform_pass.size(); ++i) {
        for (size_t j = i + 1; j < transform_pass.size(); ++j) {
            solver = k_col_algo::checkCollision(transform_pass[i], transform_pass[j]);
            // resolve it right away
            if (solver.isCollided) {
                transform_pass[i]->gameObject->transform.move(solver.slide_vec, solver.length + KEPSILON);
            }
        }
    }
}

CollisionManager::~CollisionManager()
{
}

CollisionManager::CollisionManager()
{
}
