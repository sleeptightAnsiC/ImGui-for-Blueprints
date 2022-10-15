// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <ImGui.h>
#include "Misc/Optional.h"
#include "ImGuiBPFL.generated.h"

/* structs */

UENUM(BlueprintType)
enum ImGui_WindowFlags
{
	None                         UMETA(DisplayName = "Null"),
	NoTitleBar                   UMETA(DisplayName = "NoTitleBar"),                  // Disable title-bar
	NoResize                     UMETA(DisplayName = "NoResize"),                    // Disable user resizing with the lower-right grip
	NoMove                       UMETA(DisplayName = "NoMove"),                      // Disable user moving the window
	NoScrollbar                  UMETA(DisplayName = "NoScrollbar"),                 // Disable scrollbars (window can still scroll with mouse or programmatically)
	NoScrollWithMouse            UMETA(DisplayName = "NoScrollWithMouse"),           // Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
	NoCollapse                   UMETA(DisplayName = "NoCollapse"),                  // Disable user collapsing window by double-clicking on it. Also referred to as Window Menu Button (e.g. within a docking node).
	AlwaysAutoResize             UMETA(DisplayName = "AlwaysAutoResize"),            // Resize every window to its content every frame
	NoBackground                 UMETA(DisplayName = "NoBackground"),                // Disable drawing background color (WindowBg, etc.) and outside border. Similar as using SetNextWindowBgAlpha(0.0f).
	NoSavedSettings              UMETA(DisplayName = "NoSavedSettings"),             // Never load/save settings in .ini file
	NoMouseInputs                UMETA(DisplayName = "NoMouseInputs"),               // Disable catching mouse, hovering test with pass through.
	MenuBar                      UMETA(DisplayName = "MenuBar"),                     // Has a menu-bar
	HorizontalScrollbar          UMETA(DisplayName = "HorizontalScrollbar"),         // Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)); prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
	NoFocusOnAppearing           UMETA(DisplayName = "NoFocusOnAppearing"),          // Disable taking focus when transitioning from hidden to visible state
	NoBringToFrontOnFocus        UMETA(DisplayName = "NoBringToFrontOnFocus"),       // Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)
	AlwaysVerticalScrollbar      UMETA(DisplayName = "AlwaysVerticalScrollbar"),     // Always show vertical scrollbar (even if ContentSize.y < Size.y)
	AlwaysHorizontalScrollbar    UMETA(DisplayName = "AlwaysHorizontalScrollbar"),   // Always show horizontal scrollbar (even if ContentSize.x < Size.x)
	AlwaysUseWindowPadding       UMETA(DisplayName = "AlwaysUseWindowPadding"),      // Ensure child windows without border uses style.WindowPadding (ignored by default for non-bordered child windows, because more convenient)
	NoNavInputs                  UMETA(DisplayName = "NoNavInputs"),                 // No gamepad/keyboard navigation within the window
	NoNavFocus                   UMETA(DisplayName = "NoNavFocus"),                  // No focusing toward this window with gamepad/keyboard navigation (e.g. skipped by CTRL+TAB)
	UnsavedDocument              UMETA(DisplayName = "UnsavedDocument"),             // Display a dot next to the title. When used in a tab/docking context, tab is selected when clicking the X + closure is not assumed (will wait for user to stop submitting the tab). Otherwise closure is assumed when pressing the X, so if you keep submitting the tab may reappear at end of tab bar.
	NoNav                        UMETA(DisplayName = "NoNav"),
	NoDecoration                 UMETA(DisplayName = "NoDecoration"),
	NoInputs                     UMETA(DisplayName = "NoInputs")
};

UENUM(BlueprintType)
enum ImGui_WindowConditions
{
	Nothing = ImGuiCond_None				UMETA(DisplayName = "Null"),
	Once = ImGuiCond_Once					UMETA(DisplayName = "Once"),
	Always = ImGuiCond_Always				UMETA(DisplayName = "Always"),
	FirstUseEver = ImGuiCond_FirstUseEver	UMETA(DisplayName = "FirstUseEver"),
	Appearing = ImGuiCond_Appearing			UMETA(DisplayName = "Appearing")
};


