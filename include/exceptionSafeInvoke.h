//
// Created by User on 28.12.2022.
//

#ifndef INVOKE_EXCEPTIONSAFEINVOKE_H
#define INVOKE_EXCEPTIONSAFEINVOKE_H

#include <functional>
#include <optional>


namespace detail {

    template<class C, class Pointed, class T1, class... Args>
    bool exceptionSafeInvokeMemptrVoid(Pointed C::* f, T1&& t1, Args&&... args)
    {
        try {
            (std::forward<T1>(t1).*f)(std::forward<Args>(args)...);
            return true;
        }
        catch (...) {
            return false;
        }
    }

    template<class T, class C, class Pointed, class T1, class... Args>
    std::optional<T> exceptionSafeInvokeMemptrNonvoid(Pointed C::* f, T1&& t1, Args&&... args)
    {
        try {
            return (std::forward<T1>(t1).*f)(std::forward<Args>(args)...);
        }
        catch (...) {
            return std::nullopt;
        }
    }

    template<class C, class Pointed, class T1, class... Args>
    decltype(auto) exceptionSafeInvokeMemptr(Pointed C::* f, T1&& t1, Args&&... args)
    {
        if constexpr (std::is_function_v<Pointed>) {
            using return_type = decltype((std::forward<T1>(t1).*f)(std::forward<Args>(args)...));

            if constexpr (std::is_same_v<return_type, void>) {
                return exceptionSafeInvokeMemptrVoid(f, t1, args...);
            } else {
                return exceptionSafeInvokeMemptrNonvoid<return_type>(f, t1, args...);
            }
        } else {
            using return_type = decltype(std::forward<T1>(t1).*f);
            return std::make_optional<return_type>(std::forward<T1>(t1).*f);
        }
    }

    template<class F, class... Args>
    bool exceptionSafeInvokeVoid(F&& f, Args&&... args) {
        try {
            std::forward<F>(f)(std::forward<Args>(args)...);
            return false;
        }
        catch (...) {
            return false;
        }
    }

    template<class T, class F, class... Args>
    std::optional<T> exceptionSafeInvokeNonvoid(F&& f, Args&&... args) {
        try {
            return std::forward<F>(f)(std::forward<Args>(args)...);
        }
        catch(...) {
            return std::nullopt;
        }
    }

}

template<class F, class... Args>
decltype(auto) exceptionSafeInvoke(F&& f, Args&&... args) {
    if constexpr (std::is_member_pointer_v<std::decay_t<F>>) {
        return detail::exceptionSafeInvokeMemptr(f, std::forward<Args>(args)...);
    } else {
        using return_type = decltype(std::forward<F>(f)(std::forward<Args>(args)...));

        if constexpr (std::is_same<return_type, void>::value) {
            return detail::exceptionSafeInvokeVoid(f, args...);
        } else {
            return detail::exceptionSafeInvokeNonvoid<return_type>(f, args...);
        }
    }
}

#endif //INVOKE_EXCEPTIONSAFEINVOKE_H
