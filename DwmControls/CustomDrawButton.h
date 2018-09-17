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

    /// <summary>カスタム描画ボタンコントロール。</summary>
    public ref class CustomDrawButton
        : Control, IButtonControl
    {
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

    public:
        /// <summary>コンストラクタ。</summary>
        /// <remarks>
        /// インスタンスの初期化を行う。
        /// </remarks>
        CustomDrawButton();

        /// <summary>デストラクタ。</summary>
        virtual ~CustomDrawButton();

    protected:
        /// <summary>コントロール押下処理を行う。</summary>
        virtual void ButtonClick();

    public:
        /// <summary>コントロールにフォーカスを与える。</summary>
        void SetFocus();

    protected:
        //---------------------------------------------------------------------
        // 描画処理
        //---------------------------------------------------------------------
        /// <summary>背景色描画イベントハンドラ。</summary>
        /// <param name="pevent">イベント発行元。</param>
        void OnPaintBackground(PaintEventArgs ^ pevent) override;

        /// <summary>描画イベントハンドラ。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        /// <remarks>
        /// 画像、説明文の描画を行う。
        /// </remarks>
        void OnPaint(PaintEventArgs ^ e) override;

        /// <summary>カスタム画像の描画を行う。</summary>
        /// <param name="g">グラフィックオブジェクト。</param>
        /// <param name="brh">描画ブラシ。</param>
        /// <param name="lft">左。</param>
        /// <param name="top">上。</param>
        virtual void DrawMethod(Graphics ^ g, SolidBrush ^ brh, int lft, int top);

    public:
        //---------------------------------------------------------------------
        // インフラ処理
        //---------------------------------------------------------------------
        /// <summary>コントロールに、それが既定のボタンであり、外観と動作が調整されていることが通知される。</summary>
        /// <param name="value">コントロールが既定のボタンとして動作する場合は true。それ以外の場合は false。</param>
        virtual void NotifyDefault(bool value);

        /// <summary>コントロールの Click イベントを生成します。</summary>
        virtual void PerformClick();

    protected:
        //---------------------------------------------------------------------
        // フォーカス、キーイベント
        //---------------------------------------------------------------------
        /// <summary>ロストフォーカスイベントハンドラ。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnLostFocus(EventArgs ^ e) override;

        /// <summary>フォーカス取得イベントハンドラ。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnGotFocus(EventArgs ^ e) override;

        /// <summary>キー押下イベントハンドラ（処理前）</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnPreviewKeyDown(PreviewKeyDownEventArgs ^ e) override;

        /// <summary>キーダウンイベントハンドラ。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnKeyDown(KeyEventArgs ^ e) override;

        //---------------------------------------------------------------------
        // マウスイベント
        //---------------------------------------------------------------------
        /// <summary>マウス移動イベントハンドラ。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnMouseMove(MouseEventArgs ^ e) override;

        /// <summary>マウスダウンイベントハンドラ。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnMouseDown(MouseEventArgs ^ e) override;

        /// <summary>マウスクリックイベントハンドラ。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnMouseClick(MouseEventArgs ^ e) override;

        /// <summary>マウスアップイベントハンドラ。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnMouseUp(MouseEventArgs ^ e) override;

        /// <summary>マウスリーブイベントハンドラ。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnMouseLeave(EventArgs ^ e) override;

        /// <summary>クリックイベント。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnClick(EventArgs ^ e) override;

    private:
        /// <summary>少し待ってボタンクリックを発行。</summary>
        void WaitAMomentToButtonClick();
    };

    #pragma region "「最小化」ボタン"

    /// <summary>「最小化」ボタン。</summary>
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
        void DrawMethod(Graphics ^ g, SolidBrush ^ brh, int lft, int top) override;
    };

    #pragma endregion

    #pragma region "「最大化」ボタン"

    /// <summary>「最大化」ボタン。</summary>
    ref class MaximumButton
        : CustomDrawButton
    {
    private:
        // 親ウィンドウ
        Form ^ targetForm;

        // 描画ペン
        Pen ^ pen;

    public:
        /// <summary>コンストラクタ。</summary>
        MaximumButton();

        /// <summary>デストラクタ。</summary>
        ~MaximumButton();

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
        void DrawMethod(Graphics ^ g, SolidBrush ^ brh, int lft, int top) override;

    internal:
        /// <summary>親のウィンドウを保存する。</summary>
        /// <param name="tarForm">親ウィンドウ。</param>
        void SetParentForm(Form ^ tarForm);
    };

    #pragma endregion

    #pragma region "「閉じる」ボタン"

    /// <summary>「閉じる」ボタン。</summary>
    ref class CloseButton
        : CustomDrawButton
    {
    private:
        // 描画ペン
        Pen ^ pen;

    public:
        /// <summary>コンストラクタ。</summary>
        CloseButton();

        /// <summary>デストラクタ。</summary>
        ~CloseButton();

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
        void DrawMethod(Graphics ^ g, SolidBrush ^ brh, int lft, int top) override;
    };

    #pragma endregion
}

