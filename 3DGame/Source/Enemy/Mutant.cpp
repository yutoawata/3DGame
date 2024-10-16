#include "Mutant.h"
#include "..\Player\Soldier.h"

const float Mutant::MOVE_SPEED = 80.0f;
const float Mutant::SEARCH_DISTANCE = 180.0f;

//�R���X�g���N�^
Mutant::Mutant(MoverBase* target_, Vector3 position_, int model_handle)
	: MoverBase(position_, Vector3::ZERO, Vector3(1.0f, 1.0f, 1.0f), model_handle, HIT_POINT, ATTACK_POINT,ObjectTag::ENEMY) {
	currentState = new EnemyIdleState<Mutant>(this);
	rotation = Matrix::GetRotateMatrix(angle);
	target = target_;
	speed = MOVE_SPEED;
	modelSize = Vector3(30.0f, 80.0f, 30.0f);
	isFind = true;
	AI = new BossAI<Mutant>(this);
	hitPointUI = new HPBar(Vector2(400, 50), hitPoint, 1000, 50, "�~���[�^���g");
	//���f���̓����蔻���ǉ�
	AddCubeColliderList(new CubeCollider(&checkPosition, &rotation, modelSize));

	////�U���p�̓����蔻���u�����f���̃t���[���̍��W���擾
	weaponPosition = Vector3(MV1GetFramePosition(modelHandle, WEAPON_FRAME_NUM));
	//MATRIX matrix = MV1GetFrameLocalMatrix(modelHandle, WEAPON_FRAME_NUM);
	weaponRotation = Matrix(MV1GetFrameLocalMatrix(modelHandle, WEAPON_FRAME_NUM));
	////�U���p�����蔻���ǉ�
	Vector3 length = Vector3(20.0f, 50.0f, 20.0f);
	attackColliderNum = AddCubeColliderList(new CubeCollider(&weaponPosition, &weaponRotation, length, ColliderBase::Type::WEAPON));
}

//�f�X�g���N�^
Mutant::~Mutant() {
	delete AI;
	delete currentState;
	delete hitPointUI;
}

//�X�V�O����
void Mutant::Prepare() {
	
	if (!isDamage) {
		currentState = currentState->Run();
	}
	
	//�X�e�[�g�ł̕ύX���擾
	checkPosition = currentState->getHolderPosition();
	angle = currentState->getHolderAngle();
	rotation = Matrix::GetRotateMatrix(angle);

	//�O�����x�N�g�����Z�o
	frontDirection = Vector3(target->getPosition() - position).Normalized();
	frontDirection.y = 0.0f;

	//�U���p�̓����蔻���u�����f���̃t���[���̍��W���擾
	weaponPosition = Vector3(MV1GetFramePosition(modelHandle, WEAPON_FRAME_NUM));
	
	//����̃{�[���̍��W�ϊ��s����擾
	MATRIX transformMatrix = MV1GetFrameLocalWorldMatrix(modelHandle, WEAPON_FRAME_NUM);
	//���W�ϊ��s�񂩂��]�v�f�𒊏o
	Matrix rotationMatrix = GetRotationMatrix(Matrix(transformMatrix));
	weaponRotation = rotationMatrix;

	isGround = false;
	isCollision = false;
}

//�X�V����
void Mutant::Update() {

	position = checkPosition;

	if (intervalTimer < attackInterval) {
		//�_���[�W��^����Ԋu�̃^�C�}�[�����Z����
		intervalTimer += FPSManager::getInstance()->getDeltaTime();
	}
	
	if (!isDamage) {
		//���݂̃X�e�[�g����A�j���[�V�����̎�ނ��擾
		ChengeAnimation(currentState->getAnimationName());
	}
	//���݂̃A�j���[�V������ۑ�
	nextAnimID = static_cast<int>(currentAnim);

	//�_���[�W��Ԃ��I�������Ȃ�
	if (isDamage && IsFinish()) {
		isDamage = false;
	}

	//�v���C���[�𔭌������Ȃ�
	if (isFind) {
		//HP�o�[��\��
		hitPointUI->setIsVisible(true);
	}
	else {
		//HP�o�[���\��
		hitPointUI->setIsVisible(false);
	}

	//HP��0�ɂȂ����Ȃ�
	if (hitPoint == 0) {
		currentAnim = Animation::DIE;
	}

	//�A�j���[�V�����X�V����
	UpdateAnimation();

	CheckFind();
}

//�`�揈��
void Mutant::Draw() {
	MV1DrawModel(modelHandle);
}

//�Փ˔��莞�̏���
void Mutant::OnCollision(const ObjectCollider& other_, const ColliderBase::Type& collider_type) {
	if (intervalTimer >= attackInterval) {
		//�Փˑ��肪�U���p�̓����蔻��@���@�����^�O�łȂ��Ȃ�
		if (collider_type == ColliderBase::Type::WEAPON && other_.getTag() != tag) {
			int damage = 0;
			//�Փˑ��肪�v���C���[�Ȃ�
			if (other_.getTag() == ObjectTag::PLAYER) {
				//�Փˑ���̍U���͂��擾����
				const Soldier* player = other_.getComponent<Soldier>();
				damage = player->getAttackPoint();
				currentAnim = Animation::DAMAGE;
				isDamage = true;
			}
			hitPoint -= damage;
			intervalTimer = 0.0f;
			attackInterval = 1.0f;
		}
	}
}

//�A�j���[�V�����̑J�ڏ���
void Mutant::ChengeAnimation(std::string animation_name) {

	if (animation_name == "Idle") {
		cubeColliders[attackColliderNum]->setIsActive(false);
		currentAnim = Animation::IDLE;
	}
	else if (animation_name == "Move") {
		cubeColliders[attackColliderNum]->setIsActive(false);
		currentAnim = Animation::WALK;
	}
	else if (animation_name == "Run") {
		cubeColliders[attackColliderNum]->setIsActive(false);
		currentAnim = Animation::RUN;
	}
	else if (animation_name == "Jump") {
		cubeColliders[attackColliderNum]->setIsActive(false);
		currentAnim = Animation::JUMP;
	}
	else if (animation_name == "DIE") {
		cubeColliders[attackColliderNum]->setIsActive(false);
		currentAnim = Animation::DIE;
	}
	else if (animation_name == "Attack") {
		cubeColliders[attackColliderNum]->setIsActive(true);
		currentAnim = Animation::ATTACK;
	}
	else {
		//�ΏۊO�̕����񂪓n���ꂽ�ۂ̃f�o�b�N�����L���p
	}
}

void Mutant::CheckFind() {
	Vector3 distance = target->getPosition() - position;
	isFind =  (distance.getSize() <= SEARCH_DISTANCE);
}