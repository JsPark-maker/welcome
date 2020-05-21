// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                    // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING] = L"sdf";             // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING] = L"MyClass";   // 기본 창 클래스 이름입니다.

//함수의 선언
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
//메시지처리함수
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//아직 모르겠뜸
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(
                    //프로그램의 인스턴스 핸들, 클래스가 메모리에 실제로 구현된 실체를 의미
                    _In_ HINSTANCE hInstance,
                    _In_opt_ HINSTANCE hPrevInstance,
                    _In_ LPWSTR    lpCmdLine,
                    _In_ int       nCmdShow)
{
    //의문사항
    //UNREFERENCED_PARAMETER(hPrevInstance);
    //UNREFERENCED_PARAMETER(lpCmdLine);


    // 전역 문자열을 초기화합니다. 의문사항
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    //LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    //LoadString은 잘 모르겠다 필요없는것같음

    //MyResgisterClass함수는 WNDCLASS구조체의 설정과정과 최종적으로 
    //클래스를 등록하는 RegisterClass함수의 묶음이다 
    MyRegisterClass(hInstance);


    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

//    typedef struct tagMSG {
//        //메시지를 받을 윈도우 핸들이다.
//        HWND        hwnd;
//        //어떤 종류의 메시지인가를 나타낸다. 가장중요한값!
//        UINT        message;
//        //전달된 메시지에 대한 부가적인 정보를
//        //어떤 의미를 가지는가는 메시지별로 다르다
//        WPARAM      wParam;
//        //wParam과 비슷, 부가적인 정보
//        LPARAM      lParam;
//        //메시지가 발생한 시간
//        DWORD       time;
//        //메시지가 발생했을 때의 마우스 위치
//        POINT       pt;
//#ifdef _MAC
//        DWORD       lPrivate;
//#endif
//    } MSG, * PMSG, NEAR* NPMSG, FAR* LPMSG;


    MSG msg;

    //GetMessage함수는 시스템이 유지하는 메시지 큐에서 메시지를 읽어들인다.
    //읽어드린 메시지는 첫번재 인수가 지정하는 MSG구조체에 저장된다
    //GetMessage함수는 PostQuitMessage()함수가 쏴주는 메시지 WM_QUIT을 만나게되면 FALSE가 되어 프로그램이 종료된다.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        //TranslateAccelerator는 일반적으로 메뉴항목에 대한 단축키를 제공하기위해 작성
        if (!TranslateAccelerator(
            msg.hwnd, 
            hAccelTable, 
            &msg))
        {
            //키보드 입력 메시지를 가공하여 프로그램에서 쉽게 쓸 수 있도록해줌
            //윈도우는 키보드의 어떤 키가 눌러졌다거나 떨어졌을때 키보드 메시지를 발생
            //이 함수는 키보드의 눌림(WM_KEYDOWN)과 떨어짐(WM_KEYUP)이 연속적으로 발생할 때 문자가 입력되었다는
            //메시지(WM_CHAR)를 만드는 역할을 함.
            TranslateMessage(&msg);
            //메시지큐에서 꺼낸 메시지를 프로그램의 메시지 처리 함수(WndProc)로 전달한다.
            //이 함수에 의해 메시지가 프로그램으로 전달되며 프로그램에서는 전달된 메시지를 점검하여
            //다음 동작을 결정하게됨
            //결국 이 함수가 WndProc로 전달하는 매개체
            DispatchMessage(&msg);
        }
        //메시지루프에서 하는일은 메시지를 꺼내고, 필요한 경우 약간 형태를 바꾼 후
        //응용프로그램으로 전달하는것 뿐임. 이 과정은 WM_QUIT메시지가 전달될때까지
        //즉 프로그램이 종료될때까지 반복된다.
        //메시지루프의 일은 -> 메시지큐에서 메시지를 꺼내 메시지처리함수로 전달//
    }
    return (int) msg.wParam;
}
//===========================================WinMain의 끝================================================



//  창클래스등록함수
//  클래스의 이름을 만듭니다. | 이 이름을 토대로 정보를 가져와서 창을 만듦
//  ATOM -> WORD -> unsigned short
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    //WNDCLASS구조체의 객체를 만듦
    WNDCLASSEXW wcex;
    //구조체의 사이즈만큼 값을 넣어줌 왜넣는지는 아직 의문
    wcex.cbSize = sizeof(WNDCLASSEX);
    //이 값들의 의미는 수직 or 수평의 크기가 변할 경우 윈도우를 다시 그린다는 뜻
    //가장 많이 사용하는 값이 CS_HREDRAW | CS_VREDRAW ---> 그냥 디폴트로 가져가자
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    //메세지 처리함수를 지정, 기본적으론 WndProc로 정해져있는 편
    //다른걸로 바꾸면 골치아파진다 ---> 그냥 디폴트로 가져가자
    wcex.lpfnWndProc    = WndProc;
    //예약영역을 사용하지 않을경우에는 0 | NULL -> default 
    wcex.cbClsExtra     = NULL;
    wcex.cbWndExtra     = NULL;
    //WinMain의 인수로 전달된 hInstance값을 그대로 대입해주면된다.
    wcex.hInstance      = hInstance;
    //윈도우가 사용할 마우스커서와 최소화되었을경우 출력될 아이콘
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    //첫밴째 인수는 커서를 가지고있는 프로그램의 인스턴스 핸들이되 윈도우즈가 제공하는 디폴트 커서를
    //사용하려면 nullptr로 지정하면 된다. 두번째 인수는 사용하고자 하는 커서의 이름을 지정한다.
    //IDC_ARROW (화살표 모양), IDC_CROSS (십자 모양), IDC_IBEAM (I자 모양), IDC_NO (원안에 빗금쳐진모양), IDC_WAIT (모래시계모양)
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    //윈도우의 배경 색상을 지정
    wcex.hbrBackground = (HBRUSH)(WHITE_BRUSH);
    //메뉴는 프로그램 코드에서 만드는것이 아니라, 리소스 에디터에 의해 별도만듦
    //메뉴를 사용하지않을 경우 NULL삽입
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    //윈도우의 클래스이름 정의, 여기서 지정한 이름은 CreateWindow함수에 전달
    //CreateWindow함수가 특성값을 참조하여 윈도우를 만든다
    //위에서 LoadStringW함수를 통해서 문자배열을 초기화하고 이걸 넣었다 처음에는... 굳이 그렇게 할 필요 ㄴㄴ
    wcex.lpszClassName  = L"MyClass";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    //최종적인 윈도우 클래스를 등록하는 함수이다. 설정이 완료된 WNDCLASS구조체의 주소값을 넘겨주면 등록이 완료
    return RegisterClassExW(&wcex);
}


