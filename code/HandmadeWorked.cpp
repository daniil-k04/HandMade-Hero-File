#include <windows.h>
#include <stdint.h>  // define unsigned and signed integer 
#include <xinput.h> // Controller loop
#include <dsound.h> // Get library with sounds
#define internal static 
#define local_persist static 
#define global_variable static // define var how static or something else  


// unsigned integers
typedef uint8_t u8;     // 1-byte long unsigned integer
typedef uint16_t u16;   // 2-byte long unsigned integer
typedef uint32_t u32;   // 4-byte long unsigned integer
typedef uint64_t u64;   // 8-byte long unsigned integer
// signed integers
typedef int_fast8_t s8;      // 1-byte long signed integer
typedef int_fast16_t s16;    // 2-byte long signed integer
typedef int_fast32_t s32;    // 4-byte long signed integer
typedef int_fast64_t s64;    // 8-byte long signed integer

typedef s32 b32; // define bool how 1-0 value 


global_variable bool Running; 
global_variable BITMAPINFO BitmapInfo; 
global_variable void *BitmapMemory ; 
global_variable int BitmapWidth;
global_variable int BitmapHeight;
global_variable int BytesPerPixel;


////GAMEPAD////



// Sets for get_state

#define XINPUT_GET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_STATE *pState)// define a function macro
typedef XINPUT_GET_STATE (win_xinput_get_state);
XINPUT_GET_STATE(XInput_Get_State_Stub) // Stub func for exceptions
{
	return (ERROR_DEVICE_NOT_CONNECTED);
}
global_variable win_xinput_get_state *XInputGetState_ = XInput_Get_State_Stub ; // Gamepad Vibration
#define XInputGetState XInputGetState_

//alias caller for defining upper. Maybe delete in future.



//#define Name(param) allow us use one or more params of function. For example  (number * number)


// Sets for set_state
#define XINPUT_SET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_VIBRATION *pVibration)
typedef XINPUT_SET_STATE (win_xinput_set_state); //define a type of function a variable
XINPUT_SET_STATE (XInput_Set_State_Stub) // Stubs functions returns errors about gamepad connection and stop her
{
	return (ERROR_DEVICE_NOT_CONNECTED);
}
global_variable win_xinput_set_state *XInputSetState_ = XInput_Set_State_Stub ; // Gamepad Vibration
#define XInputSetState XInputSetState_




// define all values for XInputGetState how firstly default Error_State

#define DIRECT_SOUND_INPUT(name) DWORD WINAPI name (LPCGUID pcGuidDevice, LPDIRECTSOUND *ppDS, LPUNKNOWN pUnkOuter)
typedef DIRECT_SOUND_INPUT(direct_sound_create)



internal void Win32InitDSound()

{
	// Load Library

		HMODULE DSoundLibrary = LoadLibrary("dsound.dll");
		
	if (DSoundLibrary)
	{
			
		// Create a sound object
		
		direct_sound_create* DirectSoundCreate = (direct_sound_create*) GetProcAddress(DSoundLibrary, "DirectSoundCreate");
		
		IDirectSound* DirectSound; // renaming IDirectSound
		
		
		if (DirectSoundCreate && SUCCEEDED( DirectSoundCreate (0 , &DirectSound , 0))// in second pointer refer to IDirectSound 
		
		{
			// Set cooperative level for bind sound object with window
			
			if (SUCCEEDED(DirectSound->SetCooperativeLevel(Window,DSSCL_PRIORITY))))
			{
				// Create primary buffer to set wave format (holdover of waste time)
				
				DSDUFFERDESC BufferDescription = ;
				
				IDirectSoundBuffer* PrimaryBuffer;
				
				if (SUCCEEDED(DirectSound->CreateSoundBuffer(&BufferDescription,&PrimaryBuffer,0))))
			}
			// Create secondary buffer ,where writing our samples 
		}
	}
}


internal void Win_LoadXInput()// load library take only filename (.dll)

