#include "ftrig.hpp"

#include "constants.hpp"
#include "numfunctions.hpp"
#include "common_private.hpp"

#include <cassert>
#include <bit>

// TODO = comments with doxygen?
namespace mmath 
{
    
    // ------------------------ BASIC ------------------------
    
    constexpr float sin(float const x) 
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        
        // sign of function (x%2 == x&1, x&-2 != x&1)
        int8_t const sf = -2 * ( floor( floor((x/pi) & 1)) + 1 ) + 3;
        
        // sign of argument
        int8_t const sa = -2 * ( floor( floor((-2*x/pi) & 1)) + 1 ) + 3;
        
        // scale parameter, used to offset our approximation
        float const k = floor( (x + 0.5*pi)/pi );
        
        // argument to give to our lagrange polynomial approximation, guaranteed to
        // be 0 <= arg <= pi/2
        float const arg = sa * (k * pi - x);
        
        // lagrange polynomial for sin with (0,0),(pi/6,1/2),(pi/4,sqrt(2)/2),
        // (pi/3,sqrt(3)/2),(pi/2,1)
        return sf*(0.028797*arg*arg*arg*arg
                   -0.204340696022*arg*arg*arg
                   +0.0213730075289*arg*arg
                   +0.995626*arg);
    }
    constexpr float cos(float const x) 
    {
        return sin(pi/2 - x);
    }
    constexpr float tan(float const x) 
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        // compile time constants
        static constexpr float pihalved = pi/2.f;
        static constexpr float twooverpi = 1.f/pihalved;
        static constexpr float c[4] = {0.58873f,-0.222615f,0.0907791f,-0.0148931f}; 
        // a tangent approximation in [0,pi/2] can be derived by taking an transformed 
        // hyperbola branch with its pole in pihalved, offset by a polynomial approximation 
        // of the error. hyp(x) = -1/(x-pi/2)-2/pi
        // repetition can be achieved with modular arithmetic i(x)=mod(x+pi/2, pi)-pi/2
        // https://www.desmos.com/calculator/xrkvpwljyl
        // DISADVANTAGE = 1 mod + 2 division operations + evaluation of 4th deg polynomial
        float in = ((x+pihalved)%pi)-pihalved;
        
        // faster than using in > 0.f. Proof:
        // https://www.quick-bench.com/q/gBLxxnYgEEKMI4cygqs0MzI4Rbk
        int8_t const in_sign = -2*static_cast<int32_t>(std::bit_cast<uint32_t>(in)>>31u);
        
        // cancel sign
        in = std::bit_cast<float>(std::bit_cast<uint32_t>(in) & 0x7ffffff);
        float const res = in_sign*( 1.f/(in-pihalved)-twooverpi
                                   +c[3]*in*in*in*in+c[2]*in*in*in+c[1]*in*in+c[0]*in );
        return res;
    }
    
    // ----------------------- INVERSE -----------------------
    
    constexpr float asin() {}
    constexpr float acos() {}
    constexpr float atan() {}
    constexpr float atan2() {}
    
    // TODO = requires exponential
    // --------------------- HYPERBOLIC ----------------------
    
    constexpr float sinh() {}
    constexpr float cosh() {}
    constexpr float tanh() {}
    
    // ----------------- INVERSE HYPERBOLIC ------------------
    
    constexpr float asinh() {}
    constexpr float acosh() {}
    constexpr float atanh() {}
    
    //----------------- ANGULAR CONVERSIONS ------------------
    
    constexpr float deg2rad() {}
    constexpr float rad2deg() {}
}