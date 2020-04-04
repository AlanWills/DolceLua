#pragma once

#include "DolceWindow.h"
#include "sol/sol.hpp"


namespace Dolce
{
  class LuaDolceWindow : public DolceWindow
  {
    public:
      LuaDolceWindow(const std::string& windowName, sol::table windowTable);

      void render() override;

    private:
      sol::protected_function m_renderFunction;
  };
}