{
	HMODULE XInputLibrary = LoadLibraryA("Xinput1_3.dll");// LoadLibraryA upload the a .dll module for calling necessary function.
	
	// if client cant load specified library, they switch to necessary library.
	if (!XInputLibrary)
	{
		HMODULE XInputLibrary = LoadLibraryA("Xinput1_4.dll");
	}
	if (!XInputLibrary)
	{
		HMODULE XInputLibrary = LoadLibraryA("Xinput9_1_0.dll");
	}
	if (XInputLibrary)
	{
		//casting ProcAddres dont know what type of procedure we need to load , so in begin we need to assign true type for func.
		
		XInputGetState = (win_xinput_get_state *) GetProcAddress(XInputLibrary, "XInputGetState");// GetProcAddress retrivies an addres or value fromm dll function 
			
			// if game cant load or find XInput library or Just went wrong , Game give us a Error and stop working 
			if (!XInputGetState) { XInputGetState = XInput_Get_State_Stub; } // 
			
			
			
		XInputSetState = (win_xinput_set_state *) GetProcAddress(XInputLibrary, "XInputSetState");
			if (!XInputSetState) { XInputSetState = XInput_Set_State_Stub; }
			
			
		else
		{
			// we still dont  have any xinput libraries 
			// assign GetState and SetState default stub
			XInputGetState = XInput_Get_State_Stub;
			XInputSetState = XInput_Set_State_Stub;
		}
	}	
}



internal void RenderWeirdGradient(int Xoffset , int Yoffset)
{
	BytesPerPixel = 4; 
	
	int Pitch = BytesPerPixel * BitmapWidth ;  // amount pixels in one row 
	u8 *Row = (u8 *)BitmapMemory;// Set up control on every byte in row 
//NOTE to CASTING . We can convert one type to anoter 

/*
	int Value = 56523565;       // 32-bit value
	char Byte = (char)Value;    // Take only in the first 8 bits of our value . In this exsample we convert INT to char 
*/


	for 	(int Y = 0;
			Y < BitmapHeight; 
			++Y) // advance pixel +1 until it reach end of row 
			
			{
			//NOTE try to rechange u32 to 16 and 8 Bytes.	
				u32 *Pixel = (u32 *)Row; // Go pixel by pixel
				
				for (int X = 0;
					X < BitmapWidth; // count bytes for Height
					++X)
				{
					
					// Pixel in Memory :B G R X
					/*
					*Pixel = (u8) (X+Xoffset);
					++Pixel; // advance to the next pixel (for 4 bytes)
					
					*Pixel = (u8)(Y+Yoffset);
					++Pixel; 
					
					*Pixel = (u8)Row;
					++Pixel; 
					
					*Pixel = 0;
					++Pixel;  
					*/
					
					
					// inderstand we we need to use u8 instead another integer (16 or 32 )
					u16 Red = (u16)(Y + Yoffset);
					u16 Green = (u16)(X + Xoffset);
					u16 Blue = 0;

					*Pixel++ = Red << 16 | Green << 8 | Blue; // Move Pixel in Memory for get 32 value

					// Blue is nearly, than Red and Green , because we dont need move him. 
					
				}				
			Row += Pitch  ; // move to next row 
			}
	
}



internal void Win32ResizeDIBSection (int Width , int Height)// initilize and Resize the buffer 

{		
		
		// For control dib memory and allocate for New DIBSection , each time create new DIBSection and free previous 
		BitmapInfo = {};
		
		// In BitmapHandle we have 2 param . HandleDib  and CreateDib . CreateDib reference to CreateDIBitmap , CreateDIBPatternBrush ,CreateDIBSection.
		
		//BitmapHeader include in func BitmapInfo 
		BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
		BitmapInfo.bmiHeader.biWidth = BitmapWidth;
		BitmapInfo.bmiHeader.biHeight = -BitmapHeight;// top-down Dib section create Image if BitmapHeight would be NEGATIVE.
		
		BitmapInfo.bmiHeader.biPlanes = 1; // How many bits per pixel we will use. Default 
		BitmapInfo.bmiHeader.biBitCount = 32;
		/*
		For bitmap we use only 3 bytes (1-Red , 2-Blue , 3-Green). 3*8=24 , But Windows used only 8, 16 , 32 etc.
		
		We need 8 extra Bites (4*8=32), then accept 1 additional byte 
		*/
		BitmapInfo.bmiHeader.biCompression = BI_RGB; //What type of compression we want. We need default compr 
		
		
//NOTE in future insert VirtualProtect for priviligies access for data.
if (BitmapMemory) // Same as writing (BitmapMemory != 0) or (BitmapMemory != NULL)
	{
			VirtualFree(BitmapMemory, // take from virtualalloc 
						0, // freead memory for allocating
						MEM_RELEASE);// get rid from packege we provided from VirtualAlloc and get then avaible to Windows.				
	}
	BitmapWidth = Width ; 
	BitmapHeight = Height ;	
	int BytesPerPixel = 4;//Numbers of bytes we need to draw One Pixel 
	int BitmapMemorySize = BytesPerPixel * (Width * Height); //Memory for one Bitmap 
    /*
		Width = amount pixels in each row 
		Height = amount rows in full image
	*/
	// allocate memory for bitmap 
	BitmapMemory = VirtualAlloc(0,// strating adress for allocator
								BitmapMemorySize, // size bytes for Windows drawing
								MEM_RESERVE | MEM_COMMIT, // telling windows actions ,which we want execute 
								PAGE_READWRITE); // it allocates pages of memory at a time and clears them to 0.
								
}
/*
	Incremeating row arithmetic . 
	
	1)Incremeating inside the inner loop . Quickly fly out .
	
	2)Incremeating Row before the inner loop . Skip the first row and fly out. 
	
	3)Incremeating Row inside the loop . Position was never change and it was static
	*/


