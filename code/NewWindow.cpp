#include <windows.h>
#include <iostream>
// Window class define a behavior of windows
///




LRESULT CALLBACK WindowProc(HWND Window, //Handle to window
							UINT Message, // define what action is doing independet of value Massage 
							WPARAM wParam, //Additional data of Message 
							LPARAM lParam)
										// From DispatchMassage function they send massage to specific Window Proc
	{		
		// hwnd - handle to window 
		struct StateInfo {};
		
		 
		
		if (Message = WM_CREATE)
		{

			CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);// 
			
			pState = reinterpret_cast<*StateInfo>(pCreate->lpCreateParam)// pstate = перекастованный Pcreate
			
			SetWindowLongPtr(Window, GWLP_USERDATA, (LONG_PTR)pState); // Save StateInfo Pointer to get 
			
		}
		//SetWindowLongPtr set a Pointer to StateInfo for specific own Window
		//GetWindowLongPtr give pointer to SetWindowLongPtr for specific Window
		//GWLP_USERDATA for User data will assosiated with window
		
		LONG_PTR ptr = GetWindowLongPtr(Window,GWLP_USERDATA);

	// При выделении памяти nothrow_t выдаёт пустой указатель NULL, а не вызывает исключения.


		if (pState == NULL) // if proggram is not exist, return NULL
		{
			return (0) ;
		}
		
		
		switch(Message)
		{
			case WM_QUIT:{}break ;
			
			
			case WM_SIZE:
				{
					int width = LOWORD(lParam);//16-bit value for width 
					int height = HIWORD(lParam);// 16-bit macro for height 
				}	break;
				
			case WM_PAINT:
				{
					PAINTSTRUCT ps;
					HDC hdc = BeginPaint(Window , &ps);
					
					FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_HOTLIGHT)); //rcPaint gives coordinates of rectangle to fill
					EndPaint(Window, &ps);// Signal to windows to end rePainted itSelf
					
				}break;
				
				
			case WM_CLOSE:
			{
					if (MessageBoxW(Window , L"Do you really want to close window?", L"Message Window" , MB_OKCANCEL))
					{DestroyWindow(Window)};
			}
			
			
			case WM_DESTROY: // Calling after WM_CLOSE
				PostQuitMessage(0); // put WM_QUIT message in queue
				return(0);		//Exit from massage loop. Include WM_QUIT massage in queue Programm is over
				
			return DefWindowProc(Window, Message, wParam, lParam);// windowproc 
		}
		
	}

int WINAPI wWinMain(HINSTANCE Instance,
					HINSTANCE PrevInstance,
					PWSTR pCmdLine, // pointer to strings 
					int nCmdShow)
{
	WNDCLASSW wc = {} ;
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = Instance ;
		wc.lpszClassName  = L"HeroClass" ;

	RegisterClassW(&wc); // Register WNDCLASS with operating system 



	HWND Window = CreateWindowExW(
		0,//extra Style for Window
		L"HeroClass" , // name WNDCLASS
		L"FIrst Window", // Name for title Bar
		WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		Instance,
		pState
	);
	

		// NOTE TODO Can Window Worked Without Message MSG 

		//Application communicate with Operating system , while send a numeric message to him.

	if (Window == NULL) // If proggram not Exist , he is not launch
	{
		return (0);
	}

	// Show window on screen 
	ShowWindow(Window, nCmdShow); // CmdShow - parameter to maximize or minimaze window 

	MSG msg; // Create message from appilication to O.P. 
	GetMessage(&msg, NULL, 0, 0);

	TranslateMessage(&msg); // Translate Key_Massage (Key_Down ; Key_Up) in char
	DispatchMessage(&msg); 

}