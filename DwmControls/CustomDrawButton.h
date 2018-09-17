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
    /// <summary>カスタム描画ボタンコントロール。</summary>
    public ref class CustomDrawButton
        : Control, IButtonControl
    {
        #pragma region "fields"

    private:
        /// <summary>有効状態ブラシ。</summary>
        SolidBrush ^ enableColor;

        /// <summary>無効状態ブラシ。</summary>
        SolidBrush ^ notEnableColor;

        /// <summary>ホバー時の前景ブラシ。</summary>
        SolidBrush ^ hoverFrontColor;

        /// <summary>ホバー時の背景ブラシ。</summary>
        SolidBrush ^ hoverBackColor;

        /// <summary>フォーカス色ブラシ。</summary>
        Pen ^ focusColorPen;

        /// <summary>マウスホバー色ペン。</summary>
        Pen ^ hoverColorPen;

        /// <summary>ホバー中フラグ。</summary>
        bool hover;

        /// <summary>ボタン戻り値。</summary>
        System::Windows::Forms::DialogResult dialogResult;

        #pragma endregion

        #pragma region "fields"

    public:
        /// <summary>有効時のボタンの色を設定、取得する。</summary>
        /// <value>Color値。</value>
        [Category("表示")]
        [Description("有効時のボタンの色を設定、取得する")]
        property Color EnableColor
        {
            Color get() {
                return this->enableColor->Color;
            }
            void set(Color value) {
                this->enableColor->Color = value;
            }
        }

        /// <summary>無効時のボタンの色を設定、取得する。</summary>
        /// <value>Color値。</value>
        [Category("表示")]
        [Description("無効時のボタンの色を設定、取得する")]
        property Color NotEnableColor
        {
            Color get() {
                return this->notEnableColor->Color;
            }
            void set(Color value) {
                this->notEnableColor->Color = value;
            }
        }

        /// <summary>マウスホバー枠の色を設定、取得する。</summary>
        /// <value>Color値。</value>
        [Category("表示")]
        [Description("マウスホバー枠の色を設定、取得する")]
        property Color HoverColor
        {
            Color get() {
                return this->hoverColorPen->Color;
            }
            void set(Color value) {
                this->hoverColorPen->Color = value;
            }
        }

        /// <summary>マウスホバー時の前景色を設定、取得する。</summary>
        /// <value>Color値。</value>
        [Category("表示")]
        [Description("マウスホバー時の前景色を設定、取得する")]
        property Color HoverFrontColor
        {
            Color get() {
                return this->hoverFrontColor->Color;
            }
            void set(Color value) {
                this->hoverFrontColor->Color = value;
            }
        }

        /// <summary>マウスホバー時の背景色を設定、取得する。</summary>
        /// <value>Color値。</value>
        [Category("表示")]
        [Description("マウスホバー時の背景色を設定、取得する")]
        property Color HoverBackColor
        {
            Color get() {
                return this->hoverBackColor->Color;
            }
            void set(Color value) {
                this->hoverBackColor->Color = value;
            }
        }

        /// <summary>マウスフォーカス枠の色を設定、取得する。</summary>
        /// <value>Color値。</value>
        [Category("表示")]
        [Description("マウスフォーカス枠の色を設定、取得する")]
        property Color FocusColor
        {
            Color get() {
                return this->focusColorPen->Color;
            }
            void set(Color value) {
                this->focusColorPen->Color = value;
            }
        }

        /// <summary>ボタンがクリックされたときに親フォームに返される値を取得または設定します。</summary>
        /// <value>DialogResult。</value>
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

        /// <summary>アイコンの大きさを取得する。</summary>
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

        /// <summary>コンストラクタ。</summary>
        /// <remarks>
        /// インスタンスの初期化を行う。
        /// </remarks>
        CustomDrawButton()
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

        /// <summary>デストラクタ。</summary>
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
        /// <summary>コントロール押下処理を行う。</summary>
        virtual void ButtonClick()
        {
            Control::OnClick(gcnew EventArgs());
        }

    private:
        /// <summary>少し待ってボタンクリックを発行。</summary>
        void SleepMilSecond()
        {
            System::Threading::Thread::Sleep(10);
            this->Invoke(gcnew Action(this, &CustomDrawButton::ButtonClick));
        }

    public:
        /// <summary>コントロールにフォーカスを与える。</summary>
        void SetFocus()
        {
            if (this->IsHandleCreated) {
                ::SetFocus((HWND)this->Handle.ToPointer());
            }
        }

    protected:
        //---------------------------------------------------------------------
        // 描画処理
        //---------------------------------------------------------------------
        /// <summary>背景色描画イベントハンドラ。</summary>
        /// <param name="pevent">イベント発行元。</param>
        void OnPaintBackground(PaintEventArgs ^ pevent) override
        {
            Control::OnPaintBackground(pevent);
        }

        void OnSizeChanged(EventArgs ^ e) override
        {
            int a = 50;
            Control::OnSizeChanged(e);
        }

        /// <summary>描画イベントハンドラ。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        /// <remarks>
        /// 画像、説明文の描画を行う。
        /// </remarks>
        void OnPaint(PaintEventArgs ^ e) override
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

        /// <summary>カスタム画像の描画を行う。</summary>
        /// <param name="g">グラフィックオブジェクト。</param>
        /// <param name="brh">描画ブラシ。</param>
        /// <param name="lft">左。</param>
        /// <param name="top">上。</param>
        virtual void DrawMethod(Graphics ^ g, SolidBrush ^ brh, int lft, int top)
        {
            // 空実装
        }

    public:
        //---------------------------------------------------------------------
        // インフラ処理
        //---------------------------------------------------------------------
        /// <summary>コントロールに、それが既定のボタンであり、外観と動作が調整されていることが通知される。</summary>
        /// <param name="value">コントロールが既定のボタンとして動作する場合は true。それ以外の場合は false。</param>
        virtual void NotifyDefault(bool value)
        {
            // 空実装
        }

        /// <summary>コントロールの Click イベントを生成します。</summary>
        virtual void PerformClick()
        {
            // フォーカスを設定
            ::SetFocus((HWND)this->Handle.ToPointer());

            if (this->Enabled) {
                this->ButtonClick();
            }
        }

    protected:
        //---------------------------------------------------------------------
        // フォーカス、キーイベント
        //---------------------------------------------------------------------
        /// <summary>ロストフォーカスイベントハンドラ。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnLostFocus(EventArgs ^ e) override
        {
            Control::OnLostFocus(e);
            this->Invalidate();
        }

        /// <summary>フォーカス取得イベントハンドラ。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnGotFocus(EventArgs ^ e) override
        {
            Control::OnGotFocus(e);
            this->Invalidate();
        }

        /// <summary>キー押下イベントハンドラ（処理前）</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnPreviewKeyDown(PreviewKeyDownEventArgs ^ e) override
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

        /// <summary>キーダウンイベントハンドラ。</summary>
        /// <param name="e">イベントオブジェクト。</param>
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
        // マウスイベント
        //---------------------------------------------------------------------
        /// <summary>マウス移動イベントハンドラ。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnMouseMove(MouseEventArgs ^ e) override
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

        /// <summary>マウスダウンイベントハンドラ。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnMouseDown(MouseEventArgs ^ e) override
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

        /// <summary>マウスクリックイベントハンドラ。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnMouseClick(MouseEventArgs ^ e) override
        {
            if (this->Enabled) {
                this->Invalidate();
                Task^ res = Task::Run(gcnew Action(this, &CustomDrawButton::SleepMilSecond));
            }
        }

        /// <summary>マウスアップイベントハンドラ。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnMouseUp(MouseEventArgs ^ e) override
        {
            Control::OnMouseUp(e);
            this->Invalidate();
        }

        /// <summary>マウスリーブイベントハンドラ。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnMouseLeave(EventArgs ^ e) override
        {
            Control::OnMouseLeave(e);

            // 各フラグを消去して再描画
            this->hover = false;
            this->Invalidate();
        }

        /// <summary>クリックイベント。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnClick(EventArgs ^ e) override
        {
            // 空実装
        }

        #pragma endregion
    };

    ref class MinimumButton
        : CustomDrawButton
    {
    public:
         /// <summary>アイコンの大きさを取得する。</summary>
        [Browsable(false)]
        property int SquareLength 
        {
            int get() override {
                return 9;
            }
        }

    protected:
        /// <summary>カスタム画像の描画を行う。</summary>
        /// <param name="g">グラフィックオブジェクト。</param>
        /// <param name="brh">描画ブラシ。</param>
        /// <param name="lft">左。</param>
        /// <param name="top">上。</param>
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
         /// <summary>アイコンの大きさを取得する。</summary>
        [Browsable(false)]
        property int SquareLength 
        {
            int get() override {
                return 10;
            }
        }

    protected:
        /// <summary>カスタム画像の描画を行う。</summary>
        /// <param name="g">グラフィックオブジェクト。</param>
        /// <param name="brh">描画ブラシ。</param>
        /// <param name="lft">左。</param>
        /// <param name="top">上。</param>
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
         /// <summary>アイコンの大きさを取得する。</summary>
        [Browsable(false)]
        property int SquareLength 
        {
            int get() override {
                return 9;
            }
        }

    protected:
        /// <summary>カスタム画像の描画を行う。</summary>
        /// <param name="g">グラフィックオブジェクト。</param>
        /// <param name="brh">描画ブラシ。</param>
        /// <param name="lft">左。</param>
        /// <param name="top">上。</param>
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

