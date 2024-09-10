/**
    Valve Controller
    @author Kenta Suzuki
*/

#include <cnoid/EigenUtil>
#include <cnoid/FireDevice>
#include <cnoid/FountainDevice>
#include <cnoid/SimpleController>
#include <cnoid/SmokeDevice>

using namespace cnoid;

class PlantValveController : public SimpleController
{
    Link* valve;
    DeviceList<FireDevice> fires;
    DeviceList<FountainDevice> fountains;
    DeviceList<SmokeDevice> smokes;
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
        fires = ioBody->devices();
        fountains = ioBody->devices();
        smokes = ioBody->devices();

        if(!valve) {
            (*os) << prefix << "PIPE1_VALVE_HANDLE is not found." << std::endl;
        }
        io->enableInput(valve, Link::JointAngle);

        os = &io->os();
        for(auto& fire : fires) {
            fire->on(true);
            fire->notifyStateChange();
        }
        for(auto& fountain : fountains) {
            fountain->on(true);
            fountain->notifyStateChange();
        }
        for(auto& smoke : smokes) {
            smoke->on(true);
            smoke->notifyStateChange();
        }
        return true;
    }

    virtual bool control() override
    {
        bool is_valve_opened = valve->q() > radian(0.0) ? true : false;
        for(auto& fire : fires) {
            if(is_valve_opened && !fire->on()) {
                fire->on(true);
            } else if(!is_valve_opened && fire->on()) {
                fire->on(false);
            }
            fire->notifyStateChange();
        }
        for(auto& fountain : fountains) {
            if(is_valve_opened && !fountain->on()) {
                fountain->on(true);
            } else if(!is_valve_opened && fountain->on()) {
                fountain->on(false);
            }
            fountain->notifyStateChange();
        }
        for(auto& smoke : smokes) {
            if(is_valve_opened && !smoke->on()) {
                smoke->on(true);
            } else if(!is_valve_opened && smoke->on()) {
                smoke->on(false);
            }
            smoke->notifyStateChange();
        }
        return true;
    }
};

CNOID_IMPLEMENT_SIMPLE_CONTROLLER_FACTORY(PlantValveController)