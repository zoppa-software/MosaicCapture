#pragma once

#include <Windowsx.h>
#include <dwmapi.h>
#include "CustomDrawButton.h"

namespace Dwm
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>�G�A����L���ɂ����E�B���h�E�t�H�[�������B</summary>
	public ref class DwmForm
        : public System::Windows::Forms::Form
	{
    public:
        /// <summary>�g����]�T��B</summary>
        static const int BAR_PIXEL = 5;

        /// <summary>����{�^���T�C�Y�i���j</summary>
        static const int BTN_WIDTH = 28;

        /// <summary>����{�^���T�C�Y�i���j</summary>
        static const int BTN_HEIGHT = 24;

    private:
        // �g�̑傫���ێ�
        int borderLeft, borderRight, borderTop, borderBottom;

        // �e�{�^���Q��
        Dwm::CloseButton ^ closeBtn;
        Dwm::MaximumButton ^ maximumBtn;
        Dwm::MinimumButton ^ minimumBtn;

        // �g
        bool managedBorder;

        // �g����p�ɃJ�[�\�����ύX���Ȃ�ΐ^
        bool changedCursor;

        // �f�U�C�i�ϐ�
        System::ComponentModel::Container ^components;

        // ���O�̃E�B���h�E�\�����
        FormWindowState prevState;

    public:
        /// <summary>�G�A�����L���Ȃ�ΐ^��Ԃ��B</summary>
        property bool DwmIsCompositionEnabled
        {
            bool get() {
                int res;
                HRESULT hr = ::DwmIsCompositionEnabled(&res);
                return (bool)(SUCCEEDED(hr) && res);
            }
        }

    protected:
        /// <summary>�E�B���h�E�̓�����ʂ��擾����B</summary>
        /// <return>������ʁB</return>
        property System::Windows::Forms::CreateParams ^ CreateParams
        {
            System::Windows::Forms::CreateParams ^ get() override
            {
                System::Windows::Forms::CreateParams ^ cp = Control::CreateParams;
                cp->ClassStyle |= CS_DROPSHADOW;
                return cp;
            }
        }

        //---------------------------------------------------------------------
        // �R���X�g���N�^�A�f�X�g���N�^
        //---------------------------------------------------------------------
	public:
        /// <summary>�R���X�g���N�^�B</summary>
        DwmForm();

		/// <summary>�f�X�g���N�^�B</summary>
        virtual ~DwmForm();

        //---------------------------------------------------------------------
        // �C�x���g�n���h��
        //---------------------------------------------------------------------
    protected:
        /// <summary>�R���|�[�l���g�̏��������s���B</summary>
        void InitializeComponent();

        /// <summary>�����\���C�x���g�n���h���B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        virtual void OnShown(EventArgs ^ e) override;

        /// <summary>�T�C�Y�ύX�C�x���g�n���h���B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        virtual void OnSizeChanged(EventArgs ^ e) override;

    private:
        /// <summary>�E�C���h�E����{�^���̈ʒu���C������B</summary>
        void AjustControlButtonPosition();

        //---------------------------------------------------------------------
        // �{�^������
        //---------------------------------------------------------------------
    private:
        /// <summary>�u�ŏ����v�{�^�������C�x���g�B</summary>
        /// <param name="sender">�C�x���g���s���B</param>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void minimumBtn_Click(Object ^ sender, EventArgs ^ e);

        /// <summary>�u�ő剻�v�{�^�������C�x���g�B</summary>
        /// <param name="sender">�C�x���g���s���B</param>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void maximumBtn_Click(Object ^ sender, EventArgs ^ e);

        /// <summary>�u����v�{�^�������C�x���g�B</summary>
        /// <param name="sender">�C�x���g���s���B</param>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void closeBtn_Click(Object ^ sender, EventArgs ^ e);

        //---------------------------------------------------------------------
        // �E�B���h�E����
        //---------------------------------------------------------------------
    protected:
        /// <summary>�E�B���h�E�v���V�[�W���B</summary>
        /// <param name="m">���b�Z�[�W�\���́B</param>
        virtual void WndProc(Message% m) override;

        /// <summary>�G�A����������g�̕���ݒ肷��B</summary>
        /// <param name="leftWidth">���g���B</param>
        /// <param name="rightWidth">�E�g���B</param>
        /// <param name="topHeight">�㕔�g�����B</param>
        /// <param name="bottomHeight">�����g�����B</param>
        void DwmExtendFrameIntoClientArea(int leftWidth, int rightWidth, int topHeight, int bottomHeight);

    private:
        /// <summary>Dwm����̂��߂̃��b�Z�[�W����������B</summary>
        /// <param name="handle">�E�B���h�E�n���h���B</param>
        /// <param name="msg">���b�Z�[�W�B</param>
        /// <param name="wprm">W�p�����[�^�B</param>
        /// <param name="lprm">L�p�����[�^�B</param>
        /// <return>���b�Z�[�W������������^��Ԃ��B</return>
        bool WindProcByDwm(IntPtr handle, int msg, IntPtr wprm, IntPtr lprm);

        /// <summary>�E�B���h�E�q�b�g�e�X�g�B</summary>
        /// <param name="handle">�E�B���h�E�n���h���B</param>
        /// <param name="wprm">W�p�����[�^�B</param>
        /// <param name="lprm">L�p�����[�^�B</param>
        /// <return>���b�Z�[�W������������^��Ԃ��B</return>
        LRESULT HitTestNCA(HWND hWnd, WPARAM wParam, LPARAM lParam);

        /// <summary>�E�B���h�E����p�ɃJ�[�\����ύX�B</summary>
        /// <param name="posmsg">�}�E�X�ʒu���������b�Z�[�W�B</param>
        void ChangeCursorDwm(LRESULT posmsg);
    };
}
