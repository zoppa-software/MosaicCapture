#pragma once

#include <windows.h>

namespace Dwm
{
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Diagnostics;
    using namespace System::Drawing;
    using namespace System::Runtime::InteropServices;
    using namespace System::Threading::Tasks;
    using namespace System::Windows::Forms;

    /// <summary>�J�X�^���`��{�^���R���g���[���B</summary>
    public ref class CustomDrawButton
        : Control, IButtonControl
    {
    private:
        /// <summary>�L����ԃu���V�B</summary>
        SolidBrush ^ enableColor;

        /// <summary>������ԃu���V�B</summary>
        SolidBrush ^ notEnableColor;

        /// <summary>�z�o�[���̑O�i�u���V�B</summary>
        SolidBrush ^ hoverFrontColor;

        /// <summary>�z�o�[���̔w�i�u���V�B</summary>
        SolidBrush ^ hoverBackColor;

        /// <summary>�t�H�[�J�X�F�u���V�B</summary>
        Pen ^ focusColorPen;

        /// <summary>�}�E�X�z�o�[�F�y���B</summary>
        Pen ^ hoverColorPen;

        /// <summary>�z�o�[���t���O�B</summary>
        bool hover;

        /// <summary>�{�^���߂�l�B</summary>
        System::Windows::Forms::DialogResult dialogResult;

    public:
        /// <summary>�L�����̃{�^���̐F��ݒ�A�擾����B</summary>
        /// <value>Color�l�B</value>
        [Category("�\��")]
        [Description("�L�����̃{�^���̐F��ݒ�A�擾����")]
        property Color EnableColor
        {
            Color get() {
                return this->enableColor->Color;
            }
            void set(Color value) {
                this->enableColor->Color = value;
            }
        }

        /// <summary>�������̃{�^���̐F��ݒ�A�擾����B</summary>
        /// <value>Color�l�B</value>
        [Category("�\��")]
        [Description("�������̃{�^���̐F��ݒ�A�擾����")]
        property Color NotEnableColor
        {
            Color get() {
                return this->notEnableColor->Color;
            }
            void set(Color value) {
                this->notEnableColor->Color = value;
            }
        }

        /// <summary>�}�E�X�z�o�[�g�̐F��ݒ�A�擾����B</summary>
        /// <value>Color�l�B</value>
        [Category("�\��")]
        [Description("�}�E�X�z�o�[�g�̐F��ݒ�A�擾����")]
        property Color HoverColor
        {
            Color get() {
                return this->hoverColorPen->Color;
            }
            void set(Color value) {
                this->hoverColorPen->Color = value;
            }
        }

        /// <summary>�}�E�X�z�o�[���̑O�i�F��ݒ�A�擾����B</summary>
        /// <value>Color�l�B</value>
        [Category("�\��")]
        [Description("�}�E�X�z�o�[���̑O�i�F��ݒ�A�擾����")]
        property Color HoverFrontColor
        {
            Color get() {
                return this->hoverFrontColor->Color;
            }
            void set(Color value) {
                this->hoverFrontColor->Color = value;
            }
        }

        /// <summary>�}�E�X�z�o�[���̔w�i�F��ݒ�A�擾����B</summary>
        /// <value>Color�l�B</value>
        [Category("�\��")]
        [Description("�}�E�X�z�o�[���̔w�i�F��ݒ�A�擾����")]
        property Color HoverBackColor
        {
            Color get() {
                return this->hoverBackColor->Color;
            }
            void set(Color value) {
                this->hoverBackColor->Color = value;
            }
        }

        /// <summary>�}�E�X�t�H�[�J�X�g�̐F��ݒ�A�擾����B</summary>
        /// <value>Color�l�B</value>
        [Category("�\��")]
        [Description("�}�E�X�t�H�[�J�X�g�̐F��ݒ�A�擾����")]
        property Color FocusColor
        {
            Color get() {
                return this->focusColorPen->Color;
            }
            void set(Color value) {
                this->focusColorPen->Color = value;
            }
        }

        /// <summary>�{�^�����N���b�N���ꂽ�Ƃ��ɐe�t�H�[���ɕԂ����l���擾�܂��͐ݒ肵�܂��B</summary>
        /// <value>DialogResult�B</value>
        [Browsable(false)]
        virtual property System::Windows::Forms::DialogResult DialogResult
        {
            System::Windows::Forms::DialogResult get() {
                return this->dialogResult;
            }
            void set(System::Windows::Forms::DialogResult value) {
                this->dialogResult = value;
            }
        }

        /// <summary>�A�C�R���̑傫�����擾����B</summary>
        [Browsable(false)]
        virtual property int SquareLength
        {
            int get() {
                return 15;
            }
        }

    public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <remarks>
        /// �C���X�^���X�̏��������s���B
        /// </remarks>
        CustomDrawButton();

        /// <summary>�f�X�g���N�^�B</summary>
        virtual ~CustomDrawButton();

    protected:
        /// <summary>�R���g���[�������������s���B</summary>
        virtual void ButtonClick();

    public:
        /// <summary>�R���g���[���Ƀt�H�[�J�X��^����B</summary>
        void SetFocus();

    protected:
        //---------------------------------------------------------------------
        // �`�揈��
        //---------------------------------------------------------------------
        /// <summary>�w�i�F�`��C�x���g�n���h���B</summary>
        /// <param name="pevent">�C�x���g���s���B</param>
        void OnPaintBackground(PaintEventArgs ^ pevent) override;

        /// <summary>�`��C�x���g�n���h���B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        /// <remarks>
        /// �摜�A�������̕`����s���B
        /// </remarks>
        void OnPaint(PaintEventArgs ^ e) override;

        /// <summary>�J�X�^���摜�̕`����s���B</summary>
        /// <param name="g">�O���t�B�b�N�I�u�W�F�N�g�B</param>
        /// <param name="brh">�`��u���V�B</param>
        /// <param name="lft">���B</param>
        /// <param name="top">��B</param>
        virtual void DrawMethod(Graphics ^ g, SolidBrush ^ brh, int lft, int top);

    public:
        //---------------------------------------------------------------------
        // �C���t������
        //---------------------------------------------------------------------
        /// <summary>�R���g���[���ɁA���ꂪ����̃{�^���ł���A�O�ςƓ��삪��������Ă��邱�Ƃ��ʒm�����B</summary>
        /// <param name="value">�R���g���[��������̃{�^���Ƃ��ē��삷��ꍇ�� true�B����ȊO�̏ꍇ�� false�B</param>
        virtual void NotifyDefault(bool value);

        /// <summary>�R���g���[���� Click �C�x���g�𐶐����܂��B</summary>
        virtual void PerformClick();

    protected:
        //---------------------------------------------------------------------
        // �t�H�[�J�X�A�L�[�C�x���g
        //---------------------------------------------------------------------
        /// <summary>���X�g�t�H�[�J�X�C�x���g�n���h���B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnLostFocus(EventArgs ^ e) override;

        /// <summary>�t�H�[�J�X�擾�C�x���g�n���h���B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnGotFocus(EventArgs ^ e) override;

        /// <summary>�L�[�����C�x���g�n���h���i�����O�j</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnPreviewKeyDown(PreviewKeyDownEventArgs ^ e) override;

        /// <summary>�L�[�_�E���C�x���g�n���h���B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnKeyDown(KeyEventArgs ^ e) override;

        //---------------------------------------------------------------------
        // �}�E�X�C�x���g
        //---------------------------------------------------------------------
        /// <summary>�}�E�X�ړ��C�x���g�n���h���B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnMouseMove(MouseEventArgs ^ e) override;

        /// <summary>�}�E�X�_�E���C�x���g�n���h���B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnMouseDown(MouseEventArgs ^ e) override;

        /// <summary>�}�E�X�N���b�N�C�x���g�n���h���B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnMouseClick(MouseEventArgs ^ e) override;

        /// <summary>�}�E�X�A�b�v�C�x���g�n���h���B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnMouseUp(MouseEventArgs ^ e) override;

        /// <summary>�}�E�X���[�u�C�x���g�n���h���B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnMouseLeave(EventArgs ^ e) override;

        /// <summary>�N���b�N�C�x���g�B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnClick(EventArgs ^ e) override;

    private:
        /// <summary>�����҂��ă{�^���N���b�N�𔭍s�B</summary>
        void WaitAMomentToButtonClick();
    };

