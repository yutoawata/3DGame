#include "MagicBall.h"
#include "..\..\ManagerClass\FPSManager.h"

const float MagicBall::ACTIVE_TIME = 5.0f;
const float MagicBall::IDLING_TIME = 2.0f;

//�R���X�g���N�^
MagicBall::MagicBall(Vector3 position_, Vector3 direction_, float high_, int model_handle)
	: MoverBase(position_, model_handle, ObjectTag::ENEMY){
	direction = direction_.Normalized();
	scale = Vector3(0.3f, 0.3f, 0.3f);
	position = position_ + (direction * radius);
	rotation = Matrix::GetRotateMatrix(angle);
	modelSize = Vector3(radius, radius, radius);
	high = high_;
	attackPoint = 15;
	AddSphereColliderList(new SphereCollider(&position, &rotation, radius, ColliderBase::Type::WEAPON));
	Inactivate();
}

//�f�X�g���N�^
MagicBall::~MagicBall() {}

//�X�V�O����
void MagicBall::Prepare() {
	//�I�u�W�F�N�g�Əo����Ԃ𓯊�
	sphereColliders[colliderNum]->setIsActive(isActive);
}

//�X�V����
void MagicBall::Update() {

	if (isActive) {
		timer += FPSManager::getInstance()->getDeltaTime();
		UpdateAnimation();
		
		//�ҋ@���Ԃ��߂�����
		if (timer >= IDLING_TIME) {
			//�ړ������֐i��
			position += direction.Normalized() * speed * FPSManager::getInstance()->getDeltaTime();
		}
		else if (timer >= ACTIVE_TIME) {//�o�����Ԃ��߂�����
			Inactivate();//��A�N�e�B�u������
		}
	}
}

//�`�揈��
void MagicBall::Draw() {
	if (isActive) {
		MV1DrawModel(modelHandle);
	}
}

//�Փ˔��莞�̏���
void MagicBall::OnCollision(const ObjectCollider& other_, const ColliderBase::Type& collider_type) {

	if (other_.getTag() == ObjectTag::PLAYER) {
		Inactivate();
	}
}

//�A�N�e�B�u������
void MagicBall::Activate(Vector3 position_, Vector3 direction_) {
	direction = direction_.Normalized();
	position = position_ + (direction * radius);
	position.y += high;
	isActive = true;
}

//��A�N�e�B�u������
void MagicBall::Inactivate() {
	isActive = false;
	isBrake = true;
	sphereColliders[colliderNum]->setIsActive(isActive);
	timer = 0.0f;
}