UENUM(BlueprintType)
enum ImGui_DragType
{
	Drag_Float		UMETA(DisplayName = "Float"),
	Drag_Int		UMETA(DisplayName = "Int"),
	Drag_Vector2D	UMETA(DisplayName = "Vector 2D"),
	Drag_Vector		UMETA(DisplayName = "Vector"),
	Drag_Vector4	UMETA(DisplayName = "Vector 4"),
	Drag_Rotator	UMETA(DisplayName = "Rotator"),
	Drag_Transform	UMETA(DisplayName = "Transform"),
	Drag_Color		UMETA(DisplayName = "Color")
};

UENUM(BlueprintType)
enum ImGui_InputTextType
{
	InputText_None					UMETA(DisplayName = "NULL"),				//ImGuiInputTextFlags_None
	InputText_CharsDecimal			UMETA(DisplayName = "DecimalChars"),		//ImGuiInputTextFlags_CharsDecimal        // Allow 0123456789.+-*/
	//not-needed																//ImGuiInputTextFlags_CharsHexadecimal    // Allow 0123456789ABCDEFabcdef
	InputText_Uppercases			UMETA(DisplayName = "Uppercases"),			//ImGuiInputTextFlags_CharsUppercase      // Turn a..z into A..Z
	InputText_NoBlanks				UMETA(DisplayName = "NoBlanks"),			//ImGuiInputTextFlags_CharsNoBlank        // Filter out spaces, tabs
	InputText_AutoSelectAll			UMETA(DisplayName = "AutoSelectAll"),		//ImGuiInputTextFlags_AutoSelectAll       // Select entire text when first taking mouse focus
	InputText_EnterReturnsTrue		UMETA(DisplayName = "EnterReturnsTrue"),	//ImGuiInputTextFlags_EnterReturnsTrue    // Return 'true' when Enter is pressed (as opposed to every time the value was modified). Consider looking at the IsItemDeactivatedAfterEdit() function.
	//not-needed																//ImGuiInputTextFlags_CallbackCompletion  // Callback on pressing TAB (for completion handling)
	//not-needed																//ImGuiInputTextFlags_CallbackHistory     // Callback on pressing Up/Down arrows (for history handling)
	//not-needed																//ImGuiInputTextFlags_CallbackAlways      // Callback on each iteration. User code may query cursor position, modify text buffer.
	//not-needed																//ImGuiInputTextFlags_CallbackCharFilter  // Callback on character inputs to replace or discard them. Modify 'EventChar' to replace or discard, or return 1 in callback to discard.
	InputText_AllowTabInput			UMETA(DisplayName = "AllowTabInput"),		//ImGuiInputTextFlags_AllowTabInput       // Pressing TAB input a '\t' character into the text field
	InputText_CtrlEnterForNewLine	UMETA(DisplayName = "CtrlEnterForNewLine"),	//ImGuiInputTextFlags_CtrlEnterForNewLine // In multi-line mode, unfocus with Enter, add new line with Ctrl+Enter (default is opposite: unfocus with Ctrl+Enter, add line with Enter).
	InputText_NoHorizontalScroll	UMETA(DisplayName = "NoHorizontalScroll"),	//ImGuiInputTextFlags_NoHorizontalScroll  // Disable following the cursor horizontally
	//not-needed																//ImGuiInputTextFlags_AlwaysOverwrite     // Overwrite mode
	InputText_ReadOnly				UMETA(DisplayName = "ReadOnly"),			//ImGuiInputTextFlags_ReadOnly            // Read-only mode
	InputText_Password				UMETA(DisplayName = "Password"),			//ImGuiInputTextFlags_Password            // Password mode, display all characters as '*'
	InputText_NoUndoRedo			UMETA(DisplayName = "NoUndoRedo"),			//ImGuiInputTextFlags_NoUndoRedo          // Disable undo/redo. Note that input text owns the text data while active, if you want to provide your own undo/redo stack you need e.g. to call ClearActiveID().
	InputText_CharsScientific		UMETA(DisplayName = "ScientificChars")		//ImGuiInputTextFlags_CharsScientific     // Allow 0123456789.+-*/eE (Scientific notation input)
	//not-needed																//ImGuiInputTextFlags_CallbackResize      // Callback on buffer capacity changes request (beyond 'buf_size' parameter value), allowing the string to grow. Notify when the string wants to be resized (for string types which hold a cache of their Size). You will be provided a new BufSize in the callback and NEED to honor it. (see misc/cpp/imgui_stdlib.h for an example of using this)
	//not-needed																//ImGuiInputTextFlags_CallbackEdit        // Callback on any edit (note that InputText() already returns true on edit, the callback is useful mainly to manipulate the underlying buffer while focus is active)
};

