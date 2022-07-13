// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <ImGui.h>
#include "ImGuiBPFL.generated.h"



UENUM(BlueprintType)//, Category = "DearImGui")
enum ImGui_WindowFlags
{
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
	NoInputs                     UMETA(DisplayName = "NoInputs"),
	None                         UMETA(DisplayName = "Null")
};

UENUM(BlueprintType)//, Category = "DearImGui")
enum ImGui_WindowConditions
{
	Nothing =		ImGuiCond_None			UMETA(DisplayName = "Null"),
	Once =			ImGuiCond_Once			UMETA(DisplayName = "Once"),
	Always =		ImGuiCond_Always		UMETA(DisplayName = "Always"),
	FirstUseEver =	ImGuiCond_FirstUseEver	UMETA(DisplayName = "FirstUseEver"),
	Appearing =		ImGuiCond_Appearing		UMETA(DisplayName = "Appearing")
};


UENUM(BlueprintType)//, Category = "DearImGui")
enum VariableType
{
	Type_Float		UMETA(DisplayName = "Float"),
	Type_Float2		UMETA(DisplayName = "Vector 2D"),
	Type_Float3		UMETA(DisplayName = "Vector"),
	Type_Float4		UMETA(DisplayName = "Vector 4"),
	Type_Int		UMETA(DisplayName = "Int"),
	Type_Rotator	UMETA(DisplayName = "Rotator"),
	Type_Transfomr	UMETA(DisplayName = "Transform")
};



UCLASS()
class IMGUI_API UImGuiBPFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	//placeholders / test

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void PrintSimpleWindow(FString Name, FString Text, FVector2D RelativeScreenPosition);

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void PrintSimpleWatermark(FString Name, FString Text, FVector2D RelativeScreenPosition, bool bPrintTextOnly, float BackgroundAlpha);

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void TestFunction();


	// Front-End for blueprints

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void StartPrintingMainWindow(FString Name, TSet<TEnumAsByte<ImGui_WindowFlags>> Properties);

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void StopPrintingMainWindow();

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void AddText(FString Text);

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void StayInSameWindowLine();

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void AddButton(FString Name, bool& bClicked);

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void AddSeparator();

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void AddSpacing();

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void SetNextWindowRelativePosition(FVector2D RelativeScreenPosition, ImGui_WindowConditions Condition);

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void SetNextWindowBackgroundAlpha(float BackgroundAlpha);

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void SetNextWindowCollapseState(bool bCollapsed);  //Do-poprawy/przemyślenia - brak Condition

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void SetNextWindowFocused();

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void AddCollapsingHeader(FString Name, bool& bOpen);

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void StartPrintingChild(FString Name, FVector2D SizeInPixels, bool bBorder, TSet<TEnumAsByte<ImGui_WindowFlags>> Properties);

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void StopPrintingChild();

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void StartPrintingGroup();

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void StopPrintingGroup();

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void AddCheckbox(FString Label, bool bOldState, bool& bNewState, bool& bStateChanged);

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void AddRadioButtons(TSet<FString> Labels, int OldState, int& NewState, bool& bStateChanged);

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void AddBullet();

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void AddProgressBar(FVector2D SizeInPixels, float Progress, FString Overlay = " ");

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void StartPrintingCombo(FString Label, FString Preview, bool& bOpen);

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void StopPrintingCombo();

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void StartPrintingMenu(FString Label, bool bEnabled, bool& bOpen);

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void StopPrintingMenu();

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void StartAddingToMenuBar();

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void StopAddingToMenuBar();

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void StartPrintingMainMenuBar();

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void StopPrintingMainMenuBar();

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void AddMainMenuItem(FString Label, FString Shortcut, bool bSelected, bool bEnabled, bool& bClicked);

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (DevelopmentOnly))
	static void TestGenericFunction(const TArray<UProperty*>& TargetArray, UProperty*& Item);

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta = (CustomStructureParam = "Input, Item"))
	static FString Test(UProperty* Input, UProperty*& Item);

private:

	static bool ValidateWindowFunction(bool bShallPrintingFlagBeSet, FString FunctionName, FString PassedData, FString AdditionalErrorMessage);

	static void TextMousePosition();

    static ImGuiWindowFlags GetFixedWidnowFlag(ImGui_WindowFlags Flag);
};