/*

	int Pitch = BytesPerPixel * Width ;  // amount pixels in one row 
	u8 *Row = (u8 *)BitmapMemory;// Set up control on every byte in row 
	
	for 	(int Y = 0;
			Y < BitmapHeight; 
			++Y) // advance pixel +1 until it reach end of row 
			
			{
			//NOTE try to rechange u32 to 16 and 8 Bytes.	
				u8 *Pixel = (u8 *)Row; // Go pixel by pixel
				
				for (int X = 0;
					X < BitmapWidth; // count bytes for Height
					++X)
				
				{
					// Pixel in Memory :B G R X
					*Pixel = 0 ;
					++Pixel; // advance to the next pixel (for 4 bytes)
					
					*Pixel = 0;
					++Pixel; 
					
					*Pixel = 255;
					++Pixel; 
					
					*Pixel = 0;
					++Pixel;  
				}				
			Row += Pitch  ; // move to next row 
			}	

*/		






internal void Win32UpdateWindow (HDC DeviceContext , RECT *ClientRect)//store the deviceContext for copy pixels from bitmapMemory to Windows 
{
		// Width and Height for WindowRect from ClientRect parameters 
		int WindowWidth = ClientRect->right - ClientRect->left;// -> instead (.) allow us , what changes with values get outside the code 
		int WindowHeight = ClientRect->bottom - ClientRect->top;
	
	
	// PITCH  is a pointer to move from one row of bytes to other (BitmapWidth * BytesPerPixel)
	
	
	// assign and copy colors for Client Rectangle.
	// StretchDIBits is lower , than BitBlt
	StretchDIBits(DeviceContext,  //handle 
                  0, 0, WindowWidth, WindowHeight, // Param ClientRect
                  0, 0, BitmapWidth, BitmapHeight, // Param SourceRect (same ClietRect)
                  BitmapMemory, 
                  &BitmapInfo,  
                  DIB_RGB_COLORS, SRCCOPY); // DIB_RGB_COLORS set default RGB instead Palette. Also that means what kind of buffer we need to is passed 
}

LRESULT CALLBACK Win32MainWindowCallback(HWND Window, 
                   UINT Message,
                   WPARAM WParam,
                   LPARAM LParam)
{
	LRESULT Result = 0 ;
	switch (Message)
	{
		
		
//NOTE Try to convert in switch statement

		// When Key is holding , they create 16 битное значение для этой клавиши
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_KEYDOWN:
		case WM_KEYUP:
		{
			// bit shifting 
			b32 IsDown = ((LParam & (1<<31)) == 0 );
			b32 WasDown = ( (LParam & (1<<30)) !=0);
			u16 VKcode = WParam;
			switch (IsDown != WasDown)
			{
				case (VKcode=='W'):{};break;
		
				case 'S':{};break;
				
				case 'D':{};break;
				
				case 'A':{};break;
			
				case VK_ESCAPE : 
				{
					
					if (IsDown)
					{OutputDebugStringA("IsDown");}
				
					if (WasDown)
					{OutputDebugStringA("WasDown");}
				
				};break;
			
			// When ALT+F4 is Down . Window is close 
				
				
				//
				b32 AltKeyWasDown = ((LParam & (1<<29)));
				
				if ((VKcode == VK_F4) && AltKeyWasDown)
				{Running = false;}
			
				
				else if (VKcode == VK_ESCAPE)
				{
					
				}
			
				else if (VKcode == VK_SPACE)
				{}
			}
		}

		//space work
		case WM_SIZE:
		{
			  RECT ClientRect;
			  GetClientRect(Window, &ClientRect);

			  int Width = ClientRect.right - ClientRect.left;  // 
			  int Height = ClientRect.bottom - ClientRect.top; // 

			  Win32ResizeDIBSection(Width, Height);
		}break;

		case WM_DESTROY:
		{
			Running = false;
		} break;
		
		case WM_CLOSE:
		{
			Running = false;
			
		} break;
		
		case WM_ACTIVATEAPP:
		{
			
		} break;
		
		case WM_PAINT:
		{
			
			PAINTSTRUCT Paint;
			HDC DeviceContext = BeginPaint(Window, &Paint);
				
			
				// Do our painting here
				RECT ClientRect; 
				GetClientRect (Window , &ClientRect ); 

				// pass Win32UpdateWindow in WindowRect 
				Win32UpdateWindow(DeviceContext ,  &ClientRect);
				EndPaint(Window, &Paint);
			
		} break;
		default:
		{
			Result = DefWindowProc(Window, Message, WParam, LParam);
		}break;
	}
	return (Result);// If anycase will use , return var 0
}


