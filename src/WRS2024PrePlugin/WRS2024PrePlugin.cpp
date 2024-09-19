/**
   @author Kenta Suzuki
*/

#include <cnoid/ExecutablePath>
#include <cnoid/Format>
#include <cnoid/Plugin>
#include <cnoid/WRSUtilBar>

using namespace cnoid;

class WRS2024PrePlugin : public Plugin
{
public:
    WRS2024PrePlugin() : Plugin("WRS2024Pre")
    {
        require("Body");
    }
    
    virtual bool initialize() override
    {
        auto bar = new WRSUtilBar("WRS2024PreBar");
        bar->setProjectDirectory(shareDir() + "/WRS2024PRE/project");
        bar->setRegistrationFile(shareDir() + "/WRS2024PRE/share/default/registration.yaml");
        bar->update();
        addToolBar(bar);
        return true;
    }

    virtual const char* description() const override
    {
        static std::string text =
            formatC("WRS2024Pre Plugin Version {}\n", CNOID_FULL_VERSION_STRING) +
            "\n" +
            "Copyright (c) 2024 Japan Atomic Energy Agency.\n"
            "\n" +
            MITLicenseText();
        return text.c_str();
    }
};

CNOID_IMPLEMENT_PLUGIN_ENTRY(WRS2024PrePlugin)