// #include "LowLevel.hpp"

// #include "Direct.hpp"

// using namespace low_level;

// Interbot::Interbot() : m_leftMotor(Motor::Side::Left), m_rightMotor(Motor::Side::Right)
// {}

// bool Interbot::init()
// {
//     return static_cast<bool>(direct::controller.begin());
// }

// const Interbot::Battery& Interbot::getBattery()
// {
//     return m_battery;
// }

// float Interbot::Battery::getVoltage() const
// {
//     return direct::battery.getRaw() / 77.0f;
// }

// Interbot::Motor& Interbot::getLeftMotor()
// {
//     return m_leftMotor;
// }

// Interbot::Motor& Interbot::getRightMotor()
// {
//     return m_rightMotor;
// }

// void Interbot::Motor::setSpeed(float speed)
// {
//     auto motor = [this] { return m_side == Side::Left ? direct::M1 : direct::M2; }();
//     auto naturalDirectionScale = [this] { return m_side == Side::Left ? 1.0f : -1.0f;
//     }(); m_speed = speed;

//     // TODO
//     int pwm = static_cast<int>(abs(speed * 255.0f));
//     motor.setDuty(pwm);
// }

// float Interbot::Motor::getSpeed() const
// {
//     return m_speed;
// }

// Interbot::Motor::Direction Interbot::Motor::getDirection() const
// {
//     return m_speed > 0.0f ? Direction::Forward : Direction::Backward;
// }

// void Interbot::Motor::stop()
// {
//     setSpeed(0.0f);
// }

// Interbot::Motor::Motor(Side side) : m_side(side) {}

// const Interbot::LightSensor& Interbot::getLightSensor() const
// {
//     return m_lightSensor;
// }

// const Interbot::MoistureSensor& Interbot::getMoistureSensor() const
// {
//     return m_moistureSensor;
// }

// const Interbot::RainSensor& Interbot::getRainSensor() const
// {
//     return m_rainSensor;
// }