int WINAPI // try to rename CALLBACK
	wWinMain	(HINSTANCE Instance,
				HINSTANCE PrevInstance,
				PWSTR pCmdLine, // pointer to strings 
				int nCmdShow)
	{
		Win_LoadXInput(); // gamepad_input
		
		WNDCLASSW WindowClass = {}; 
			WindowClass.style = CS_OWNDC;
			WindowClass.lpfnWndProc = Win32MainWindowCallback;
			WindowClass.hInstance = Instance;
			// WindowClass.hIcon;
			WindowClass.lpszClassName = L"HandmadeHeroWindowClass";
			
		(RegisterClassW(&WindowClass)) ;// is Val is 0 , we continue a project . Another way , we exist
		
		HWND Window = CreateWindowEx(0, WindowClass.lpszClassName, "Hero",
										  WS_OVERLAPPEDWINDOW | WS_VISIBLE,
										  CW_USEDEFAULT, CW_USEDEFAULT,
										  CW_USEDEFAULT, CW_USEDEFAULT,
										  0, 0, Instance, 0);
									  
				  // a for loop which would run forever						  
				if (Window) 
				{	
					Win32ResizeDIBSection(&GlobalBackBuffer,1280,720);
					Win32InitDSound();
					int Xoffset = 0;// values for WeirdGradient 
					int Yoffset = 0;
					Running = true;
					while (Running) 
					{	
						MSG Message;
						while (PeekMessageA(&Message , 0 , 0 , 0, PM_REMOVE))
						{
							if (Message.message == WM_QUIT) // Check each message , if WM_QUIT == breakout.
							{
								Running = false;
							}	
							
							TranslateMessage(&Message);
							DispatchMessageA(&Message);
						}	
						
						
						int X_USER_MAX_COUNT = 0;
						for(DWORD ControllerIndex=0;
							ControllerIndex < X_USER_MAX_COUNT;
							++ControllerIndex)
						{
							XINPUT_STATE ControllerState ;
							if (XInputGetState(ControllerIndex ,// assosiated with user device (how much user will be pluged buttons on controller)
								&ControllerState) == ERROR_SUCCESS ) // value memory input 
							{
									//Casting ControllerState
									XINPUT_GAMEPAD *Pad =&ControllerState.Gamepad; //Controller pluged
									
									bool Start 			= Pad->wButtons & XINPUT_GAMEPAD_START;
									bool Back 			= Pad->wButtons & XINPUT_GAMEPAD_BACK;
									bool Right 			= Pad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
									bool Left 			= Pad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
									bool Up 			= Pad->wButtons & XINPUT_GAMEPAD_DPAD_UP;
									bool Down 			= Pad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
									bool RightShoulder 	= Pad->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
									bool LeftShoulder 	= Pad->wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
									bool A 				= Pad->wButtons & XINPUT_GAMEPAD_A;
									bool B 				= Pad->wButtons & XINPUT_GAMEPAD_B;
									bool X 				= Pad->wButtons & XINPUT_GAMEPAD_X;
									bool Y 				= Pad->wButtons & XINPUT_GAMEPAD_Y;
									
									// plugged inf for left and right stick coordinates.
									s16 StickLX = Pad->sThumbLX;
									s16 StickLY = Pad->sThumbLY;
									s16 StickRX = Pad->sThumbRX;
									s16 StickRY = Pad->sThumbRY;
							}
							else
							{
								// Controller not connected
							}
						}
						
						RenderWeirdGradient(Xoffset , Yoffset);
						++Xoffset; //increment our PerPixel in width.
						
						HDC DeviceContext = GetDC(Window);// take a DC we reserved in our Window
						
						RECT ClientRect;
						
						GetClientRect(Window, &ClientRect);
								
						Win32UpdateWindow(DeviceContext, &ClientRect);

						ReleaseDC(Window, DeviceContext);
					}
				}
	return (0);                        
}
