#include<windows.h>
//====================================================================
//̽�ⷶΧ����
//������������i������X,Y���õ���Χ
//���⣬�������Ƿ���ȷ
//====================================================================
public:
	int DetectFeld[4];
	void detectFeld(int i, int X, int Y) {

		int HaiFeld = 400;
		int SalmonFeld = 80;
		int KleinfischFeld = 9;//���޸�

		switch (i) {

		case'1':
			DetectFeld[0] = X - HaiFeld;
			DetectFeld[1] = X + HaiFeld;
			DetectFeld[2] = Y - HaiFeld;
			DetectFeld[3] = Y + HaiFeld;
			break;
		case'2':
			DetectFeld[0] = X - SalmonFeld;
			DetectFeld[1] = X + SalmonFeld;
			DetectFeld[2] = Y - SalmonFeld;
			DetectFeld[3] = Y + SalmonFeld;
			break;
		case'3':
			DetectFeld[0] = X - KleinfischFeld;
			DetectFeld[1] = X + KleinfischFeld;
			DetectFeld[2] = Y - KleinfischFeld;
			DetectFeld[3] = Y + KleinfischFeld;
			break;
		default:
			MessageBox(GetForegroundWindow(), "DetectFeld is wrong.", "Error Infomation", 2);
			break;
		};

	}��


		//====================================================================
		//�ж������Ⱥ����
		//�������귶Χ����DetectFeld����������i�����ط�Χ�������Ⱥ����XMax,YMax,û���������Ⱥ����Ueber(�������귶Χ�ڵ�������������
		//i=0(hai),1(salmon),2(kleinfisch)
		// ���⣬�������Ƿ���ȷ������xxx��Ҫ�޸�
		//====================================================================
public:
	int XMax, YMax, Ueber;

	void judegObject(int i, int DetectFeld[]) {
		int j = 0;
		int k = 0;
		int a, amax = 0;//���ڱȴ�С����ʱ������
		XMax = YMax = Ueber;
		if (i = 0) {
			for (j = DetectFeld[0]; j <= DetectFeld[1]; j++) {
				for (k = DetectFeld[2]; k <= DetectFeld[3]; k++) {
					a = xxx(i, j);//xxx(i,j)ΪI,J������������Ⱥ����			
					if (amax < a) {
						amax = a;
						XMax = j;
						YMax = k;
					};
				};
			};
		};
		if (i = 1) {
			for (j = DetectFeld[0]; j <= DetectFeld[1]; j++) {
				for (k = DetectFeld[2]; k <= DetectFeld[3]; k++) {
					a = xxx(i, j);//xxx(i,j)ΪI,J������С��Ⱥ����			
					if (amax < a) {
						amax = a;
						XMax = j;
						YMax = k;
					};
				};
			};
		}��
	};
	//====================================================================
	//����׷��������û����������չ�������㺯��
	// ������������X,Y�������Ⱥ����XMax,YMax,�ж�׷�����ƶ�
	//i=0(hai),1(salmon),2(kleinfisch)
	// ���⣬�������Ƿ���ȷ���漰���������ڣ�������Ϊ����һ����ʱ�������ΪTupdate
	//������ v.Hai,v.Salmon,v.KleinfischΪ����������٣�Hai,40km/h, Salmon 15m/s,С����Ⱥ�ٶ�δ��
	//��ʱ��Ϊһ�θ����ڿ�x,y����ߣ�֮��Ϊ�ٶ��ȶ��������ƶ�
	//====================================================================
	void jagd(X, Y, XMax, Ymax) {
		if (XMax == Ueber) {
			//����ƶ�������
		};
		else if(X=Xmax&&Y=Ymax){
			//��ʳ����;
			
		};
		else {//�´��޸Ĵ˴��ƶ�ģʽ
			if (X - XMax > 0)
				X = X + Tupdate * v.Hai*(-1);
			else
				X= X + Tupdate * v.Hai;
			if (Y - YMax > 0)
				Y = Y + Tupdate * v.Hai*(-1);
			else
				Y = Y+ Tupdate * v.Hai;
		}��

	}��
}��

//====================================================================
//��ʳ������ռ��һ�θ���ʱ�䣬���ø���ǰ��Ⱥ���ݣ������Ⱥ����
// ������������X,Y
//i=0(hai),1(salmon),2(kleinfisch)
// ���⣬�������Ƿ���ȷ
//====================================================================


//====================================================================
//����ƶ�����
//��Ҫ����
//====================================================================


//====================================================================
//С����Ⱥ��������������
//====================================================================