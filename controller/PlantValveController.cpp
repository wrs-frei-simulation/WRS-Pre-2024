/**
    Valve Controller
    @author Kenta Suzuki
*/

#include <cnoid/EigenUtil>
#include <cnoid/SimpleController>
#include <cnoid/FountainDevice>

using namespace cnoid;

class PlantValveController : public SimpleController
{
    Link* valve;
    DeviceList<FountainDevice> fountains;
    std::ostream* os;

public:
    virtual bool initialize(SimpleControllerIO* io) override
    {
        auto ioBody = io->body();

        std::string prefix;

        for(auto& option : io->options()) {
            prefix = option;
            io->os() << "prefix: " << prefix << std::endl;
        }

        valve = ioBody->link(prefix + "PIPE1_VALVE_HANDLE");
        fountains = ioBody->devices();

        if(!valve) {
            (*os) << prefix << "PIPE1_VALVE_HANDLE is not found." << std::endl;
        }
        io->enableInput(valve, Link::JointAngle);

        os = &io->os();
        for(auto& fountain : fountains) {
            fountain->on(true);
            fountain->notifyStateChange();
        }
        return true;
    }

    virtual bool control() override
    {
        bool is_valve_opened = valve->q() > radian(0.0) ? true : false;
        for(auto& fountain : fountains) {
            if(is_valve_opened && !fountain->on()) {
                fountain->on(true);
            } else if(!is_valve_opened && fountain->on()) {
                fountain->on(false);
            }
            fountain->notifyStateChange();
        }
        return true;
    }
};

CNOID_IMPLEMENT_SIMPLE_CONTROLLER_FACTORY(PlantValveController)