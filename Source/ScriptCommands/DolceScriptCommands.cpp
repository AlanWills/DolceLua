#include "ScriptCommands/DolceScriptCommands.h"
#include "ScriptCommands/ImGui/ImGuiScriptCommands.h"
#include "Lua/LuaState.h"
#include "LuaDolceWindow.h"
#include "Dolce.h"

namespace Dolce::Lua::ScriptCommands
{
  namespace Internals
  {
    void registerWindow(Dolce& dolce, const std::string& windowName, sol::table windowTable)
    {
      dolce.registerWindow(std::make_unique<::Dolce::LuaDolceWindow>(windowName, windowTable));
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state, Dolce& dolce)
  {
    ImGui::ScriptCommands::initialize(state);

    auto dolceUserType = state.new_usertype<Dolce>(
      "Dolce",
      "instance", sol::make_object(state.lua_state(), &dolce),
      "registerWindow", &Internals::registerWindow);

    Celeste::Lua::LuaState::requireModule("Debug.DolceWindows");
  }
}