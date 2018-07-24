#pragma once

#include <ozo/error.h>

#include <sstream>

namespace ozo {
namespace tests {
namespace error {

enum code {
    ok, // to do no use error code 0
    error, // error
};

namespace detail {

class category : public error_category {
public:
    const char* name() const noexcept { return "ozo::tests::error::detail::category"; }

    std::string message(int value) const {
        switch (code(value)) {
            case ok:
                return "no error";
            case error:
                return "test error";
        }
        std::ostringstream error;
        error << "no message for value: " << value;
        return error.str();
    }
};

} // namespace detail

inline const error_category& get_category() {
    static detail::category instance;
    return instance;
}

} // namespace error
} // namespace tests
} // namespace ozo

namespace boost {
namespace system {

template <>
struct is_error_code_enum<ozo::tests::error::code> : std::true_type {};

} // namespace system
} // namespace boost

namespace ozo {
namespace tests {
namespace error {

inline auto make_error_code(const code e) {
    return boost::system::error_code(static_cast<int>(e), get_category());
}

} // namespace error
} // namespace tests
} // namespace ozo
