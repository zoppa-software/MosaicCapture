#include "stdafx.h"
#include "CustomDrawButton.h"

#pragma once

#include <windows.h>

namespace Dwm
{
    /// <summary>コンストラクタ。</summary>
    /// <remarks>
    /// インスタンスの初期化を行う。
    /// </remarks>
    CustomDrawButton::CustomDrawButton()
    {
        // リソースを設定
        this->enableColor = gcnew SolidBrush(Color::DimGray);
        this->notEnableColor = gcnew SolidBrush(Color::LightGray);
        this->focusColorPen = gcnew Pen(Color::DimGray);
        this->hoverColorPen = gcnew Pen(Color::LightGray, 1);
        this->hoverBackColor = gcnew SolidBrush(Color::FromArgb(128, 255, 255, 255));
        this->hoverFrontColor = gcnew SolidBrush(Color::DimGray);
        this->hover = false;
        this->DialogResult = System::Windows::Forms::DialogResult::None;

        // ちらつき防止スタイルを設定
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
    // 描画処理
    //---------------------------------------------------------------------
    void CustomDrawButton::OnPaintBackground(PaintEventArgs ^ pevent)
    {
        Control::OnPaintBackground(pevent);
    }

    void CustomDrawButton::OnPaint(PaintEventArgs ^ e)
    {
        Control::OnPaint(e);

        Graphics ^ g = e->Graphics;

        // 有効、無効カラーを設定
        SolidBrush ^ brh;
        if (this->Enabled) {
            brh = (this->hover ? this->hoverFrontColor : this->enableColor);
        }
        else {
            brh = this->notEnableColor;
        }
        int lft = (this->ClientRectangle.Width - this->SquareLength) / 2;
        int top = (this->ClientRectangle.Height - this->SquareLength) / 2;

        // ホバー時背景を描画する
        if (this->hover) {
            g->FillRectangle(this->hoverBackColor, this->ClientRectangle);
        }

        // アイコンを描画する
        this->DrawMethod(g, brh, lft, top);

        // フォーカス／ホバー枠の描画を行う
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
        // 空実装
    }

    //---------------------------------------------------------------------
    // インフラ処理
    //---------------------------------------------------------------------
    /// <summary>コントロールに、それが既定のボタンであり、外観と動作が調整されていることが通知される。</summary>
    /// <param name="value">コントロールが既定のボタンとして動作する場合は true。それ以外の場合は false。</param>
    void CustomDrawButton::NotifyDefault(bool value)
    {
        // 空実装
    }

    void CustomDrawButton::PerformClick()
    {
        // フォーカスを設定
        ::SetFocus((HWND)this->Handle.ToPointer());

        if (this->Enabled) {
            this->ButtonClick();
        }
    }

    //---------------------------------------------------------------------
    // フォーカス、キーイベント
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
        // 特殊なキーを処理するためフラグを設定
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
    // マウスイベント
    //-------------------------------------------------------------------------
    void CustomDrawButton::OnMouseMove(MouseEventArgs ^ e)
    {
        Control::OnMouseMove(e);

        if (this->Enabled) {
            // 前回のホバー状態を記憶
            bool oldf = this->hover;
            this->hover = true;

            // 前回と今回が異なるならば再描画
            if (oldf != this->hover) {
                this->Invalidate();
            }
        }
    }

    void CustomDrawButton::OnMouseDown(MouseEventArgs ^ e)
    {
        Control::OnMouseDown(e);

        if (this->Enabled) {
            // フォーカスを設定
            ::SetFocus((HWND)this->Handle.ToPointer());

            // 左クリックかつ画像領域内にマウスポインタがあるならば縮小表示
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

        // 各フラグを消去して再描画
        this->hover = false;
        this->Invalidate();
    }

    void CustomDrawButton::OnClick(EventArgs ^ e)
    {
        // 空実装
    }

    void CustomDrawButton::WaitAMomentToButtonClick()
    {
        System::Threading::Thread::Sleep(10);
        this->Invoke(gcnew Action(this, &CustomDrawButton::ButtonClick));
    }

    //-------------------------------------------------------------------------
    // 「最小化」ボタン
    //-------------------------------------------------------------------------
    void MinimumButton::DrawMethod(Graphics ^ g, SolidBrush ^ brh, int lft, int top)
    {
        g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::None;

        // DPI調整
        float scale = g->DpiX / 96.0f;
        g->ScaleTransform(scale, scale);

        // アイコン描画
        g->FillRectangle(brh, lft, top + 7, 8, 3);
    }

    //-------------------------------------------------------------------------
    // 「最大化」ボタン
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

        // DPI調整
        float scale = g->DpiX / 96.0f;
        g->ScaleTransform(scale, scale);

        // ペンの色を設定
        this->pen->Color = brh->Color;

        // ウィンドウ状態を取得する
        FormWindowState state = this->targetForm != nullptr ?
                                this->targetForm->WindowState : FormWindowState::Normal;
        switch (state)
        {
        case FormWindowState::Maximized:
            // 最大化状態描画
            g->FillRectangle(brh, lft, top + 3, 9, 2);
            g->DrawRectangle(this->pen, lft, top + 5, 8, 5);

            g->FillRectangle(brh, lft + 2, top, 9, 2);
            g->DrawLine(this->pen, lft + 10, top + 2, lft + 10, top + 7);
            break;

        default:
            // 通常状態描画
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
    // 「閉じる」ボタン
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

        // DPI調整 
        float scale = g->DpiX / 96.0f;
        g->ScaleTransform(scale, scale);

        // アイコン描画
        System::Drawing::Rectangle rec = this->ClientRectangle;
        this->pen->Color = brh->Color;
        g->DrawLine(this->pen, lft, top, lft + 8, top + 8);
        g->DrawLine(this->pen, lft, top + 8, lft + 8, top);
    }
}
