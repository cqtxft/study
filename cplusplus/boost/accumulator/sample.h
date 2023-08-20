#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>

namespace boost {                           // Putting your accumulators in the
namespace accumulators {                    // impl namespace has some
namespace impl {                            // advantages. See below.

template<typename Sample>
struct sum_accumulator                      // All accumulators should inherit from
  : accumulator_base                        // accumulator_base.
{
    typedef Sample result_type;             // The type returned by result() below.

    template<typename Args>                 // The constructor takes an argument pack.
    sum_accumulator(Args const & args)
      : sum(args[sample | Sample()])        // Maybe there is an initial value in the
    {                                       // argument pack. ('sample' is defined in
    }                                       // sample.hpp, included above.)

    template<typename Args>                 // The accumulate function is the function
    void operator ()(Args const & args)     // call operator, and it also accepts an
    {                                       // argument pack.
        this->sum += args[sample];
    }

    result_type result(dont_care) const     // The result function will also be passed
    {                                       // an argument pack, but we don't use it here,
        return this->sum;                   // so we use "dont_care" as the argument type.
    }
private:
    Sample sum;
};

}}}
