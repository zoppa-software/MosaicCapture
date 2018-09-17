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

	/// <summary>エアロを有効にしたウィンドウフォーム実装。</summary>
	public ref class DwmForm
        : public System::Windows::Forms::Form
	{
    public:
        /// <summary>枠判定余裕代。</summary>
        static const int BAR_PIXEL = 5;

        /// <summary>操作ボタンサイズ（幅）</summary>
        static const int BTN_WIDTH = 28;

        /// <summary>操作ボタンサイズ（高）</summary>
        static const int BTN_HEIGHT = 24;

    private:
        // 枠の大きさ保持
        int borderLeft, borderRight, borderTop, borderBottom;

        // 各ボタン参照
        Dwm::CloseButton ^ closeBtn;
        Dwm::MaximumButton ^ maximumBtn;
        Dwm::MinimumButton ^ minimumBtn;

        // 枠
        bool managedBorder;

        // 枠操作用にカーソルが変更中ならば真
        bool changedCursor;

        // デザイナ変数
        System::ComponentModel::Container ^components;

        // 直前のウィンドウ表示状態
        FormWindowState prevState;

    public:
        /// <summary>エアロが有効ならば真を返す。</summary>
        property bool DwmIsCompositionEnabled
        {
            bool get() {
                int res;
                HRESULT hr = ::DwmIsCompositionEnabled(&res);
                return (bool)(SUCCEEDED(hr) && res);
            }
        }

    protected:
        /// <summary>ウィンドウの特殊効果を取得する。</summary>
        /// <return>特殊効果。</return>
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
        // コンストラクタ、デストラクタ
        //---------------------------------------------------------------------
	public:
        /// <summary>コンストラクタ。</summary>
        DwmForm();

		/// <summary>デストラクタ。</summary>
        virtual ~DwmForm();

        //---------------------------------------------------------------------
        // イベントハンドラ
        //---------------------------------------------------------------------
    protected:
        /// <summary>コンポーネントの初期化を行う。</summary>
        void InitializeComponent();

        /// <summary>初期表示イベントハンドラ。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        virtual void OnShown(EventArgs ^ e) override;

        /// <summary>サイズ変更イベントハンドラ。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        virtual void OnSizeChanged(EventArgs ^ e) override;

    private:
        /// <summary>ウインドウ制御ボタンの位置を修正する。</summary>
        void AjustControlButtonPosition();

        //---------------------------------------------------------------------
        // ボタン押下
        //---------------------------------------------------------------------
    private:
        /// <summary>「最小化」ボタン押下イベント。</summary>
        /// <param name="sender">イベント発行元。</param>
        /// <param name="e">イベントオブジェクト。</param>
        void minimumBtn_Click(Object ^ sender, EventArgs ^ e);

        /// <summary>「最大化」ボタン押下イベント。</summary>
        /// <param name="sender">イベント発行元。</param>
        /// <param name="e">イベントオブジェクト。</param>
        void maximumBtn_Click(Object ^ sender, EventArgs ^ e);

        /// <summary>「閉じる」ボタン押下イベント。</summary>
        /// <param name="sender">イベント発行元。</param>
        /// <param name="e">イベントオブジェクト。</param>
        void closeBtn_Click(Object ^ sender, EventArgs ^ e);

        //---------------------------------------------------------------------
        // ウィンドウ制御
        //---------------------------------------------------------------------
    protected:
        /// <summary>ウィンドウプロシージャ。</summary>
        /// <param name="m">メッセージ構造体。</param>
        virtual void WndProc(Message% m) override;

        /// <summary>エアロ処理する枠の幅を設定する。</summary>
        /// <param name="leftWidth">左枠幅。</param>
        /// <param name="rightWidth">右枠幅。</param>
        /// <param name="topHeight">上部枠高さ。</param>
        /// <param name="bottomHeight">下部枠高さ。</param>
        void DwmExtendFrameIntoClientArea(int leftWidth, int rightWidth, int topHeight, int bottomHeight);

    private:
        /// <summary>Dwm制御のためのメッセージを処理する。</summary>
        /// <param name="handle">ウィンドウハンドル。</param>
        /// <param name="msg">メッセージ。</param>
        /// <param name="wprm">Wパラメータ。</param>
        /// <param name="lprm">Lパラメータ。</param>
        /// <return>メッセージを処理したら真を返す。</return>
        bool WindProcByDwm(IntPtr handle, int msg, IntPtr wprm, IntPtr lprm);

        /// <summary>ウィンドウヒットテスト。</summary>
        /// <param name="handle">ウィンドウハンドル。</param>
        /// <param name="wprm">Wパラメータ。</param>
        /// <param name="lprm">Lパラメータ。</param>
        /// <return>メッセージを処理したら真を返す。</return>
        LRESULT HitTestNCA(HWND hWnd, WPARAM wParam, LPARAM lParam);

        /// <summary>ウィンドウ制御用にカーソルを変更。</summary>
        /// <param name="posmsg">マウス位置を示すメッセージ。</param>
        void ChangeCursorDwm(LRESULT posmsg);
    };
}
