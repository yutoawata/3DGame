#include "Soldier.h"
#include "..\Enemy\Mutant.h"

const int Soldier::ATTACK_SOUND = LoadSoundMem("Sound/Slash.mp3");

//�R���X�g���N�^
Soldier::Soldier(Vector3 position_, int model_halde)
	: MoverBase(position_, Vector3(0.0f, DX_PI_F / 2.0f, 0.0f), Vector3(0.5f, 0.5f, 0.5f),
				model_halde, HIT_POINT, ATTACK_POINT, ObjectTag::PLAYER) {
	currentState = new IdleState<Soldier>(this);
	camera = new Camera(position);
	hitPointUI = new HPBar(Vector2(20, 1000), hitPoint, 800, 40, "�v���C���[");
	speed = 1.0f;
	rotation = Matrix::GetRotateMatrix(angle);
	modelSize = Vector3(10.0f, 40.0f, 10.0f);
	//���f���̓����蔻���ǉ�
	AddCubeColliderList(new CubeCollider(&checkPosition, &rotation, modelSize));
	
	//�U���p�̓����蔻���u�����f���̃t���[���̍��W���擾
	attackPosition = Vector3(MV1GetFramePosition(modelHandle, WEAPON_FRAME_NUM));
	//����̃{�[���̍��W�ϊ��s����擾
	MATRIX transformMatrix = MV1GetFrameLocalWorldMatrix(modelHandle, WEAPON_FRAME_NUM);
	//���W�ϊ��s�񂩂��]�v�f�𒊏o
	Matrix rotationMatrix = GetRotationMatrix(Matrix(transformMatrix));
	weaponRotation = rotationMatrix;
	//�U���p�����蔻���ǉ�
	Vector3 weaponLength = Vector3(2.0f, 35.0f, 2.0f);
	weaponColliderNum = AddCubeColliderList(new CubeCollider(&attackPosition, &weaponRotation, weaponLength, ColliderBase::Type::WEAPON));
	cubeColliders[weaponColliderNum]->setIsActive(false);
	hitPointUI->setIsVisible(true);
}

//�f�X�g���N�^
Soldier::~Soldier() {
	delete camera;
	delete currentState;
	delete hitPointUI;
	camera = nullptr;
	currentState = nullptr;
	hitPointUI = nullptr;
	MV1DeleteModel(modelHandle);
	DeleteSoundMem(ATTACK_SOUND);
}

//�X�V�O����
void Soldier::Prepare() {
	//�O�����x�N�g�����Z�o
	frontDirection = Vector3(position - camera->getPosition());
	frontDirection.y = 0.0f;
	frontDirection = frontDirection.Normalized();

	//�X�V�����̑O�Ɉړ���̍��W�𓖂��蔻��p�̍��W�ɑ��
	currentState = currentState->Run();
	checkPosition = currentState->getHolderPosition();

	//�U���p�̓����蔻���u�����f���̃t���[���̍��W���擾
	attackPosition = Vector3(MV1GetFramePosition(modelHandle, WEAPON_FRAME_NUM));

	//����̃{�[���̍��W�ϊ��s����擾
	MATRIX transformMatrix = MV1GetFrameLocalWorldMatrix(modelHandle, WEAPON_FRAME_NUM);
	//���W�ϊ��s�񂩂��]�v�f�𒊏o
	Matrix rotationMatrix = GetRotationMatrix(Matrix(transformMatrix));
	weaponRotation = rotationMatrix;

	angle = currentState->getHolderAngle();
	rotation = Matrix::GetRotateMatrix(angle);
	isGround = false;
	isCollision = false;
}

//�X�V����
void Soldier::Update() {
	position = checkPosition;

	if (interbalTimer < damageInterbal) {
		interbalTimer += FPSManager::getInstance()->getDeltaTime();
	}

	if (!isDamage) {
		//���݂̃X�e�[�g����A�j���[�V�����̎�ނ��擾
		ChengeAnimation(currentState->getAnimationName());
	}

	if (isDamage && IsFinish()) {
		isDamage = false;
	}

	if (!CheckHitKey(KEY_INPUT_LALT)) {
		camera->Update(position);
	}
	
	nextAnimID = static_cast<int>(currentAnim);
	UpdateAnimation();
}

//�`�揈��
void Soldier::Draw() {
	MV1DrawModel(modelHandle);
}

//�Փ˔��莞�̏���
void Soldier::OnCollision(const ObjectCollider& other_, const ColliderBase::Type& collider_type) {
	//�_���[�W���󂯂�ȏソ���Ă�����
	if (interbalTimer >= damageInterbal && currentAnim != Animation::AVOID) {
		if (collider_type == ColliderBase::Type::WEAPON) {
			int damage = 0;
			if (other_.getTag() == ObjectTag::ENEMY) {
				//�_���[�W�ʂ��擾
				const MoverBase* enemy = other_.getComponent<MoverBase>();
				hitPoint -= enemy->getAttackPoint();
				//�_���[�W�Ԋu�̌v�������Z�b�g
				damageInterbal = 1.0f;
				interbalTimer = 0;
				currentAnim = Animation::DAMAGE;
				isDamage = true;	
			}
		}
	}
	if (collider_type == ColliderBase::Type::BODY && CheckSoundMem(ATTACK_SOUND) == FALSE) {
		//�U�����ʉ����ŏ�����o�b�N�O���E���h�Đ�
		PlaySoundMem(ATTACK_SOUND, DX_PLAYTYPE_BACK, TRUE);
	}
	if (other_.getTag() == ObjectTag::FIELD) {
		isGround = true;
	}
}

//�A�j���[�V�����̑J�ڏ���
void Soldier::ChengeAnimation(std::string animation_name) {

	if (animation_name == "Idle") {
		cubeColliders[weaponColliderNum]->setIsActive(false);
		currentAnim = Animation::IDLE;
	}
	else if (animation_name == "Move") {
		cubeColliders[weaponColliderNum]->setIsActive(false);
		currentAnim = Animation::WALK;
	}
	else if (animation_name == "Run") {
		cubeColliders[weaponColliderNum]->setIsActive(false);
		currentAnim = Animation::RUN;
	}
	else if (animation_name == "Jump") {
		cubeColliders[weaponColliderNum]->setIsActive(false);
		currentAnim = Animation::JUMP;
	}
	else if (animation_name == "Avoid") {
		cubeColliders[weaponColliderNum]->setIsActive(false);
		currentAnim = Animation::AVOID;
	}
	else if (animation_name == "Attack") {
		cubeColliders[weaponColliderNum]->setIsActive(true);
		currentAnim = Animation::ATTACK;
	}
	else {
		//�ΏۊO�̕����񂪓n���ꂽ�ۂ̃f�o�b�N�����L���p
	}
}
