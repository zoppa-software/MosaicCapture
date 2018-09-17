#pragma once

#include <windows.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Diagnostics;
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;
using namespace System::Threading::Tasks;
using namespace System::Windows::Forms;

namespace Dwm
{
    /// <summary>�J�X�^���`��{�^���R���g���[���B</summary>
    public ref class CustomDrawButton
        : Control, IButtonControl
    {
        #pragma region "fields"

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

        #pragma endregion

        #pragma region "fields"

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


       #pragma endregion

    public:
        #pragma region "constructor"

        /// <summary>�R���X�g���N�^�B</summary>
        /// <remarks>
        /// �C���X�^���X�̏��������s���B
        /// </remarks>
        CustomDrawButton()
        {
            // ���\�[�X��ݒ�
            this->enableColor = gcnew SolidBrush(Color::DimGray);
            this->notEnableColor = gcnew SolidBrush(Color::LightGray);
            this->focusColorPen = gcnew Pen(Color::DimGray);
            this->hoverColorPen = gcnew Pen(Color::LightGray, 1);
            this->hoverBackColor = gcnew SolidBrush(Color::FromArgb(128, 255, 255, 255));
            this->hoverFrontColor = gcnew SolidBrush(Color::DimGray);
            this->hover = false;
            this->DialogResult = System::Windows::Forms::DialogResult::None;

            // ������h�~�X�^�C����ݒ�
            this->SetStyle(ControlStyles::DoubleBuffer |
                           ControlStyles::UserPaint |
                           ControlStyles::AllPaintingInWmPaint, true);
        }

        /// <summary>�f�X�g���N�^�B</summary>
        virtual ~CustomDrawButton()
        {
            if (this->enableColor != nullptr) {
                delete this->enableColor;
                this->enableColor = nullptr;
            }
            if (this->notEnableColor != nullptr) {
                delete notEnableColor;
                this->notEnableColor = nullptr;
            }
            if (this->focusColorPen != nullptr) {
                delete this->focusColorPen;
                this->focusColorPen = nullptr;
            }
            if (this->hoverColorPen != nullptr) {
                delete this->hoverColorPen;
                this->hoverColorPen = nullptr;
            }
            if (this->hoverFrontColor != nullptr) {
                delete this->hoverFrontColor;
                this->hoverFrontColor = nullptr;
            }
            if (this->hoverBackColor != nullptr) {
                delete this->hoverBackColor;
                this->hoverBackColor = nullptr;
            }
        }

        #pragma endregion

        #pragma region "methods"

    protected:
        /// <summary>�R���g���[�������������s���B</summary>
        virtual void ButtonClick()
        {
            Control::OnClick(gcnew EventArgs());
        }

    private:
        /// <summary>�����҂��ă{�^���N���b�N�𔭍s�B</summary>
        void SleepMilSecond()
        {
            System::Threading::Thread::Sleep(10);
            this->Invoke(gcnew Action(this, &CustomDrawButton::ButtonClick));
        }

    public:
        /// <summary>�R���g���[���Ƀt�H�[�J�X��^����B</summary>
        void SetFocus()
        {
            if (this->IsHandleCreated) {
                ::SetFocus((HWND)this->Handle.ToPointer());
            }
        }

    protected:
        //---------------------------------------------------------------------
        // �`�揈��
        //---------------------------------------------------------------------
        /// <summary>�w�i�F�`��C�x���g�n���h���B</summary>
        /// <param name="pevent">�C�x���g���s���B</param>
        void OnPaintBackground(PaintEventArgs ^ pevent) override
        {
            Control::OnPaintBackground(pevent);
        }

        void OnSizeChanged(EventArgs ^ e) override
        {
            int a = 50;
            Control::OnSizeChanged(e);
        }

        /// <summary>�`��C�x���g�n���h���B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        /// <remarks>
        /// �摜�A�������̕`����s���B
        /// </remarks>
        void OnPaint(PaintEventArgs ^ e) override
        {
            Control::OnPaint(e);

            Graphics ^ g = e->Graphics;

            // �L���A�����J���[��ݒ�
            SolidBrush ^ brh;
            if (this->Enabled) {
                brh = (this->hover ? this->hoverFrontColor : this->enableColor);
            }
            else {
                brh = this->notEnableColor;
            }
            int lft = (this->ClientRectangle.Width - this->SquareLength) / 2;
            int top = (this->ClientRectangle.Height - this->SquareLength) / 2;

            // �z�o�[���w�i��`�悷��
            if (this->hover) {
                g->FillRectangle(this->hoverBackColor, this->ClientRectangle);
            }

            // �A�C�R����`�悷��
            this->DrawMethod(g, brh, lft, top);

            // �t�H�[�J�X�^�z�o�[�g�̕`����s��
            if (this->Focused || this->hover) {
                Pen ^ frmbrh = (this->Focused ? this->focusColorPen : this->hoverColorPen);
                g->DrawRectangle(frmbrh,
                                 this->ClientRectangle.X,
                                 this->ClientRectangle.Y,
                                 this->ClientRectangle.Width - 1,
                                 this->ClientRectangle.Height - 1);
            }
        }

        /// <summary>�J�X�^���摜�̕`����s���B</summary>
        /// <param name="g">�O���t�B�b�N�I�u�W�F�N�g�B</param>
        /// <param name="brh">�`��u���V�B</param>
        /// <param name="lft">���B</param>
        /// <param name="top">��B</param>
        virtual void DrawMethod(Graphics ^ g, SolidBrush ^ brh, int lft, int top)
        {
            // �����
        }

    public:
        //---------------------------------------------------------------------
        // �C���t������
        //---------------------------------------------------------------------
        /// <summary>�R���g���[���ɁA���ꂪ����̃{�^���ł���A�O�ςƓ��삪��������Ă��邱�Ƃ��ʒm�����B</summary>
        /// <param name="value">�R���g���[��������̃{�^���Ƃ��ē��삷��ꍇ�� true�B����ȊO�̏ꍇ�� false�B</param>
        virtual void NotifyDefault(bool value)
        {
            // �����
        }

        /// <summary>�R���g���[���� Click �C�x���g�𐶐����܂��B</summary>
        virtual void PerformClick()
        {
            // �t�H�[�J�X��ݒ�
            ::SetFocus((HWND)this->Handle.ToPointer());

            if (this->Enabled) {
                this->ButtonClick();
            }
        }

    protected:
        //---------------------------------------------------------------------
        // �t�H�[�J�X�A�L�[�C�x���g
        //---------------------------------------------------------------------
        /// <summary>���X�g�t�H�[�J�X�C�x���g�n���h���B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnLostFocus(EventArgs ^ e) override
        {
            Control::OnLostFocus(e);
            this->Invalidate();
        }

        /// <summary>�t�H�[�J�X�擾�C�x���g�n���h���B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnGotFocus(EventArgs ^ e) override
        {
            Control::OnGotFocus(e);
            this->Invalidate();
        }

        /// <summary>�L�[�����C�x���g�n���h���i�����O�j</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnPreviewKeyDown(PreviewKeyDownEventArgs ^ e) override
        {
            // ����ȃL�[���������邽�߃t���O��ݒ�
            switch (e->KeyCode)
            {
            case Keys::Enter:
                    e->IsInputKey = true;
                    break;

                default:
                    Control::OnPreviewKeyDown(e);
                    break;

            }
        }

        /// <summary>�L�[�_�E���C�x���g�n���h���B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnKeyDown(KeyEventArgs ^ e) override
        {
            Control::OnKeyDown(e);

            switch (e->KeyCode)
            {
            case Keys::Enter:
                this->ButtonClick();
                break;
            }
        }

        //---------------------------------------------------------------------
        // �}�E�X�C�x���g
        //---------------------------------------------------------------------
        /// <summary>�}�E�X�ړ��C�x���g�n���h���B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnMouseMove(MouseEventArgs ^ e) override
        {
            Control::OnMouseMove(e);

            if (this->Enabled) {
                // �O��̃z�o�[��Ԃ��L��
                bool oldf = this->hover;
                this->hover = true;

                // �O��ƍ��񂪈قȂ�Ȃ�΍ĕ`��
                if (oldf != this->hover) {
                    this->Invalidate();
                }
            }
        }

        /// <summary>�}�E�X�_�E���C�x���g�n���h���B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnMouseDown(MouseEventArgs ^ e) override
        {
            Control::OnMouseDown(e);

            if (this->Enabled) {
                // �t�H�[�J�X��ݒ�
                ::SetFocus((HWND)this->Handle.ToPointer());

                // ���N���b�N���摜�̈���Ƀ}�E�X�|�C���^������Ȃ�Ώk���\��
                if (e->Button == System::Windows::Forms::MouseButtons::Left) {
                    this->Invalidate();
                }
            }
        }

        /// <summary>�}�E�X�N���b�N�C�x���g�n���h���B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnMouseClick(MouseEventArgs ^ e) override
        {
            if (this->Enabled) {
                this->Invalidate();
                Task^ res = Task::Run(gcnew Action(this, &CustomDrawButton::SleepMilSecond));
            }
        }

        /// <summary>�}�E�X�A�b�v�C�x���g�n���h���B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnMouseUp(MouseEventArgs ^ e) override
        {
            Control::OnMouseUp(e);
            this->Invalidate();
        }

        /// <summary>�}�E�X���[�u�C�x���g�n���h���B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnMouseLeave(EventArgs ^ e) override
        {
            Control::OnMouseLeave(e);

            // �e�t���O���������čĕ`��
            this->hover = false;
            this->Invalidate();
        }

        /// <summary>�N���b�N�C�x���g�B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnClick(EventArgs ^ e) override
        {
            // �����
        }

        #pragma endregion
    };

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
        void DrawMethod(Graphics ^ g, SolidBrush ^ brh, int lft, int top) override
        {
            g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::None;

            float scale = g->DpiX / 96.0f;
            g->ScaleTransform(scale, scale);

            g->FillRectangle(brh, lft, top + 7, 8, 3);
        }
    };

    ref class MaximumButton
        : CustomDrawButton
    {
    private:
        Form ^ targetForm;

        Pen ^ pen;

    public:
        MaximumButton()
        {
            this->pen = gcnew Pen(Color::Black, 1);
        }

        ~MaximumButton()
        {
            if (this->pen != nullptr) {
                delete this->pen;
                this->pen = nullptr;
            }
        }

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
        void DrawMethod(Graphics ^ g, SolidBrush ^ brh, int lft, int top) override
        {
            g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::None;

            float scale = g->DpiX / 96.0f;
            g->ScaleTransform(scale, scale);

            FormWindowState state = this->targetForm != nullptr ? this->targetForm->WindowState : FormWindowState::Normal;
            this->pen->Color = brh->Color;
            switch (state)
            {
            case FormWindowState::Maximized:
                g->FillRectangle(brh, lft, top + 3, 9, 2);
                g->DrawRectangle(this->pen, lft, top + 5, 8, 5);

                g->FillRectangle(brh, lft + 2, top, 9, 2);
                g->DrawLine(this->pen, lft + 10, top + 2, lft + 10, top + 7);
                break;

            default:
                g->FillRectangle(brh, lft, top, 9, 2);
                g->DrawRectangle(this->pen, lft, top + 2, 8, 6);
                break;
            }
        }

    public:
        void SetParentForm(Form ^ tarForm)
        {
            this->targetForm = tarForm;
        }
    };

    ref class CloseButton
        : CustomDrawButton
    {
    private:
        Pen ^ pen;

    public:
        CloseButton()
        {
            this->pen = gcnew Pen(Color::Black, 2);
        }

        ~CloseButton()
        {
            if (this->pen != nullptr) {
                delete this->pen;
                this->pen = nullptr;
            }
        }

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
        void DrawMethod(Graphics ^ g, SolidBrush ^ brh, int lft, int top) override
        {
            g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

            float scale = g->DpiX / 96.0f;
            g->ScaleTransform(scale, scale);

            System::Drawing::Rectangle rec = this->ClientRectangle;
            this->pen->Color = brh->Color;
            g->DrawLine(this->pen, lft, top, lft + 8, top + 8);
            g->DrawLine(this->pen, lft, top + 8, lft + 8, top);
        }
    };
}