UENUM(BlueprintType)
enum ImGui_DirType
{
	DirType_None = 0				UMETA(DisplayName = "None"),
	DirType_Left = 1				UMETA(DisplayName = "Left"),
	DirType_Right = 2				UMETA(DisplayName = "Right"),
	DirType_Up = 3					UMETA(DisplayName = "Up"),
	DirType_Down = 4				UMETA(DisplayName = "Down")
};



UCLASS()
class IMGUI_API UImGuiBPFL : public UBlueprintFunctionLibrary //, public UK2Node_MacroInstance
{
	GENERATED_BODY()

public:

	//! Placeholders ! / test

	UFUNCTION(BlueprintCallable, Category = "DearImGui|! Placeholders !")
	static void PrintSimpleWindow(FString Name, FString Text, FVector2D ScreenPosition);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|! Placeholders !")
	static void PrintSimpleWatermark(FString Name, FString Text, FVector2D ScreenPosition, bool bPrintTextOnly, float BackgroundAlpha);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|! Placeholders !")
	static void TestFunction();


	/* - Functions for Blueprint Graphs -	*/

// Context creation and access

/* Main	*/

// Demo, Debug, Information		
// Styles

/* Windows */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Windows|! Raw C++ Functions !", meta = (AutoCreateRefTerm = "Properties, bOpen"), BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bOpen") bool BeginMainWindow(FString Name, TSet<TEnumAsByte<ImGui_WindowFlags>> Properties, bool bClosable, UPARAM(ref) bool& bOpen);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Windows|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void EndMainWindow();

/* Child Windows */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Child Windows|! Raw C++ Functions !", meta = (AutoCreateRefTerm = "Properties"), BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bVisible") bool BeginChild(FString HashName, FVector2D Size, bool bBorder, TSet<TEnumAsByte<ImGui_WindowFlags>> Properties);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Child Windows|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void EndChild();

/* Windows Utilities */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Windows Utilities")
	static UPARAM(DisplayName = "bCollapsed") bool IsWindowCollapsed();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Windows Utilities")
	static UPARAM(DisplayName = "bFocused") bool IsWindowFocused();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Windows Utilities")
	static UPARAM(DisplayName = "bHovered") bool IsWindowHovered();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Windows Utilities")
	static UPARAM(DisplayName = "Position") FVector2D GetWindowPosition(bool bRelative = false);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Windows Utilities")
	static UPARAM(DisplayName = "Size") FVector2D GetWindowSize(bool bRelative = false);

/* Window manipulation */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Window manipulation")
	static void SetNextWindowScreenPosition(FVector2D ScreenPosition, ImGui_WindowConditions Condition = Always);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Window manipulation")
	static void SetNextWindowSize(FVector2D Size, ImGui_WindowConditions Condition = Always);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Window manipulation")
	static void SetNextWindowSizeConstraints(FVector2D SizeMin, FVector2D SizeMax);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Window manipulation")
	static void SetNextWindowContentSize(FVector2D Size);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Window manipulation")
	static void SetNextWindowCollapsed(bool bCollapsed, ImGui_WindowConditions Condition = Always);  //Do-poprawy/przemy�lenia - brak Condition

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Window manipulation")
	static void SetNextWindowFocused();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Window manipulation")
	static void SetNextWindowBackgroundAlpha(float BackgroundAlpha);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Window manipulation")
	static void SetWindowFontScale(float Scale = 1);

