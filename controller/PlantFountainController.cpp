/**
    Fountaiin Controller
    @author Kenta Suzuki
*/

#include <cnoid/EigenUtil>
#include <cnoid/SimpleController>
#include <cnoid/FountainDevice>

using namespace cnoid;

class PlantFountainController : public SimpleController
{
    Link* valve;
    DeviceList<FountainDevice> fountains;
    std::ostream* os;

public:
    virtual bool initialize(SimpleControllerIO* io) override
    {
        auto ioBody = io->body();
        valve = ioBody->link("SB3_SB3_PIPE1_VALVE_HANDLE");
        fountains = ioBody->devices();

        if(!valve) {
            (*os) << "SB3_SB3_PIPE1_VALVE_HANDLE is not found." << std::endl;
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

CNOID_IMPLEMENT_SIMPLE_CONTROLLER_FACTORY(PlantFountainController)