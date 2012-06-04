//-----------------------��������̓��[�U�[��`�N���X-------------------------------------

//DefaultAbstractScene���p�����ăV�[���N���X����������ꍇ�A
//�ȉ��̂��̂���������
//�������o�֐�
//+void Draw()�@�`��֐�
//+void Update()�@����I�ɍs���`��ȊO�̏����֐�
//+std::string GetScene() �������g�̃N���X����\���C�ӂ̕������Ԃ��֐�


//�^�C�g�����
class Title : public scene::DefaultAbstractScene{
public:
	void Draw(){
		std::cout << "Draw: --------------------" << std::endl;
		std::cout << "Draw: Title�V�[���̕`��"  << std::endl;
		std::cout << "Draw:�E�j���[�Q�[��" << std::endl;
		std::cout << "Draw:�E�Z�[�u�f�[�^����" << std::endl;
		std::cout << "Draw:�E�I�v�V����" << std::endl;
	}

	void Update(){
		std::cout << "Update: �L�[�{�[�h�����Ƃ�" << std::endl;
		std::cout << std::endl;

		//������Ŏw�肵�Ď��̃V�[���ֈڍs
		this->next_ = "battle";
	}

	std::string GetScene(){
		return std::string("title");
	}
	virtual ~Title(){}
};

//�o�g�����
class Battle : public scene::DefaultAbstractScene{
public:

	Battle() : count_(0), hero(100, 50){}

	void Draw(){

		std::cout << "Draw: --------------------" << std::endl;
		std::cout << "Draw: Battle�V�[���̕`��" << std::endl;

		//HP�Ƃ�MP�Ƃ����j���[�̕\��
		std::cout << "Draw: HP = " << this->hero.HP << std::endl;
		std::cout << "Draw: MP = " << this->hero.MP << std::endl;

		if(3 < this->count_){
			std::cout << "Draw: �厖�ȃV�[���Ȃ̂�" << this->count_ + 1 << "��`�悵�܂���" << std::endl;
		}
	}
	void Update(){
		std::cout << "Update: Battle�V�[��������G�̓������`������c" << std::endl;
		std::cout << std::endl;

		//�퓬����
		this->RecieveDamage(this->hero);
		this->UseSpell(this->hero);

		if(3 < this->count_)
			this->next_ = "ending";
		this->count_++;
	}

	std::string GetScene(){
		return std::string("battle");
	}

	virtual ~Battle(){}
private:
	int count_;

	struct Chara{
		Chara(int hp, int mp) : HP(hp), MP(mp){} 
		int HP;
		int MP;
	};
	
	Chara hero;

	//�G����̃_���[�W
	void RecieveDamage(Chara& c){
		c.HP -= 15;
	}

	//MP����̎������g��
	void UseSpell(Chara& c){
		c.MP -= 3;
	}


};

//�G���f�B���O���
class Ending : public scene::DefaultAbstractScene{
public:
	void Draw(){
		std::cout << "Draw: --------------------" << std::endl;
		std::cout << "Draw: �G���f�B���O" << std::endl;
	}
	void Update(){
		std::cout << "Update: Ending..." << std::endl;
		std::cout << std::endl;
		this->next_ = "theend";
	}
	std::string GetScene(){
		return std::string("ending");
	}
	virtual ~Ending(){}
};

//The end���
class TheEnd : public scene::DefaultAbstractScene{
public:
	void Draw(){
		std::cout << "Draw: --------------------" << std::endl;
		std::cout << "Draw: ***********The End***************" << std::endl;
	}
	void Update(){
		std::cout << "Update: The End" << std::endl;
		std::cout << std::endl;
	}
	std::string GetScene(){
		return std::string("theend");
	}
	virtual ~TheEnd(){}
};

//�A�z�z��̊��蓖�Ă��s���N���X���`����
template<class AbstractScene = scene::DefaultAbstractScene>
struct EspoirSceneAssignment
{
	typedef std::string KeyType;
	typedef boost::shared_ptr<AbstractScene> SPAbs;
	typedef boost::unordered_map<KeyType, SPAbs> Assoc;
	
	//���[�U�[�͂��̊֐������̌`�ŕK���������Ȃ���΂Ȃ�Ȃ�
	//�߂�l: �ŏ��ɊJ�n����V�[����Key
	//����: ���蓖�Ă�A�z�z��
	static KeyType Assigne(Assoc& assoc){
		const std::string title("title");
		assoc[title] = SPAbs(new Title);
		assoc["battle"] = SPAbs(new Battle);
		assoc["ending"] = SPAbs(new Ending);
		assoc["theend"] = SPAbs(new TheEnd);
		//...
		//�g���V�[���N���X�̐���������

		return title;
	}

};


