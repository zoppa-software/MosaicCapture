#include "stdafx.h"
#include "CustomDrawButton.h"

#pragma once

#include <windows.h>

namespace Dwm
{
    /// <summary>�R���X�g���N�^�B</summary>
    /// <remarks>
    /// �C���X�^���X�̏��������s���B
    /// </remarks>
    CustomDrawButton::CustomDrawButton()
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

    CustomDrawButton::~CustomDrawButton()
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

    void CustomDrawButton::ButtonClick()
    {
        Control::OnClick(gcnew EventArgs());
    }

    void CustomDrawButton::SetFocus()
    {
        if (this->IsHandleCreated) {
            ::SetFocus((HWND)this->Handle.ToPointer());
        }
    }

    //---------------------------------------------------------------------
    // �`�揈��
    //---------------------------------------------------------------------
    void CustomDrawButton::OnPaintBackground(PaintEventArgs ^ pevent)
    {
        Control::OnPaintBackground(pevent);
    }

    void CustomDrawButton::OnPaint(PaintEventArgs ^ e)
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

    void CustomDrawButton::DrawMethod(Graphics ^ g, SolidBrush ^ brh, int lft, int top)
    {
        // �����
    }

    //---------------------------------------------------------------------
    // �C���t������
    //---------------------------------------------------------------------
    /// <summary>�R���g���[���ɁA���ꂪ����̃{�^���ł���A�O�ςƓ��삪��������Ă��邱�Ƃ��ʒm�����B</summary>
    /// <param name="value">�R���g���[��������̃{�^���Ƃ��ē��삷��ꍇ�� true�B����ȊO�̏ꍇ�� false�B</param>
    void CustomDrawButton::NotifyDefault(bool value)
    {
        // �����
    }

    void CustomDrawButton::PerformClick()
    {
        // �t�H�[�J�X��ݒ�
        ::SetFocus((HWND)this->Handle.ToPointer());

        if (this->Enabled) {
            this->ButtonClick();
        }
    }

    //---------------------------------------------------------------------
    // �t�H�[�J�X�A�L�[�C�x���g
    //---------------------------------------------------------------------
    void CustomDrawButton::OnLostFocus(EventArgs ^ e)
    {
        Control::OnLostFocus(e);
        this->Invalidate();
    }

    void CustomDrawButton::OnGotFocus(EventArgs ^ e)
    {
        Control::OnGotFocus(e);
        this->Invalidate();
    }

    void CustomDrawButton::OnPreviewKeyDown(PreviewKeyDownEventArgs ^ e)
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

    void CustomDrawButton::OnKeyDown(KeyEventArgs ^ e)
    {
        Control::OnKeyDown(e);

        switch (e->KeyCode)
        {
        case Keys::Enter:
            this->ButtonClick();
            break;
        }
    }

    //-------------------------------------------------------------------------
    // �}�E�X�C�x���g
    //-------------------------------------------------------------------------
    void CustomDrawButton::OnMouseMove(MouseEventArgs ^ e)
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

    void CustomDrawButton::OnMouseDown(MouseEventArgs ^ e)
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

    void CustomDrawButton::OnMouseClick(MouseEventArgs ^ e)
    {
        if (this->Enabled) {
            this->Invalidate();
            Task::Run(gcnew Action(this, &CustomDrawButton::WaitAMomentToButtonClick));
        }
    }

    void CustomDrawButton::OnMouseUp(MouseEventArgs ^ e)
    {
        Control::OnMouseUp(e);
        this->Invalidate();
    }

    void CustomDrawButton::OnMouseLeave(EventArgs ^ e)
    {
        Control::OnMouseLeave(e);

        // �e�t���O���������čĕ`��
        this->hover = false;
        this->Invalidate();
    }

    void CustomDrawButton::OnClick(EventArgs ^ e)
    {
        // �����
    }

    void CustomDrawButton::WaitAMomentToButtonClick()
    {
        System::Threading::Thread::Sleep(10);
        this->Invoke(gcnew Action(this, &CustomDrawButton::ButtonClick));
    }

    //-------------------------------------------------------------------------
    // �u�ŏ����v�{�^��
    //-------------------------------------------------------------------------
    void MinimumButton::DrawMethod(Graphics ^ g, SolidBrush ^ brh, int lft, int top)
    {
        g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::None;

        // DPI����
        float scale = g->DpiX / 96.0f;
        g->ScaleTransform(scale, scale);

        // �A�C�R���`��
        g->FillRectangle(brh, lft, top + 7, 8, 3);
    }

    //-------------------------------------------------------------------------
    // �u�ő剻�v�{�^��
    //-------------------------------------------------------------------------
    MaximumButton::MaximumButton()
    {
        this->pen = gcnew Pen(Color::Black, 1);
    }

    MaximumButton::~MaximumButton()
    {
        if (this->pen != nullptr) {
            delete this->pen;
            this->pen = nullptr;
        }
    }

    void MaximumButton::DrawMethod(Graphics ^ g, SolidBrush ^ brh, int lft, int top)
    {
        g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::None;

        // DPI����
        float scale = g->DpiX / 96.0f;
        g->ScaleTransform(scale, scale);

        // �y���̐F��ݒ�
        this->pen->Color = brh->Color;

        // �E�B���h�E��Ԃ��擾����
        FormWindowState state = this->targetForm != nullptr ?
                                this->targetForm->WindowState : FormWindowState::Normal;
        switch (state)
        {
        case FormWindowState::Maximized:
            // �ő剻��ԕ`��
            g->FillRectangle(brh, lft, top + 3, 9, 2);
            g->DrawRectangle(this->pen, lft, top + 5, 8, 5);

            g->FillRectangle(brh, lft + 2, top, 9, 2);
            g->DrawLine(this->pen, lft + 10, top + 2, lft + 10, top + 7);
            break;

        default:
            // �ʏ��ԕ`��
            g->FillRectangle(brh, lft, top, 9, 2);
            g->DrawRectangle(this->pen, lft, top + 2, 8, 6);
            break;
        }
    }

    void MaximumButton::SetParentForm(Form ^ tarForm)
    {
        this->targetForm = tarForm;
    }

    //-------------------------------------------------------------------------
    // �u����v�{�^��
    //-------------------------------------------------------------------------
    CloseButton::CloseButton()
    {
        this->pen = gcnew Pen(Color::Black, 2);
    }

    CloseButton::~CloseButton()
    {
        if (this->pen != nullptr) {
            delete this->pen;
            this->pen = nullptr;
        }
    }

    void CloseButton::DrawMethod(Graphics ^ g, SolidBrush ^ brh, int lft, int top)
    {
        g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

        // DPI���� 
        float scale = g->DpiX / 96.0f;
        g->ScaleTransform(scale, scale);

        // �A�C�R���`��
        System::Drawing::Rectangle rec = this->ClientRectangle;
        this->pen->Color = brh->Color;
        g->DrawLine(this->pen, lft, top, lft + 8, top + 8);
        g->DrawLine(this->pen, lft, top + 8, lft + 8, top);
    }
}
