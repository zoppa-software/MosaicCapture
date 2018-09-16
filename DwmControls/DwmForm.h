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

	/// <summary>
	/// DwmForm の概要
	/// </summary>
	public ref class DwmForm
        : public System::Windows::Forms::Form
	{
    public:
        static const int BAR_PIXEL = 5;
    private: Dwm::CloseButton^  closeBtn;
    private: Dwm::MaximumButton^  maximumBtn;
    private: Dwm::MinimumButton^  minimumBtn;

    public:

    public:

    private:
        bool managedBorder;

    public:
        /// <summary>描画処理イベントデリゲート。</summary>
        /// <param name="sender">イベント発行元。</param>
        /// <param name="e">イベントオブジェクト。</param>
        bool DwmIsCompositionEnabled()
        {
            int res;
            HRESULT hr = ::DwmIsCompositionEnabled(&res);
            return (bool)(SUCCEEDED(hr) && res);
        }

    private:
        void DwmExtendFrameIntoClientArea(IntPtr handle, int leftWidth, int rightWidth, int topHeight, int bottomHeight)
        {
            MARGINS margin;
            margin.cxLeftWidth = leftWidth;
            margin.cxRightWidth = rightWidth;
            margin.cyTopHeight = topHeight;
            margin.cyBottomHeight = bottomHeight;

            ::DwmExtendFrameIntoClientArea((HWND)handle.ToPointer(), &margin);
        }

    protected:
        property System::Windows::Forms::CreateParams ^ CreateParams
        {
            System::Windows::Forms::CreateParams ^ get() override
            {
                System::Windows::Forms::CreateParams ^ cp = Control::CreateParams;
                cp->ClassStyle |= CS_DROPSHADOW;
                return cp;
            }
        }

	public:
		DwmForm(void)
		{
			InitializeComponent();

            this->SetStyle(ControlStyles::DoubleBuffer |
                ControlStyles::UserPaint |
                ControlStyles::AllPaintingInWmPaint, true);

            if (this->DwmIsCompositionEnabled()) {
                this->DwmExtendFrameIntoClientArea(this->Handle, 3, 3, 65, 40);
            }
            this->managedBorder = false;

            this->maximumBtn->SetParentForm(this);
            //this->preState = FormWindowState::Normal;
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~DwmForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
            this->closeBtn = (gcnew Dwm::CloseButton());
            this->maximumBtn = (gcnew Dwm::MaximumButton());
            this->minimumBtn = (gcnew Dwm::MinimumButton());
            this->SuspendLayout();
            // 
            // closeBtn
            // 
            this->closeBtn->DialogResult = System::Windows::Forms::DialogResult::None;
            this->closeBtn->EnableColor = System::Drawing::Color::DimGray;
            this->closeBtn->FocusColor = System::Drawing::Color::WhiteSmoke;
            this->closeBtn->HoverColor = System::Drawing::Color::Crimson;
            this->closeBtn->Location = System::Drawing::Point(651, 2);
            this->closeBtn->Name = L"closeBtn";
            this->closeBtn->NotEnableColor = System::Drawing::Color::LightGray;
            this->closeBtn->Size = System::Drawing::Size(28, 28);
            this->closeBtn->TabIndex = 2;
            this->closeBtn->TabStop = false;
            this->closeBtn->Click += gcnew System::EventHandler(this, &DwmForm::closeBtn_Click);
            // 
            // maximumBtn
            // 
            this->maximumBtn->DialogResult = System::Windows::Forms::DialogResult::None;
            this->maximumBtn->EnableColor = System::Drawing::Color::DimGray;
            this->maximumBtn->FocusColor = System::Drawing::Color::WhiteSmoke;
            this->maximumBtn->HoverColor = System::Drawing::Color::LightGray;
            this->maximumBtn->Location = System::Drawing::Point(617, 2);
            this->maximumBtn->Name = L"maximumBtn";
            this->maximumBtn->NotEnableColor = System::Drawing::Color::LightGray;
            this->maximumBtn->Size = System::Drawing::Size(28, 28);
            this->maximumBtn->TabIndex = 1;
            this->maximumBtn->TabStop = false;
            this->maximumBtn->Click += gcnew System::EventHandler(this, &DwmForm::maximumBtn_Click);
            // 
            // minimumBtn
            // 
            this->minimumBtn->DialogResult = System::Windows::Forms::DialogResult::None;
            this->minimumBtn->EnableColor = System::Drawing::Color::DimGray;
            this->minimumBtn->FocusColor = System::Drawing::Color::WhiteSmoke;
            this->minimumBtn->HoverColor = System::Drawing::Color::LightGray;
            this->minimumBtn->Location = System::Drawing::Point(583, 2);
            this->minimumBtn->Name = L"minimumBtn";
            this->minimumBtn->NotEnableColor = System::Drawing::Color::LightGray;
            this->minimumBtn->Size = System::Drawing::Size(28, 28);
            this->minimumBtn->TabIndex = 0;
            this->minimumBtn->TabStop = false;
            this->minimumBtn->Click += gcnew System::EventHandler(this, &DwmForm::minimumBtn_Click);
            // 
            // DwmForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(10, 18);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(681, 527);
            this->Controls->Add(this->minimumBtn);
            this->Controls->Add(this->maximumBtn);
            this->Controls->Add(this->closeBtn);
            this->Name = L"DwmForm";
            this->Text = L"DwmForm";
            this->ResumeLayout(false);

        }
#pragma endregion

    private:
        LRESULT HitTestNCA(HWND hWnd, WPARAM wParam, LPARAM lParam)
        {
            // カーソル座標を取得
            POINT ptMouse = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};

            // ウィンドウの矩形を取得
            RECT rcWindow;
            ::GetWindowRect(hWnd, &rcWindow);

            //// Get the frame rectangle, adjusted for the style without a caption.
            //RECT rcFrame = { 0 };
            //::AdjustWindowRectEx(&rcFrame, WS_OVERLAPPEDWINDOW & ~WS_CAPTION, FALSE, NULL);

            // Determine if the hit test is for resizing. Default middle (1,1).
            USHORT uRow = 1;
            USHORT uCol = 1;
            bool fOnResizeBorder = false;

            // Determine if the point is at the top or bottom of the window.
            if (ptMouse.y >= rcWindow.top && ptMouse.y < rcWindow.top + 40)
            {
                fOnResizeBorder = (ptMouse.y < rcWindow.top + BAR_PIXEL);
                uRow = 0;
            }
            else if (ptMouse.y < rcWindow.bottom && ptMouse.y >= rcWindow.bottom - BAR_PIXEL)
            {
                uRow = 2;
            }

            // Determine if the point is at the left or right of the window.
            if (ptMouse.x >= rcWindow.left && ptMouse.x < rcWindow.left + BAR_PIXEL)
            {
                uCol = 0; // left side
            }
            else if (ptMouse.x < rcWindow.right && ptMouse.x >= rcWindow.right - BAR_PIXEL)
            {
                uCol = 2; // right side
            }

            // Hit test (HTTOPLEFT, ... HTBOTTOMRIGHT)
            LRESULT hitTests[3][3] = 
            {
                { HTTOPLEFT,    fOnResizeBorder ? HTTOP : HTCAPTION,    HTTOPRIGHT },
                { HTLEFT,       HTNOWHERE,     HTRIGHT },
                { HTBOTTOMLEFT, HTBOTTOM, HTBOTTOMRIGHT },
            };

            LRESULT res = hitTests[uRow][uCol];
            switch (res)
            {
            case HTTOPLEFT:
            case HTBOTTOMRIGHT:
                ::SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
                break;

            case HTTOP:
            case HTBOTTOM:
                ::SetCursor(LoadCursor(NULL, IDC_SIZENS));
                break;

            case HTCAPTION:
                ::SetCursor(LoadCursor(NULL, IDC_ARROW));
                break;

            case HTTOPRIGHT:
            case HTBOTTOMLEFT:
                ::SetCursor(LoadCursor(NULL, IDC_SIZENESW));
                break;

            case HTLEFT:
            case HTRIGHT:
                ::SetCursor(LoadCursor(NULL, IDC_SIZEWE));
                break;

            default:
                break;
            }

            return res;
        }

        bool WindProcByDwm(IntPtr handle, int msg, IntPtr wprm, IntPtr lprm)
        {
            if (msg == WM_NCCALCSIZE) {
                NCCALCSIZE_PARAMS *pncsp = reinterpret_cast<NCCALCSIZE_PARAMS*>(lprm.ToPointer());

                pncsp->rgrc[0].left   = pncsp->rgrc[0].left   + 0;
                pncsp->rgrc[0].top    = pncsp->rgrc[0].top    + 0;
                pncsp->rgrc[0].right  = pncsp->rgrc[0].right  - 0;
                pncsp->rgrc[0].bottom = pncsp->rgrc[0].bottom - 0;
                return false;
            }
            else if (msg == WM_NCHITTEST) {
                LRESULT res = HitTestNCA((HWND)handle.ToPointer(), (WPARAM)wprm.ToPointer(), (LPARAM)lprm.ToPointer());

                if (res != HTNOWHERE) {
                    //System::Diagnostics::Debug::WriteLine(L"{0}, {1}", res, DateTime::Now);

                    if (GetAsyncKeyState(VK_LBUTTON) < 0 && (!this->managedBorder || res == HTCAPTION)) {
                        System::Diagnostics::Debug::WriteLine(L"{0}, {1}", res, DateTime::Now);
                        //ReleaseCapture();
                        //タイトルバーでマウスの左ボタンが押されたことにする
                        SendMessage((HWND)handle.ToPointer(), WM_NCLBUTTONDOWN, res, 0);
                        this->managedBorder = true;
                        return true;
                    }
                    else if (this->managedBorder && GetAsyncKeyState(VK_LBUTTON) >= 0) {
                        this->managedBorder = false;
                        return false;
                    }
                    else {
                        return false;
                    }
                }
                else {
                    return false;
                }
            }
            else if (msg == WM_SETCURSOR) {
                return true;
            }
            else {
                return false;
            }
        }

    protected:
        /// <summary>ウィンドウプロシージャ。</summary>
        /// <param name="m">メッセージ構造体。</param>
        virtual void WndProc(Message% m) override
        {
            if (this->WindProcByDwm(this->Handle, m.Msg, m.WParam, m.LParam)) {
            }
            else if (m.Msg == WM_GETMINMAXINFO) {
                LPMINMAXINFO lpmm = (LPMINMAXINFO)m.LParam.ToPointer();
                lpmm->ptMinTrackSize.x = this->MinimumSize.Width;
                lpmm->ptMinTrackSize.y = this->MinimumSize.Height;;
            }
            else {
                Control::WndProc(m);
            }
        }

        virtual void OnShown(EventArgs ^ e) override
        {
            this->minimumBtn->Location = Point(this->Width - 88, 5);
            this->maximumBtn->Location = Point(this->Width - 58, 5);
            this->closeBtn->Location = Point(this->Width - 28, 5);
        }

        FormWindowState prevState;

        virtual void OnSizeChanged(EventArgs ^ e) override
        {
            this->minimumBtn->Location = Point(this->Width - 88, 5);
            this->maximumBtn->Location = Point(this->Width - 58, 5);
            this->closeBtn->Location = Point(this->Width - 28, 5);

            if (this->Location.X < -10000 ||
                this->Location.Y < -10000) {
                this->prevState = this->WindowState;
                this->WindowState = FormWindowState::Minimized;
            }
            else if (this->WindowState == FormWindowState::Minimized) {
                this->WindowState = this->prevState;
            }
        }

    private:
        void closeBtn_Click(Object^  sender, EventArgs^  e)
        {
            this->Close();
        }

        void maximumBtn_Click(Object^  sender, EventArgs^  e)
        {
            if (this->WindowState != FormWindowState::Maximized) {
                this->WindowState = FormWindowState::Maximized;
            }
            else {
                this->WindowState = FormWindowState::Normal;
            }
        }

        void minimumBtn_Click(Object^  sender, EventArgs^  e)
        {
            if (this->WindowState != FormWindowState::Minimized) {
                this->WindowState = FormWindowState::Minimized;
            }
            else {
                this->WindowState = FormWindowState::Normal;
            }
        }
    };
}