    #pragma region "�u�ŏ����v�{�^��"

    /// <summary>�u�ŏ����v�{�^���B</summary>
    ref class MinimumButton
        : CustomDrawButton
    {
    public:
         /// <summary>�A�C�R���̑傫�����擾����B</summary>
        [Browsable(false)]
        property int SquareLength 
        {
            int get() override {
                return 9;
            }
        }

    protected:
        /// <summary>�J�X�^���摜�̕`����s���B</summary>
        /// <param name="g">�O���t�B�b�N�I�u�W�F�N�g�B</param>
        /// <param name="brh">�`��u���V�B</param>
        /// <param name="lft">���B</param>
        /// <param name="top">��B</param>
        void DrawMethod(Graphics ^ g, SolidBrush ^ brh, int lft, int top) override;
    };

    #pragma endregion

    #pragma region "�u�ő剻�v�{�^��"

    /// <summary>�u�ő剻�v�{�^���B</summary>
    ref class MaximumButton
        : CustomDrawButton
    {
    private:
        // �e�E�B���h�E
        Form ^ targetForm;

        // �`��y��
        Pen ^ pen;

    public:
        /// <summary>�R���X�g���N�^�B</summary>
        MaximumButton();

        /// <summary>�f�X�g���N�^�B</summary>
        ~MaximumButton();

    public:
         /// <summary>�A�C�R���̑傫�����擾����B</summary>
        [Browsable(false)]
        property int SquareLength 
        {
            int get() override {
                return 10;
            }
        }

    protected:
        /// <summary>�J�X�^���摜�̕`����s���B</summary>
        /// <param name="g">�O���t�B�b�N�I�u�W�F�N�g�B</param>
        /// <param name="brh">�`��u���V�B</param>
        /// <param name="lft">���B</param>
        /// <param name="top">��B</param>
        void DrawMethod(Graphics ^ g, SolidBrush ^ brh, int lft, int top) override;

    internal:
        /// <summary>�e�̃E�B���h�E��ۑ�����B</summary>
        /// <param name="tarForm">�e�E�B���h�E�B</param>
        void SetParentForm(Form ^ tarForm);
    };

    #pragma endregion

    #pragma region "�u����v�{�^��"

    /// <summary>�u����v�{�^���B</summary>
    ref class CloseButton
        : CustomDrawButton
    {
    private:
        // �`��y��
        Pen ^ pen;

    public:
        /// <summary>�R���X�g���N�^�B</summary>
        CloseButton();

        /// <summary>�f�X�g���N�^�B</summary>
        ~CloseButton();

    public:
         /// <summary>�A�C�R���̑傫�����擾����B</summary>
        [Browsable(false)]
        property int SquareLength 
        {
            int get() override {
                return 9;
            }
        }

    protected:
        /// <summary>�J�X�^���摜�̕`����s���B</summary>
        /// <param name="g">�O���t�B�b�N�I�u�W�F�N�g�B</param>
        /// <param name="brh">�`��u���V�B</param>
        /// <param name="lft">���B</param>
        /// <param name="top">��B</param>
        void DrawMethod(Graphics ^ g, SolidBrush ^ brh, int lft, int top) override;
    };

    #pragma endregion
}