// Content region
// Windows Scrolling
// Parameters stacks (shared)
// Parameters stacks (current window)
// Style read access

/* Cursor / Layout */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Cursor|Layout")
	static void AddSeparator();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Cursor|Layout")
	static void StayInSameLine();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Cursor|Layout")
	static void AddSpacing();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Cursor|Layout")
	static void AddDummy(FVector2D Size);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Cursor|Layout")
	static void Indent(float ToRight = 0);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Cursor|Layout|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void BeginGroup();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Cursor|Layout|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void EndGroup();

// ID stack/scopes

/* Widgets / Text */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Text")
	static void AddText(FString Text);

/* Widgets / Main */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Main|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bClicked") bool Button(FString Label, FVector2D Size);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Main|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bClicked") bool SmallButton(FString Label);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Main|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bClicked") bool InvisibleButton(FString HashName, FVector2D Size);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Main|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bClicked") bool ArrowButton(FString HashName, ImGui_DirType Direction);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Main|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bChanged") bool Checkbox(FString Label, UPARAM(ref) bool& CheckedBool);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Main|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bClicked") bool RadioButton(FString Label, bool bActive);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Main|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bClicked") bool RadioButtonList(TSet<FString> Labels, UPARAM(ref) int& RadioedIntiger);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Main")
	static void AddProgressBar(float Fraction, FVector2D Size, FString Overlay);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Main")
	static void AddBullet();

/* Widgets / Combo Box */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Combo Box|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bOpen") bool BeginCombo(FString Label, FString Preview);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Combo Box|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void EndCombo();

/* Widgets / Drag Sliders */  

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Drag Sliders|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bChanged") bool AddDragFloatArray(FString Label, UPARAM(ref) TArray<float>& DraggedArrayReference, float DragSpeed = 1.0f, float MinValue = 0.0f, float MaxValue = 0.0f);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Drag Sliders|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bChanged") bool AddDragIntArray(FString Label, UPARAM(ref) TArray<int>& DraggedArrayReference, float DragSpeed = 1.0f, int MinValue = 0, int MaxValue = 0);

/* Widgets / Regular Sliders */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Regular Sliders|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bChanged") bool AddSliderFloatArray(FString Label, UPARAM(ref) TArray<float>& SlidedArrayReference, float MinValue = 0.0f, float MaxValue = 100.0f);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Regular Sliders|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bChanged") bool AddSliderIntArray(FString Label, UPARAM(ref) TArray<int>& SlidedArrayReference, int MinValue = 0, int MaxValue = 100);


/* Widgets / Input with Keyboard */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Input with Keyboard|! Raw C++ Functions !", meta = (AutoCreateRefTerm = "Properties"), BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bCallback") bool InputTextBox(FString Label, FString Hint, UPARAM(ref) FString& InputedString, int MaxCharactersCount, FVector2D BoxSize, TSet<TEnumAsByte<ImGui_InputTextType>> Properties);

// Widgets: Color Editor/Picker (tip: the ColorEdit* functions have a little color square that can be left-clicked to open a picker, and right-clicked to open an option menu.)
/* Widgets / Trees */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Trees|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bOpen") bool TreeNode(FString Label);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Trees|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bOpen") bool CollapsingHeader(FString Label);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Trees|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void SetNextItemOpen(bool bOpen = true, ImGui_WindowConditions Condition = Always);

/* Widgets / Selectables */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Selectables|! Raw C++ Functions !", meta = (AutoCreateRefTerm = "bSelected"), BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bClicked") bool Selectable(FString Label, UPARAM(ref) bool& bSelected, FVector2D Size);

/* Widgets / List Boxes	*/

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|List Boxes|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bOpen") bool BeginListBox(FString Label, FVector2D Size);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|List Boxes|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void EndListBox();

// Widgets: Data Plotting
// Widgets: Value() Helpers.

