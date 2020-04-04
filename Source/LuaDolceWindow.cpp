#include "LuaDolceWindow.h"
#include "imgui.h"


namespace Dolce
{
  //------------------------------------------------------------------------------------------------
  LuaDolceWindow::LuaDolceWindow(const std::string& windowName, sol::table windowTable) :
    DolceWindow(windowName)
  {
    m_renderFunction = windowTable["render"].get<sol::protected_function>();
  }

  //------------------------------------------------------------------------------------------------
  void LuaDolceWindow::render()
  {
    if (m_renderFunction.valid())
    {
      auto result = m_renderFunction.call();
      if (!result.valid())
      {
        sol::error e = result;
        ImGui::Text(e.what());
      }
    }
  }
}