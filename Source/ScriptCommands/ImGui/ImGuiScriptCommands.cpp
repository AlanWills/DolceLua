#include "ScriptCommands/ImGui/ImGuiScriptCommands.h"
#include "sol/sol.hpp"

#include "imgui.h"


namespace Dolce::Lua::ImGui::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    state.create_named_table(
      "ImGui",
      "Text", &::ImGui::Text);
  }
}