#include <DxLib.h>
#include "app.h"
#include "config.h"

#define CoGVersion (2.0)

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);//�傫���A�𑜓x
	SetOutApplicationLogValidFlag(FALSE); // ���O���o���Ȃ�
	SetDrawScreen(DX_SCREEN_BACK);

	SetMainWindowText(WINDOW_NAME);//�E�B���h�E�̖��O
	SetWindowSizeExtendRate(WINDOW_EXTEND);//�E�B���h�E�g�嗦
	ChangeWindowMode(WINDOW_MODE); // Window���[�h�̏ꍇ

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	SetAlwaysRunFlag(TRUE);//�E�B���h�E���A�N�e�B�u�ł͂Ȃ���Ԃł�����
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	AppInit();
	while (true) {
		clsDx();
		AppUpdate();
		ClearDrawScreen();
		AppDraw();
		if (ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE) != 0 )
			break;
		ScreenFlip();
	}
	AppRelease();
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
} 