#include "TestUtils.h"
#include "LuaAssert.h"
#include "Lua/LuaState.h"
#include "ScriptCommands/DolceScriptCommands.h"
#include "Dolce.h"
#include "GLFW/glfw3.h"

using LuaState = Celeste::Lua::LuaState;


namespace TestDolceLua
{
  void render() {}

  TEST_UTILS_TEST_CLASS(TestDolceScriptCommands)

  GLFWwindow* window;

  //------------------------------------------------------------------------------------------------
  void TestDolceScriptCommands::testInitialize()
  {
    glfwInit();
    window = glfwCreateWindow(1, 1, "", nullptr, nullptr);

    LuaState::instance()["Dolce"] = sol::nil;
    LuaState::instance()["ImGui"] = sol::nil;
    LuaState::instance().collect_garbage();
  }

  //------------------------------------------------------------------------------------------------
  void TestDolceScriptCommands::testCleanup()
  {
    glfwTerminate();
    if (window != nullptr)
    {
      glfwDestroyWindow(window);
    }

    LuaState::instance()["Dolce"] = sol::nil;
    LuaState::instance()["ImGui"] = sol::nil;
    LuaState::instance().collect_garbage();
  }

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DolceScriptCommands_Initialize_AddsDolceTable_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();
    Dolce::Dolce dolce(window);
    Dolce::Lua::ScriptCommands::initialize(state, dolce);

    LuaAssert::IsTable(state["Dolce"]);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DolceScriptCommands_Initialize_Adds_instance_ToDolceTable)
  {
    sol::state& state = LuaState::instance();
    Dolce::Dolce dolce(window);
    Dolce::Lua::ScriptCommands::initialize(state, dolce);
    
    Assert::IsTrue(state["Dolce"]["instance"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DolceScriptCommands_Initialize_Adds_registerWindow_ToDolceTable)
  {
    sol::state& state = LuaState::instance();
    Dolce::Dolce dolce(window);
    Dolce::Lua::ScriptCommands::initialize(state, dolce);

    Assert::IsTrue(state["Dolce"]["registerWindow"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DolceScriptCommands_Initialize_Loads_DebugDolceWindows_Module)
  {
    sol::state& state = LuaState::instance();
    Dolce::Dolce dolce(window);
    Dolce::Lua::ScriptCommands::initialize(state, dolce);

    Assert::IsTrue(state["package"].valid());
    Assert::IsTrue(state["package"]["loaded"].valid());
    Assert::IsTrue(state["package"]["loaded"]["Debug.DolceWindows"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DolceScriptCommands_Initialize_InitializesImGuiScriptCommands)
  {
    sol::state& state = LuaState::instance();
    Dolce::Dolce dolce(window);
    Dolce::Lua::ScriptCommands::initialize(state, dolce);

    LuaAssert::IsTable(state["ImGui"]);
  }

#pragma endregion

#pragma region Instance Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DolceScriptCommands_instance_ReturnsDolceInstance_InputtingIntoInitialize)
  {
    sol::state& state = LuaState::instance();
    Dolce::Dolce dolce(window);
    Dolce::Lua::ScriptCommands::initialize(state, dolce);

    Dolce::Dolce* result = state["Dolce"]["instance"].get<Dolce::Dolce*>();

    Assert::IsTrue(&dolce == result);
  }

#pragma endregion

#pragma region Register Window Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DolceScriptCommands_registerWindow_AddsWindowToDolceInstance)
  {
    sol::state& state = LuaState::instance();
    Dolce::Dolce dolce(window);
    Dolce::Lua::ScriptCommands::initialize(state, dolce);

    sol::table windowTable = state.create_table();
    windowTable["render"] = &render;

    auto result = state["Dolce"]["registerWindow"].get<sol::protected_function>().call(dolce, "Test Window", windowTable);

    LuaAssert::IsValid(result);
    Assert::IsNotNull(dolce.findWindow("Test Window"));
  }

#pragma endregion

  };
}