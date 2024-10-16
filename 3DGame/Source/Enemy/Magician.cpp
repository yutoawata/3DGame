#include "Magician.h"
#include "State\EnemyIdleState.h"
#include "..\Player\Soldier.h"

//�R���X�g���N�^
Magician::Magician(MoverBase* target_, MoverBase* boss_, Vector3 position_, int model_handle)
	: MoverBase(model_handle, ObjectTag::ENEMY) {
	position = Vector3(300.0f, 50.0f, 300.0f);
	scale = Vector3(0.5f, 0.5f, 0.5f);
	rotation = Matrix::GetRotateMatrix(angle);
	target = target_;
	boss = boss_;
	hitPoint = 100;
	speed = 80.0f;
	modelSize = Vector3(20.0f, 50.0f, 20.0f);
	lightBall = new MagicBall(position, target->getPosition() - position, modelSize.y);
	currentState = new EnemyIdleState<Magician>(this);
	AI = new LongRangeAI<Magician>(this);
	hitPointUI = new HPBar(Vector2(400, 50), hitPoint, 1000, 50, "���p�t");
	AddCubeColliderList(new CubeCollider(&checkPosition, &rotation, modelSize));
	isFind = true;
}

//�f�X�g���N�^
Magician::~Magician() {
	delete AI;
	delete currentState;
	delete hitPointUI;
	delete lightBall;
	AI = nullptr;
	currentState = nullptr;
	hitPointUI = nullptr;
	lightBall = nullptr;
}

//�X�V�O����
void Magician::Prepare() {
	if (!isDamage) {
		currentState = currentState->Run();
	}
	
	if (lightBall->IsActive()) {
		lightBall->Prepare();
	}
	//�X�e�[�g�ł̕ύX��ۑ�
	checkPosition = currentState->getHolderPosition();
	angle = currentState->getHolderAngle();
	rotation = Matrix::GetRotateMatrix(angle);
	
	//�O�����x�N�g�����擾
	frontDirection = Vector3(target->getPosition() - position).Normalized();
	frontDirection.y = 0.0f;
}

//�X�V����
void Magician::Update() {
	position = checkPosition;
	
	if (interbalTimer < damageInterbal) {
		interbalTimer += FPSManager::getInstance()->getDeltaTime();
	}

	if (!isDamage) {
		//���݂̃X�e�[�g����A�j���[�V�����̎�ނ��擾
		ChengeAnimation(currentState->getAnimationName());
	}
	else {
		if (IsFinish()) {
			isDamage = false;
		}
	}
	nextAnimID = static_cast<int>(currentAnim);

	//�A�j���[�V�����X�V����
	UpdateAnimation();
	
	//�U�����@�̍X�V����
	lightBall->Update();

	if (hitPoint == 0) {
		ChengeAnimation("DIE");
	}

	//������ԂȂ�
	if (isFind) {
		//�{�X��HP�o�[��\������Ă��Ȃ����
		if (!boss->IsFind()) {
			//HP�o�[��\��
			hitPointUI->setIsVisible(true);
		}
		else {
			//HP�o�[���\��
			hitPointUI->setIsVisible(false);
		}
	}
	else {
		//HP�o�[���\��
		hitPointUI->setIsVisible(false);
	}
}

//�`�揈��
void Magician::Draw() {
	MV1DrawModel(modelHandle);
	lightBall->Draw();
}

//�Փ˔��莞�̏���
void Magician::OnCollision(const ObjectCollider& other_, const ColliderBase::Type& collider_type) {
	if (interbalTimer >= damageInterbal) {
		//�Փˑ��肪�U���p�̓����蔻��@���@�����^�O�łȂ��Ȃ�
		if (collider_type == ColliderBase::Type::WEAPON && other_.getTag() != tag) {
			int damage = 0;
			//�Փˑ��肪�v���C���[�Ȃ�
			if (other_.getTag() == ObjectTag::PLAYER) {
				//�Փˑ���̍U���͂��擾����
				const Soldier* player = other_.getComponent<Soldier>();
				damage = player->getAttackPoint();
			}
			hitPoint -= damage;
			interbalTimer = 0.0f;
			damageInterbal = 1.0f;
			currentAnim = Animation::DAMAGE;
			isDamage = true;
		}
	}
}

void Magician::ChengeAnimation(std::string animation_name) {

	if (animation_name == "Idle") {
		canCreate = true;
		currentAnim = Animation::IDLE;
	}
	else if (animation_name == "Move") {
		currentAnim = Animation::RUN;
	}
	else if (animation_name == "DIE") {
		currentAnim = Animation::DIE;
	}
	else if (animation_name == "Attack") {
		//���e�𔭎˂��Ă��Ȃ��@���@�����t���O��true�Ȃ�
		if (!lightBall->IsActive() && canCreate) {
			currentAnim = Animation::ATTACK;
			Vector3 direction = target->getPosition() - position;
			lightBall->Activate(position, direction.Normalized());
			canCreate = false;
		}
	}
	else {
		//�ΏۊO�̕����񂪓n���ꂽ�ۂ̃f�o�b�N�����L���p
	}
}