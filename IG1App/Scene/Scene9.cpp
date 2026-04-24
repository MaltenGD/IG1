#include "Scene9.h"

#include "CompoundEntity.h"
#include "Entity/Sphere.h"
#include "Entity/Cone.h"
#include "Entity/Disk.h"

void Scene9::init()
{
	setGL();
	opaque_gObjects.push_back(new RGBAxes(400.0));

	constexpr float bodyR = 90.0f;
	constexpr float headR = 60.0f;
	constexpr float bodyCenterY = -40.0f;
	constexpr float headCenterY = bodyCenterY + bodyR + headR - 10.0f;

	constexpr float noseH = 34.0f;
	constexpr float noseBaseR = 8.0f;

	constexpr float eyeH = 18.0f;
	constexpr float eyeBaseR = 6.0f;
	constexpr float eyeX = 20.0f;
	constexpr float eyeY = headCenterY + 10.0f;
	constexpr float eyeZ = headR - 5.0f;

	constexpr float hatBrimR = 55.0f;
	constexpr float hatTopR = 35.0f;
	constexpr float hatH = 25.0f;
	constexpr float hatY = headCenterY + headR + 10.0f;

	const glm::vec4 snowColor(243.0f / 255.0f, 243.0f / 255.0f, 243.0f / 255.0f, 1.0f);
	const glm::vec4 noseColor(1.0f, 0.5f, 0.0f, 1.0f);
	const glm::vec4 eyeColor(0.0f, 128.0f / 255.0f, 128.0f / 255.0f, 1.0f);

	Sphere* body = new Sphere(bodyR, 30, 40);
	body->setColor(snowColor);
	body->setModelMat(glm::translate(body->modelMat(), glm::vec3(0.0f, bodyCenterY, 0.0f)));

	Sphere* head = new Sphere(headR, 24, 32);
	head->setColor(snowColor);
	head->setModelMat(glm::translate(head->modelMat(), glm::vec3(0.0f, headCenterY, 0.0f)));

	Cone* nose = new Cone(noseH, noseBaseR, 0.0, 1, 24);
	nose->setColor(noseColor);
	glm::mat4 noseMat = glm::translate(nose->modelMat(), glm::vec3(0.0f, headCenterY, headR + noseH * 0.6f));
	noseMat = glm::rotate(noseMat, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	nose->setModelMat(noseMat);

	Cone* leftEye = new Cone(eyeH, eyeBaseR, 0.0, 1, 16);
	leftEye->setColor(eyeColor);
	glm::mat4 leftEyeMat = glm::translate(leftEye->modelMat(), glm::vec3(-eyeX, eyeY, eyeZ + eyeH * 0.55f));
	leftEyeMat = glm::rotate(leftEyeMat, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	leftEye->setModelMat(leftEyeMat);

	Cone* rightEye = new Cone(eyeH, eyeBaseR, 0.0, 1, 16);
	rightEye->setColor(eyeColor);
	glm::mat4 rightEyeMat = glm::translate(rightEye->modelMat(), glm::vec3(eyeX, eyeY, eyeZ + eyeH * 0.55f));
	rightEyeMat = glm::rotate(rightEyeMat, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	rightEye->setModelMat(rightEyeMat);

	Disk* brim = new Disk(hatBrimR, 0.0, 8, 40);
	brim->setColor(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
	brim->setModelMat(glm::translate(brim->modelMat(), glm::vec3(0.0f, hatY, 0.0f)));

	Cone* hatBody = new Cone(hatH, hatTopR, hatTopR, 1, 40);
	hatBody->setColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	hatBody->setModelMat(glm::translate(hatBody->modelMat(), glm::vec3(0.0f, hatY + hatH * 0.5f, 0.0f)));

	Disk* hatTop = new Disk(hatTopR, 0.0, 6, 40);
	hatTop->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	hatTop->setModelMat(glm::translate(hatTop->modelMat(), glm::vec3(0.0f, hatY + hatH, 0.0f)));

	CompoundEntity* hat = new CompoundEntity();
	hat->addEntity(brim, hatBody, hatTop);

	node = new CompoundEntity();
	node->addEntity(body, head, nose, leftEye, rightEye, hat);

	opaque_gObjects.push_back(node);
}