/* Widgets / Menus */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Menus|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bOpen") bool BeginMenuBar();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Menus|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void EndMenuBar();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Menus|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bOpen") bool BeginMainMenuBar();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Menus|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void EndMainMenuBar();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Menus|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bOpen") bool BeginMenu(FString Label, bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Menus|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void EndMenu();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Widgets|Menus|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bActivated") bool MenuItem(FString Label, FString Shortcut, UPARAM(ref) bool& bSelected, bool bEnabled);

/* Tooltips	*/

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Tooltips|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void BeginTooltip();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Tooltips|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void EndTooltip();

/* Popups / begin/end functions */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Popups|! Raw C++ Functions !", meta = (AutoCreateRefTerm = "Properties"), BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bOpen") bool BeginPopup(FString HashName, TSet<TEnumAsByte<ImGui_WindowFlags>> Properties);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Popups|! Raw C++ Functions !", meta = (AutoCreateRefTerm = "bOpenModal, Properties"), BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bOpen") bool BeginPopupModal(FString Name, bool bClosable, UPARAM(ref) bool& bOpenModal, TSet<TEnumAsByte<ImGui_WindowFlags>> Properties);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Popups|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void EndPopup();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Popups|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void OpenPopup(FString HashName);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Popups|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void CloseCurrentPopup();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Popups", BlueprintPure)
	static bool IsPopupOpen(FString HashName);

// Popups: open/close functions
// Popups: open+begin combined functions helpers
// Popups: query functions

/* Tables */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Tables|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bOpen") bool BeginTable(FString HashName, int Column, FVector2D OuterSize, float InnerWidth);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Tables|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void EndTable();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Tables")
	static void TableNextRow(float MinRowHeight);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Tables|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bVisible") bool TableNextColumn();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Tables|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bVisible") bool TableSetColumnIndex(int Column);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Tables|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void TableHeader(FString Label);

// Tables: Headers & Columns declaration
// Tables: Sorting
// Tables: Miscellaneous functions
// Legacy Columns API (prefer using Tables!)
/* Tab Bars, Tabs */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Tab Bars, Tabs|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bVisible") bool BeginTabBar(FString HashName);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Tab Bars, Tabs|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void EndTabBar();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Tab Bars, Tabs|! Raw C++ Functions !", meta = (AutoCreateRefTerm = "bOpen"), BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bSelected") bool BeginTabItem(FString Label, bool bClosable, UPARAM(ref) bool& bOpen);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Tab Bars, Tabs|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void EndTabItem();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Tab Bars, Tabs|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static UPARAM(DisplayName = "bClicked") bool TabItemButton(FString Label);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Tab Bars, Tabs")
	static void SetNextTabItemClosed(FString Label);


// Logging/Capture

/* Drag and Drop */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Drag and Drop|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static bool BeginDragDropSource();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Drag and Drop|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static bool SetDragDropPayload(FString HashName);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Drag and Drop|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void EndDragDropSource();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Drag and Drop|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static bool BeginDragDropTarget();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Drag and Drop|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static bool AcceptDragDropPayload(FString HashName);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Drag and Drop|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void EndDragDropTarget();

/* Disabling [BETA API] */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Disabling|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void BeginDisabled(bool bDisabled = true);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|Disabling|! Raw C++ Functions !", BlueprintInternalUseOnly)
	static void EndDisabled();

// Clipping
// Focus, Activation
// Item/Widgets Utilities and Query Functions
// Viewports
// Miscellaneous Utilities
// Text Utilities
// Color Utilities
// Inputs Utilities: Keyboard
// Inputs Utilities: Mouse
// Clipboard Utilities
// Settings/.Ini Utilities
// Debug Utilities
// Memory Allocators

private:

    static ImGuiWindowFlags GetFixedWidnowFlag(ImGui_WindowFlags Flag);	  

	static ImGuiInputTextFlags GetFixedInputTextFlag(ImGui_InputTextType Flag);

	static ImVec2 GetScreenSizeInPixels(FVector2D ScreenSize = FVector2D(0, 0));

	static ImVec2 GetRelativeScreenPosition(FVector2D ScreenSize = FVector2D(0, 0));
};