//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   //인스턴스핸들을 hInst전역변수에 저장
   hInst = hInstance;
   //HWND       -> HANDLE WINDOW
   //HINSTANCE  -> HANDLE INSTANCE
   HWND hWnd = CreateWindowW(
       //생성하고자 하는 윈도우의 클래스를 지정하는 문자열
       //RegisterClass에서 생성한 WNDCLASS에서 지정한 문자열을 넘겨주면된다.
       szWindowClass, 
       //윈도우의 타이틀바에 나타날 문자열이다.
       szTitle,
       //만들고자 하는 윈도우의 형태를 지정하는 인수
       //WS_OVERLAPPEDWINDOW를 지정하면 가장 무난한 형태의 윈도우 설정상태가된다.
       WS_OVERLAPPEDWINDOW,
       //윈도우의 크기와 위치를 지정하며 픽셀단위를 사용
       //CW_USEDEFAULT를 지정하면 알아서 지정해준다.
       CW_USEDEFAULT, 
       //부모 윈도우가 있을 경우 부모 윈도우의 핸들을 지정해준다.
       //부모 윈도우가 없을 경우는 NULL로 지정하면된다.
       NULL,
       //ㅇ
       CW_USEDEFAULT, 
       NULL, 
       nullptr, 
       nullptr, 
       //윈도우를 만드는 주체, 즉 프로그램의 핸들을 지정한다.
       //hInstance를 대입해주면된다.
       hInstance, 
       //CREATESTRUCT라는 구조체의 번지(특수한 목적) 보통 nullptr을 전달
       nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                //윈도우의 이동이나 크기변경 따위의 처리는 직접 해줄 필요없이 DefWindowProc으로 넘겨주기만
                //하면 된다.
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        //이 함수를 호출하면 WM_QUIT메시지를 보낸다.
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

/*메시지 처리 함수란 메시지가 발생할 때 프로그램의 반응을 처리하는 일을 하며
WinMain함수와는 별도로 WndProc이라는 이름으로 존재한다. 윈도우 프로시저라는 뜻이지만 통상
읽을때는 윈드프록이라고 읽는다 WndProc은 WinMain에서 호출하는것이 아니라 윈도우즈에 의해 호출된다
윈메인내의 메시지 루프는 메시지를 메시지 처리함수로 보내주기만 할 뿐이며 윈드프록은 메시지가 입력되면
윈도우즈에 의해 호출되어 메시지를 처리한다. 이렇게 운영체제에 의해 호출되는 응용프로그램내의 함수를
콜백함수라고한다. 윈드프록의 인수는 모두 4개이며 msg구조체의 멤버와 동일하다
hWnd메시지를 받을 윈도우의 핸들이며 imessage는 어떤 종류의 메시지인가 즉 변화가 발생했는가에 대한
정보를 가진다. 아이메시지가 WM_MOVE이면 윈도우의 위치가 변경되었음을 알리고 디스트로이면 윈도우가
파괴되었음을 알리는것이다. wParam, lParam은 message의 메시지에 따른 부가적인 정보를 가진다.
예를 들어 마우스 버튼이 눌러졌다는 WM_LBUTTONDOWN메시지가 입력되었다면 화면의 어디쯤에서 마우스 버튼이
눌러졌는가, 그때의 키보드 상황은 어떠한가에 관한 정보가 추가로 필요하며 WM_CHAR메시지, 즉 키보드로부터
키가 입력되었다는 메시지가 입력되었다면 어떤 키가 입력되었는가에 관한 추가적인 정보가 필요하다.
이러한 추가 정보들이 wParam, lParam으로 전달된다. 실제로 전달되는값은 메시지별로 다르다.
윈드프록의 구조는 대체로 다음과 같은 형태를 가진다. 메시지의 종류에 따라 다중 분기하여 메시지별로 처리진행한다.
MSG1메시지가 전달되면 처리1한 후 리턴하고 MSG2메시지가 전달되면 처리2를 한 후 리턴한다.
제일 끝에 있는 함수는 윈드프록에서 처리하지 않은 나머지 메시지에 관한 처리를 해준다.
여기서 중요한 점은!!!-> 윈드프록은 메시지를 처리했을 경우 반드시 0을 리턴해주어야한다....
DEFWINDOWPROC함수가 메시지를 처리했을 경우 이 함수가 리턴한값을 다시 리턴해주어야한다....*/