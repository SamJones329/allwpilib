#include "./include/wpilibjs.h"

using namespace emscripten;

// should try to see if can return EM_VAL directly from some functions. I know that requires allow_raw_pointers(), and making bindings for EM_VAL, but it could potentially remedy some typing issues

EM_JS(EM_VAL, convert_to_math_js_unit, (double value, const char* name), {
    const unit = toUnitMathJS(value, UTF8ToString(name));
    return Emval.toHandle(unit);
});

EM_JS(double, si_from_math_js_unit, (EM_VAL val_handle, const char* unit), {
    const val = Emval.toValue(val_handle);
    return val.toNumber(UTF8ToString(unit));
});


EMSCRIPTEN_BINDINGS(geometry) {
    class_<frc::CoordinateAxis>("CoordinateAxis")
        .constructor<const frc::CoordinateAxis&>()
        .constructor<double, double, double>()
        .class_function("N", &frc::CoordinateAxis::N)
        .class_function("S", &frc::CoordinateAxis::S)
        .class_function("E", &frc::CoordinateAxis::E)
        .class_function("W", &frc::CoordinateAxis::W)
        .class_function("U", &frc::CoordinateAxis::U)
        .class_function("D", &frc::CoordinateAxis::D)
        ;


    class_<frc::CoordinateSystem>("CoordinateSystem")
        .constructor<const frc::CoordinateSystem&>()
        .constructor<const frc::CoordinateAxis&, const frc::CoordinateAxis&, const frc::CoordinateAxis&>()
        .class_function("NWU", &frc::CoordinateSystem::NWU)
        .class_function("EDN", &frc::CoordinateSystem::EDN)
        .class_function("NED", &frc::CoordinateSystem::NED)
        ;


    class_<frc::Pose2d>("Pose2d")
        .constructor()
        .constructor(std::function<frc::Pose2d(frc::Translation2d, frc::Rotation2d)>([](frc::Translation2d translation, frc::Rotation2d rotation) {
            return frc::Pose2d(translation, rotation);
        }))
        .constructor(std::function<frc::Pose2d(val, val, frc::Rotation2d)>([](val x_val, val y_val, frc::Rotation2d rotation) {
            const double x = si_from_math_js_unit(x_val.as_handle(), "m");
            const double y = si_from_math_js_unit(y_val.as_handle(), "m");
            const units::meter_t unit_x(x);
            const units::meter_t unit_y(y);
            const frc::Translation2d translation(unit_x, unit_y);
            return frc::Pose2d(translation, rotation);
        }))
        .function("plus", &frc::Pose2d::operator+)
        .function("minus", &frc::Pose2d::operator-)
        .function("equals", &frc::Pose2d::operator==)
        .function("translation", &frc::Pose2d::Translation)
        .function("x", std::function<val(frc::Pose2d&)>([](frc::Pose2d& pose) {
            auto x = pose.X();
            return val::take_ownership(
                convert_to_math_js_unit(x.to<double>(), x.name())
            );
        }))
        .function("y", std::function<val(frc::Pose2d&)>([](frc::Pose2d& pose) {
            auto y = pose.Y();
            return val::take_ownership(
                convert_to_math_js_unit(y.to<double>(), y.name())
            );
        }))
        .function("rotation", &frc::Pose2d::Rotation)
        .function("times", &frc::Pose2d::operator*)
        .function("divideBy", &frc::Pose2d::operator/)
        .function("rotateBy", &frc::Pose2d::RotateBy)
        .function("transformBy", &frc::Pose2d::TransformBy)
        .function("relativeTo", &frc::Pose2d::RelativeTo)
        .function("exp", &frc::Pose2d::Exp)
        .function("log", &frc::Pose2d::Log)
        .function("nearest", std::function<frc::Pose2d(frc::Pose2d&, val)>([](frc::Pose2d& pose, val poses) {
            std::vector<frc::Pose2d> posesVector = vecFromJSArray<frc::Pose2d>(poses);
            return pose.Nearest(std::span<const frc::Pose2d>(posesVector));
        }))
        ;
    register_vector<frc::Pose2d>("vector<Pose2d>");


    class_<frc::Pose3d>("Pose3d")
        .constructor()
        ;


    class_<frc::Quaternion>("Quaternion")
        .constructor()
        ;


    class_<frc::Rotation2d>("Rotation2d")
        .constructor()
        .constructor(std::function<frc::Rotation2d(val)>([](val radians_val) {
            const double rads = si_from_math_js_unit(radians_val.as_handle(), "rad");
            const units::radian_t unit_rads(rads);
            return frc::Rotation2d(unit_rads);
        }))
        .constructor(std::function<frc::Rotation2d(double, double)>([](double x, double y) {
            return frc::Rotation2d(x, y);
        }))
        .function("plus", &frc::Rotation2d::operator+)
        .function("minus", std::function<frc::Rotation2d (frc::Rotation2d&, const frc::Rotation2d&)>([](frc::Rotation2d& rotation, frc::Rotation2d other) {
            return rotation - other;
        }))
        .function("negated", std::function<frc::Rotation2d (frc::Rotation2d&)>([](frc::Rotation2d& rotation) {
            return -rotation;
        }))
        .function("times", &frc::Rotation2d::operator*)
        .function("divideBy", &frc::Rotation2d::operator/)
        .function("equals", &frc::Rotation2d::operator==)
        .function("rotateBy", &frc::Rotation2d::RotateBy)
        .function("value", std::function<val(frc::Rotation2d&)>([](frc::Rotation2d& rotation) {
            auto deg = rotation.Radians();
            return val::take_ownership(
                convert_to_math_js_unit(deg.to<double>(), deg.name())
            );
        }))
        .function("cos", &frc::Rotation2d::Cos)
        .function("sin", &frc::Rotation2d::Sin)
        .function("tan", &frc::Rotation2d::Tan)
        ;


    class_<frc::Rotation3d>("Rotation3d")
        .constructor()
        ;


    class_<frc::Transform2d>("Transform2d")
        .constructor()
        .function("translation", &frc::Transform2d::Translation)
        .function("x", std::function<val(frc::Transform2d&)>([](frc::Transform2d& transform) {
            auto x = transform.X();
            return val::take_ownership(
                convert_to_math_js_unit(x.to<double>(), x.name())
            );
        }))
        .function("y", std::function<val(frc::Transform2d&)>([](frc::Transform2d& transform) {
            auto y = transform.Y();
            return val::take_ownership(
                convert_to_math_js_unit(y.to<double>(), y.name())
            );
        }))
        .function("rotation", &frc::Transform2d::Rotation)
        .function("inverse", &frc::Transform2d::Inverse)
        .function("times", &frc::Transform2d::operator*)
        .function("divideBy", &frc::Transform2d::operator/)
        .function("plus", &frc::Transform2d::operator+)
        .function("equals", &frc::Transform2d::operator==)
        ;

    
    class_<frc::Transform3d>("Transform3d")
        .constructor()
        ;


    class_<frc::Translation2d>("Translation2d")
        .constructor()
        .constructor(std::function<frc::Translation2d(val, val)>([](val x_val, val y_val) {
            const double x = si_from_math_js_unit(x_val.as_handle(), "m");
            const double y = si_from_math_js_unit(y_val.as_handle(), "m");
            const units::meter_t unit_x(x);
            const units::meter_t unit_y(y);
            return frc::Translation2d(unit_x, unit_y);
        }))
        .function("distance", std::function<val(frc::Translation2d&, frc::Translation2d&)>([](frc::Translation2d& translation, frc::Translation2d& other) {
            auto dist = translation.Distance(other);
            return val::take_ownership(
                convert_to_math_js_unit(dist.to<double>(), dist.name())
            );
        }))
        .function("x", std::function<val(frc::Translation2d&)>([](frc::Translation2d& translation) {
            auto x = translation.X();
            return val::take_ownership(
                convert_to_math_js_unit(x.to<double>(), x.name())
            );
        }))
        .function("y", std::function<val(frc::Translation2d&)>([](frc::Translation2d& translation) {
            auto y = translation.Y();
            return val::take_ownership(
                convert_to_math_js_unit(y.to<double>(), y.name())
            );
        }))
        .function("norm", std::function<val(frc::Translation2d&)>([](frc::Translation2d& translation) {
            auto norm = translation.Norm();
            return val::take_ownership(
                convert_to_math_js_unit(norm.to<double>(), norm.name())
            );
        }))
        .function("angle", &frc::Translation2d::Angle)
        .function("rotateBy", &frc::Translation2d::RotateBy)
        .function("plus", &frc::Translation2d::operator+)
        .function("minus", std::function<frc::Translation2d (frc::Translation2d&, const frc::Translation2d&)>([](frc::Translation2d& translation, frc::Translation2d other) {
            return translation - other;
        }))
        .function("negated", std::function<frc::Translation2d (frc::Translation2d&)>([](frc::Translation2d& translation) {
            return -translation;
        }))
        .function("times", &frc::Translation2d::operator*)
        .function("divideBy", &frc::Translation2d::operator/)
        .function("equals", &frc::Translation2d::operator==)
        .function("nearest", std::function<frc::Translation2d(frc::Translation2d&, val)>([](frc::Translation2d& translation, val translations) {
            std::vector<frc::Translation2d> translationsVector = vecFromJSArray<frc::Translation2d>(translations);
            return translation.Nearest(std::span<const frc::Translation2d>(translationsVector));
        }))
        ;

    
    class_<frc::Translation3d>("Translation3d")
        .constructor()
        ;


    class_<frc::Twist2d>("Twist2d")
        .constructor()
        .constructor(std::function<frc::Twist2d(val, val, val)>([](val dx_val, val dy_val, val dth_val) {
            const double dx = si_from_math_js_unit(dx_val.as_handle(), "m");
            const double dy = si_from_math_js_unit(dy_val.as_handle(), "m");
            const double dth = si_from_math_js_unit(dth_val.as_handle(), "rad");
            const units::meter_t unit_dx(dx);
            const units::meter_t unit_dy(dy);
            const units::radian_t unit_dth(dth);
            return frc::Twist2d{
                .dx = unit_dx, 
                .dy = unit_dy,
                .dtheta = unit_dth
            };
        }))
        .function("equals", &frc::Twist2d::operator==)
        .function("times", &frc::Twist2d::operator*)
        ;
    
    class_<frc::Twist3d>("Twist3d")
        .constructor()
        ;

}