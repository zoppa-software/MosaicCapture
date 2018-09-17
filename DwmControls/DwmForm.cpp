#include "stdafx.h"
#include "DwmForm.h"

namespace Dwm
{
    //---------------------------------------------------------------------
    // �R���X�g���N�^�A�f�X�g���N�^
    //---------------------------------------------------------------------
    DwmForm::DwmForm()
    {
        // �R���|�[�l���g��������
        this->InitializeComponent();

        // �_�u���o�b�t�@��ݒ�
        this->SetStyle(ControlStyles::DoubleBuffer |
                       ControlStyles::UserPaint |
                       ControlStyles::AllPaintingInWmPaint, true);

        // �G�A���g�̐ݒ�
        this->DwmExtendFrameIntoClientArea(2, 2, 40, 3);
        this->managedBorder = false;

        // �ő剻�{�^���ɐe�t�H�[���Q�Ƃ�ݒ�
        this->maximumBtn->SetParentForm(this);

        // �E�B���h�E�����ʒu��ݒ�
        this->prevState = FormWindowState::Normal;
    }

    DwmForm::~DwmForm()
    {
        if (components) {
            delete components;
        }
    }

    //---------------------------------------------------------------------
    // �C�x���g�n���h��
    //---------------------------------------------------------------------
    void DwmForm::InitializeComponent()
    {
        this->closeBtn = (gcnew Dwm::CloseButton());
        this->maximumBtn = (gcnew Dwm::MaximumButton());
        this->minimumBtn = (gcnew Dwm::MinimumButton());
        this->SuspendLayout();
        // 
        // closeBtn
        // 
        this->closeBtn->DialogResult = System::Windows::Forms::DialogResult::None;
        this->closeBtn->EnableColor = System::Drawing::Color::Black;
        this->closeBtn->FocusColor = System::Drawing::Color::Transparent;
        this->closeBtn->HoverBackColor = System::Drawing::Color::Crimson;
        this->closeBtn->HoverFrontColor = System::Drawing::Color::White;
        this->closeBtn->HoverColor = System::Drawing::Color::FromArgb(255, 232, 17, 35);
        this->closeBtn->Location = System::Drawing::Point(651, 2);
        this->closeBtn->Name = L"closeBtn";
        this->closeBtn->NotEnableColor = System::Drawing::Color::LightGray;
        this->closeBtn->Size = System::Drawing::Size(BTN_WIDTH, 32);
        this->closeBtn->TabIndex = 2;
        this->closeBtn->TabStop = false;
        this->closeBtn->Click += gcnew System::EventHandler(this, &DwmForm::closeBtn_Click);
        // 
        // maximumBtn
        // 
        this->maximumBtn->DialogResult = System::Windows::Forms::DialogResult::None;
        this->maximumBtn->EnableColor = System::Drawing::Color::Black;
        this->maximumBtn->FocusColor = System::Drawing::Color::Transparent;
        this->maximumBtn->HoverColor = System::Drawing::Color::LightGray;
        this->maximumBtn->HoverBackColor = System::Drawing::Color::FromArgb(128, 32, 32, 32);
        this->maximumBtn->HoverFrontColor = System::Drawing::Color::Black;
        this->maximumBtn->Location = System::Drawing::Point(617, 2);
        this->maximumBtn->Name = L"maximumBtn";
        this->maximumBtn->NotEnableColor = System::Drawing::Color::LightGray;
        this->maximumBtn->Size = System::Drawing::Size(BTN_WIDTH, 32);
        this->maximumBtn->TabIndex = 1;
        this->maximumBtn->TabStop = false;
        this->maximumBtn->Click += gcnew System::EventHandler(this, &DwmForm::maximumBtn_Click);
        // 
        // minimumBtn
        // 
        this->minimumBtn->DialogResult = System::Windows::Forms::DialogResult::None;
        this->minimumBtn->EnableColor = System::Drawing::Color::Black;
        this->minimumBtn->FocusColor = System::Drawing::Color::Transparent;
        this->minimumBtn->HoverColor = System::Drawing::Color::LightGray;
        this->minimumBtn->HoverBackColor = System::Drawing::Color::FromArgb(128, 32, 32, 32);
        this->minimumBtn->HoverFrontColor = System::Drawing::Color::Black;
        this->minimumBtn->Location = System::Drawing::Point(583, 2);
        this->minimumBtn->Name = L"minimumBtn";
        this->minimumBtn->NotEnableColor = System::Drawing::Color::LightGray;
        this->minimumBtn->Size = System::Drawing::Size(BTN_WIDTH, 32);
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

    void DwmForm::OnShown(EventArgs ^ e)
    {
        Form::OnShown(e);

        // �{�^���T�C�Y���C���i��ʂ̊g��E�k���ݒ肪����ƕ\�����O�܂Ńs�N�Z��������Ȃ��j
        this->closeBtn->Size = System::Drawing::Size(BTN_WIDTH, BTN_HEIGHT);
        this->maximumBtn->Size = System::Drawing::Size(BTN_WIDTH, BTN_HEIGHT);
        this->minimumBtn->Size = System::Drawing::Size(BTN_WIDTH, BTN_HEIGHT);

        // �{�^���ʒu���C��
        this->AjustControlButtonPosition();
    }

    void DwmForm::OnSizeChanged(EventArgs ^ e)
    {
        Control::OnSizeChanged(e);

        // �{�^���ʒu���C��
        this->AjustControlButtonPosition();

        // �E�B���h�E�ʒu�ƃT�C�Y�ŏ�Ԃ�ݒ�
        //
        // 1. �ŏ���ԂɕύX�A���O�̏�Ԃ�ێ�
        // 2. ���O�̏�Ԃɖ߂�
        if (this->Location.X < -10000 ||
            this->Location.Y < -10000) {
            this->prevState = this->WindowState;
            this->WindowState = FormWindowState::Minimized;
        }
        else if (this->WindowState == FormWindowState::Minimized) {
            this->WindowState = this->prevState;
        }
    }

    /// <summary>�E�C���h�E����{�^���̈ʒu���C������B</summary>
    void DwmForm::AjustControlButtonPosition()
    {
        this->minimumBtn->Location = Point(this->Width - BTN_WIDTH * 3, 0);
        this->maximumBtn->Location = Point(this->Width - BTN_WIDTH * 2, 0);
        this->closeBtn->Location = Point(this->Width - BTN_WIDTH, 0);
    }

    //-------------------------------------------------------------------------
    // �{�^����������
    //-------------------------------------------------------------------------
    void DwmForm::minimumBtn_Click(Object^  sender, EventArgs^  e)
    {
        this->WindowState = (this->WindowState != FormWindowState::Minimized ?
                             FormWindowState::Minimized :
                             FormWindowState::Normal);
    }

    void DwmForm::maximumBtn_Click(Object^  sender, EventArgs^  e)
    {
        this->WindowState = (this->WindowState != FormWindowState::Maximized ?
                             FormWindowState::Maximized :
                             FormWindowState::Normal);
    }

    void DwmForm::closeBtn_Click(Object^  sender, EventArgs^  e)
    {
        this->Close();
    }

    //---------------------------------------------------------------------
    // �E�B���h�E����
    //---------------------------------------------------------------------
    void DwmForm::WndProc(Message% m)
    {
        if (!this->WindProcByDwm(this->Handle, m.Msg, m.WParam, m.LParam)) {
            Control::WndProc(m);
        }
    }

    void DwmForm::DwmExtendFrameIntoClientArea(int leftWidth, int rightWidth, int topHeight, int bottomHeight)
    {
        if (this->DwmIsCompositionEnabled) {
            // �g�̑�����ێ�����
            this->borderLeft = leftWidth;
            this->borderRight = rightWidth;
            this->borderTop = topHeight;
            this->borderBottom = bottomHeight;

            // �G�A���g��ݒ�
            MARGINS margin;
            margin.cxLeftWidth = leftWidth;
            margin.cxRightWidth = rightWidth;
            margin.cyTopHeight = topHeight;
            margin.cyBottomHeight = bottomHeight;
            ::DwmExtendFrameIntoClientArea((HWND)this->Handle.ToPointer(), &margin);
        }
    }

    bool DwmForm::WindProcByDwm(IntPtr handle, int msg, IntPtr wprm, IntPtr lprm)
    {
        NCCALCSIZE_PARAMS * pncsp;
        LRESULT res;
        LPMINMAXINFO lpmm;

        switch (msg)
        {
        case WM_NCCALCSIZE:
            // �E�B���h�E�̃N���C�A���g�̈�̃T�C�Y�ƈʒu���v�Z����
            pncsp = reinterpret_cast<NCCALCSIZE_PARAMS*>(lprm.ToPointer());
            pncsp->rgrc[0].left = pncsp->rgrc[0].left;
            pncsp->rgrc[0].top = pncsp->rgrc[0].top;
            pncsp->rgrc[0].right = pncsp->rgrc[0].right;
            pncsp->rgrc[0].bottom = pncsp->rgrc[0].bottom;
            return false;

        case WM_NCHITTEST:
            res = HitTestNCA((HWND)handle.ToPointer(),
                             (WPARAM)wprm.ToPointer(),
                             (LPARAM)lprm.ToPointer());

            // �J�[�\����ύX
            this->ChangeCursorDwm(res);

            if (res != HTNOWHERE) {
                if (GetAsyncKeyState(VK_LBUTTON) < 0 &&
                    (!this->managedBorder || res == HTCAPTION)) {
                    //�L���v�V���������Ȃ�Έړ����邽�߁A�^�C�g���������b�Z�[�W�����z�I�ɔ��s
                    ::ReleaseCapture();
                    ::SendMessage((HWND)handle.ToPointer(), WM_NCLBUTTONDOWN, res, 0);
                    this->managedBorder = true;
                    return true;
                }
                else if (this->managedBorder &&
                         GetAsyncKeyState(VK_LBUTTON) >= 0) {
                    // �{�[�_�[���쒆�Ń}�E�X�����[�X���ꂽ��t���O�����
                    this->managedBorder = false;
                }
            }
            return false;

        case WM_SETCURSOR:
            // �J�[�\���ύX���b�Z�[�W
            if (this->changedCursor) {
                this->changedCursor = false;
                return true;
            }
            else {
                return false;
            }

        case WM_GETMINMAXINFO:
            // �E�B���h�E�ŏ��T�C�Y���b�Z�[�W
            lpmm = (LPMINMAXINFO)lprm.ToPointer();
            lpmm->ptMinTrackSize.x = this->MinimumSize.Width;
            lpmm->ptMinTrackSize.y = this->MinimumSize.Height;;
            return true;

        default:
            // �����ΏۊO���b�Z�[�W
            return false;
        }
    }

    LRESULT DwmForm::HitTestNCA(HWND hWnd, WPARAM wParam, LPARAM lParam)
    {
        // �J�[�\�����W���擾
        POINT ptMouse = { 
            GET_X_LPARAM(lParam),
            GET_Y_LPARAM(lParam)
        };

        // �E�B���h�E�̋�`���擾
        RECT rcWindow;
        ::GetWindowRect(hWnd, &rcWindow);

        // �q�b�g�e�X�g���T�C�Y�ύX�p�ł��邩�ǂ����𔻒f���܂�
        USHORT uRow = 1, uCol = 1;
        bool fOnResizeBorder = false;

        // �c�̃p�[�e�B�V�����ʒu�����肷��
        if (ptMouse.y >= rcWindow.top &&
            ptMouse.y < rcWindow.top + this->borderTop) {
            fOnResizeBorder = (ptMouse.y < rcWindow.top + BAR_PIXEL);
            uRow = 0;
        }
        else if (ptMouse.y < rcWindow.bottom &&
                 ptMouse.y >= rcWindow.bottom - BAR_PIXEL) {
            uRow = 2;
        }

        // ���̃p�[�e�B�V�����ʒu�����肷��
        if (ptMouse.x >= rcWindow.left &&
            ptMouse.x < rcWindow.left + BAR_PIXEL) {
            uCol = 0;
        }
        else if (ptMouse.x < rcWindow.right &&
                 ptMouse.x >= rcWindow.right - BAR_PIXEL) {
            uCol = 2;
        }

        // �q�b�g�e�X�g�̖߂�l
        LRESULT hitTests[3][3] =
        {
            { HTTOPLEFT,
              (fOnResizeBorder ? HTTOP : HTCAPTION),
              HTTOPRIGHT },
            { HTLEFT,
              HTNOWHERE,
              HTRIGHT },
            { HTBOTTOMLEFT,
              HTBOTTOM,
              HTBOTTOMRIGHT },
        };
        return hitTests[uRow][uCol];
    }

    void DwmForm::ChangeCursorDwm(LRESULT posmsg)
    {
        switch (posmsg)
        {
        case HTTOPLEFT:
        case HTBOTTOMRIGHT:
            this->changedCursor = true;
            ::SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
            break;

        case HTTOP:
        case HTBOTTOM:
            this->changedCursor = true;
            ::SetCursor(LoadCursor(NULL, IDC_SIZENS));
            break;

        case HTCAPTION:
            this->changedCursor = true;
            ::SetCursor(LoadCursor(NULL, IDC_ARROW));
            break;

        case HTTOPRIGHT:
        case HTBOTTOMLEFT:
            this->changedCursor = true;
            ::SetCursor(LoadCursor(NULL, IDC_SIZENESW));
            break;

        case HTLEFT:
        case HTRIGHT:
            this->changedCursor = true;
            ::SetCursor(LoadCursor(NULL, IDC_SIZEWE));
            break;

        default:
            break;
        }
    }
}